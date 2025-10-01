#include "Physics.h"

Physics::Physics(std::vector<Body*> moleculeBodyList, Body* containerBody) 
	: m_moleculeBodyList(moleculeBodyList), m_containerBody(containerBody)
{}

Physics::~Physics()
{
	delete eventArray;
}

void Physics::computeNewVelocities(Body* mol1, Body* mol2)
{
	// Positions
	float x1 = mol1->getPosition().x;
	float y1 = mol1->getPosition().y;
	float x2 = mol2->getPosition().x;
	float y2 = mol2->getPosition().y;
	// Vitesses vectorielles initiales
	sf::Vector2f v1_i = mol1->getVelocity();
	sf::Vector2f v2_i = mol2->getVelocity();
	// Masses
	float m1 = 1;
	float m2 = 1;
	// Angle molécule 1
	float alpha1 = atan2(y2 - y1, x2 - x1);
	float beta1 = atan2(v1_i.y, v1_i.x);
	float gamma1 = beta1 - alpha1;
	// Angles molécule 2
	float alpha2 = atan2(y1 - y2, x1 - x2);
	float beta2 = atan2(v2_i.y, v2_i.x);
	float gamma2 = beta2 - alpha2;
	// Normes des vitesses initiales
	float v12_i = sqrt(v1_i.x * v1_i.x + v1_i.y * v1_i.y) * cos(gamma1); // vitesse transmise au corps 2 par le corps 1
	float v11_i = sqrt(v1_i.x * v1_i.x + v1_i.y * v1_i.y) * sin(gamma1); // vitesse conservé du corps 1
	float v21_i = sqrt(v2_i.x * v2_i.x + v2_i.y * v2_i.y) * cos(gamma2);
	float v22_i = sqrt(v2_i.x * v2_i.x + v2_i.y * v2_i.y) * sin(gamma2);
	// Normes des vitesses finales
	float v12_f = ((m1 - m2) * v12_i - 2 * m2 * v21_i) / (m1 + m2);
	float v21_f = ((m2 - m1) * v21_i + 2 * m1 * v12_i) / (m1 + m2);
	// Vitesses vectorielles finales
	sf::Vector2f v1_f = v11_i * sf::Vector2f{ -sin(alpha1), cos(alpha1) } + v12_f * sf::Vector2f{ cos(alpha1), sin(alpha1) };
	sf::Vector2f v2_f = v22_i * sf::Vector2f{ -sin(alpha2), cos(alpha2) } - v21_f * sf::Vector2f{ cos(alpha2), sin(alpha2) };
	// Application des vitesses finales
	mol1->setVelocity(v1_f);
	mol2->setVelocity(v2_f);
	// Éloigment des molécules pour éviter des collisions inutiles
	mol1->setPosition(sf::Vector2f{ x1, y1 } + v1_f * m_minEventTime);
	mol2->setPosition(sf::Vector2f{ x2, y2 } + v2_f * m_minEventTime);
}

int Physics::distanceBetweenMolecules(Body* mol1, Body* mol2)
{
	float radius1 = mol1->getSize().y;
	float radius2 = mol2->getSize().y;
	float distance = sqrt(pow((mol2->getPosition().x - mol1->getPosition().x), 2) + pow((mol2->getPosition().y - mol1->getPosition().y), 2));
	
	return (distance - radius1 - radius2);
}

bool Physics::backtrackToCollision(Body* mol1, Body* mol2)
{
	// Positions vectorielles
	sf::Vector2f q1 = mol1->getPosition();
	sf::Vector2f q2 = mol2->getPosition();
	// Vitesses vectorielles
	sf::Vector2f v1 = mol1->getVelocity();
	sf::Vector2f v2 = mol2->getVelocity();
	// Rayons
	float r1 = mol1->getSize().x;
	float r2 = mol2->getSize().x;

	// Différences des positions vectorielles
	sf::Vector2f dq = { q1.x - q2.x, q1.y - q2.y };
	// Différences des vitesses vectorielles
	sf::Vector2f dv = { v1.x - v2.x, v1.y - v2.y };
	
	// Termes quadratiques
	float a = dv.x * dv.x + dv.y * dv.y;
	float b = 2 * (dq.x * dv.x + dq.y * dv.y);
	float c = dq.x * dq.x + dq.y * dq.y - (r1 + r2) * (r1 + r2);
	// Discriminant
	float disc = b * b - 4 * a * c;

	if (a == 0)
		return false;
	if (disc < 0) // Aucune collision
		return false;

	// Moment exact de la collision (2 solutions)
	float collisionTime = 1.0f;
	float t1 = (-b + sqrt(disc)) / (2 * a);
	float t2 = (-b - sqrt(disc)) / (2 * a);

	// Choisi la solution négative la plus proche de 0 (retour en arrière minimal)
	if (t1 < 0 && t2 < 0)
		collisionTime = (t1 > t2) ? t1 : t2;
	else
		collisionTime = (t1 < t2) ? t1 : t2;

	if (collisionTime > 0) 
		return false;

	// Application des nouvelles positions
	mol1->setPosition(q1 + v1 * collisionTime);
	mol2->setPosition(q2 + v2 * collisionTime);

	return true;
}

bool Physics::backtrackToWallCollision(Body* mol)
{
	// Conteneur / Murs
	Body* walls = m_containerBody;
	// Positions vectorielles
	sf::Vector2f q = mol->getPosition(); // au centre
	sf::Vector2f w = walls->getPosition();
	// Rayon molécule
	float r = mol->getSize().x;
	// Taille du conteneur
	sf::Vector2f c_size = walls->getSize();
	// Vitesse vectorielle
	sf::Vector2f v = mol->getVelocity();

	float best_t = -INFINITY;
	float t = -INFINITY;

	// Si la molécule chevauche/dépasse le mur gauche, et si la vitesse est dans cette direction
	if (q.x - r <= w.x && v.x < 0) // Horizontal gauche
	{
		t = (w.x - (q.x - r)) / v.x;
		if (t < 0 && t > best_t) best_t = t;
	}
	if (q.x + r >= w.x + c_size.x && v.x > 0) // Horizontal droit
	{
		t = ((w.x + c_size.x) - (q.x + r)) / v.x;
		if (t < 0 && t > best_t) best_t = t;
	}
	if (q.y - r <= w.y && v.y < 0) // Vertical haut
	{
		t = (w.y - (q.y - r)) / v.y;
		if (t < 0 && t > best_t) best_t = t;
	}
	if (q.y + r >= w.y + c_size.y && v.y > 0) // Vertical bas
	{
		t = ((w.y + c_size.y) - (q.y + r)) / v.y;
		if (t < 0 && t > best_t) best_t = t;
	}
	if (best_t == -INFINITY)
		return false;

	// Application de la nouvelle position
	mol->setPosition(q + v * best_t);

	return true;
}

float Physics::nextMoleculesCollision(Body* mol1, Body* mol2)
{
	// Positions vectorielles
	sf::Vector2f q1 = mol1->getPosition();
	sf::Vector2f q2 = mol2->getPosition();
	// Vitesses vectorielles
	sf::Vector2f v1 = mol1->getVelocity();
	sf::Vector2f v2 = mol2->getVelocity();
	// Rayons
	float r1 = mol1->getSize().x;
	float r2 = mol2->getSize().x;

	// Différences des positions vectorielles
	sf::Vector2f dq = { q1.x - q2.x, q1.y - q2.y };
	// Différences des vitesses vectorielles
	sf::Vector2f dv = { v1.x - v2.x, v1.y - v2.y };

	// Termes quadratiques
	float a = dv.x * dv.x + dv.y * dv.y;
	float b = 2 * (dq.x * dv.x + dq.y * dv.y);
	float c = dq.x * dq.x + dq.y * dq.y - (r1 + r2) * (r1 + r2);
	// Discriminant
	float disc = b * b - 4 * a * c;

	if (a == 0)
		return INFINITY;
	if (disc < 0) // Aucune collision
		return INFINITY;

	// Moment exact de la collision (2 solutions)
	float collisionTime = INFINITY;
	float t1 = (-b + sqrt(disc)) / (2 * a);
	float t2 = (-b - sqrt(disc)) / (2 * a);

	// Choisi la solution positive la plus petite
	if (t1 > 0.0f && t2 > 0.0f)
		collisionTime = (t1 < t2) ? t1 : t2;
	else
		collisionTime = (t1 > t2) ? t1 : t2;

	if (collisionTime <= 0.0f)
		return INFINITY;
	if (collisionTime < m_minEventTime)
		collisionTime = m_minEventTime;

	//printf("mol collision time : %f\n", collisionTime);

	return collisionTime;
}

float Physics::nextWallCollision(Body* mol)
{
	// Conteneur / Murs
	Body* walls = m_containerBody;
	// Positions vectorielles
	sf::Vector2f q = mol->getPosition(); // au centre
	sf::Vector2f w = walls->getPosition();
	// Rayon molécule
	float r = mol->getSize().x;
	// Taille du conteneur
	sf::Vector2f c_size = walls->getSize();
	// Vitesse vectorielle
	sf::Vector2f v = mol->getVelocity();

	float t = INFINITY;
	float best_t = INFINITY;

	// Quand la molécule percutera le mur gauche
	if (v.x < 0)
	{
		t = (w.x - (q.x - r)) / v.x;
		if (t > 0.0f && t < best_t) best_t = t;
	}
	// Quand la molécule percutera le mur droit
	if (v.x > 0)
	{
		t = ((w.x + c_size.x) - (q.x + r)) / v.x;
		if (t > 0.0f && t < best_t) best_t = t;
	}
	// Quand la molécule percutera le mur haut
	if (v.y < 0)
	{
		t = (w.y - (q.y - r)) / v.y;
		if (t > 0.0f && t < best_t) best_t = t;
	}
	// Quand la molécule percutera le mur bas
	if (v.y > 0)
	{
		t = ((w.y + c_size.y) - (q.y + r)) / v.y;
		if (t > 0.0f && t < best_t) best_t = t;
	}

	if (best_t < m_minEventTime)
		best_t = m_minEventTime;

	//printf("wall collision time : %f\n", best_t);

	return best_t;
}

void Physics::computeNextEvents()
{
	if (eventArray == nullptr)
	{
		eventArray = new EventArray();
		for (int i = 0; i < m_moleculeBodyList.size(); i++) // taille m_nMolecules
		{
			Body* mol1 = m_moleculeBodyList[i];
			for (int j = i + 1; j < m_moleculeBodyList.size(); j++) // // taille m_nMolecules
			{
				Body* mol2 = m_moleculeBodyList[j];
				m_event = new Event(nextMoleculesCollision(mol1, mol2), mol1, mol2, false);
				eventArray->addEvent(m_event);
			}
			m_event = new Event(nextWallCollision(mol1), mol1, nullptr, true);
			eventArray->addEvent(m_event);
		}
	}
	else
	{
		std::vector<Body*> lastBodiesCollisions = { m_nextEvent->body1, m_nextEvent->body2};
		// Supprime tous les events où les molécules associés au dernier event sont impliquées : ils ne sont plus valable
		eventArray->deleteEvent(eventArray->nextEvent());
		eventArray->deleteBodyEvent(lastBodiesCollisions[0]);
		eventArray->deleteBodyEvent(lastBodiesCollisions[1]);
		for (int i = 0; i < m_moleculeBodyList.size(); i++) // taille m_nMolecules
		{
			Body* mol1 = m_moleculeBodyList[i];
			for (int j = 0; j < lastBodiesCollisions.size(); j++) // taille 2
			{
				Body* mol2 = lastBodiesCollisions[j];
				if (mol2 == nullptr || mol1 == mol2)
					continue;
				m_event = new Event(nextMoleculesCollision(mol1, mol2), mol1, mol2, false);
				eventArray->addEvent(m_event);
			}
			m_event = new Event(nextWallCollision(mol1), mol1, nullptr, true);
			eventArray->addEvent(m_event);
		}
	}
	m_nextEvent = eventArray->nextEvent();
}

void Physics::updateMapCollisions(std::string method)
{
	//printf("%d", m_containerBody->getPosition().x + m_containerBody->getSize().x);
	for (int i = 0; i < m_moleculeBodyList.size(); i++)
	{
		Body* m = m_moleculeBodyList[i];
		if (method == "Backward Time-Driven")
			backtrackToWallCollision(m);
		//backtrackToWallCollision(m);
		if (m->getPosition().x - m->getSize().x <= m_containerBody->getPosition().x
			|| m->getPosition().x + m->getSize().x >= m_containerBody->getPosition().x + m_containerBody->getSize().x)
		{
			//printf("Molécule %d est en collision horizontale avec le conteneur.\n", i);
			m->setVelocity({ -m->getVelocity().x, m->getVelocity().y });
		}
		else if (m->getPosition().y - m->getSize().y <= m_containerBody->getPosition().y
			|| m->getPosition().y + m->getSize().y >= m_containerBody->getPosition().y + m_containerBody->getSize().y)
		{
			//printf("Molécule %d est en collision verticale avec le conteneur.\n", i);
			m->setVelocity({ m->getVelocity().x, -m->getVelocity().y });
		}
	}
}

void Physics::updateMoleculesCollisions(std::string method)
{/*
	for (int i = 0; i < m_moleculeBodyList.size(); i++)
	{
		std::vector<sf::Vector2f> boundaries1 = m_moleculeBodyList[i]->getBoundaries();
		for (int j = i + 1; j < m_moleculeBodyList.size(); j++)
		{
			std::vector<sf::Vector2f> boundaries2 = m_moleculeBodyList[j]->getBoundaries();
			for (auto b1 : boundaries1)
			{
				for (auto b2 : boundaries2)
				{
					if ((sf::Vector2i)b1 == (sf::Vector2i)b2)
					{
						printf("Collisions entre molécule %d et molécule %d.\n", i, j);
						m_moleculeBodyList[i]->setVelocity({ 0, 0 });
						m_moleculeBodyList[j]->setVelocity({ 0, 0 });
						return ; // arrêter les deux boucles dès qu'il y a une collision, pour passer à la prochaine molécule
					}
				}
			}
		}
	}*/
	for (int i = 0; i < m_moleculeBodyList.size(); i++)
	{
		Body* mol1 = m_moleculeBodyList[i];
		for (int j = i + 1; j < m_moleculeBodyList.size(); j++)
		{
			Body* mol2 = m_moleculeBodyList[j];
			if (distanceBetweenMolecules(mol1, mol2) <= 0) // true
			{
				if (method == "Backward Time-Driven")
					backtrackToCollision(mol1, mol2);
				//backtrackToCollision(mol1, mol2);
				//printf("Collisions entre molécule %d et molécule %d.\n", i, j);
				computeNewVelocities(mol1, mol2);
			}
		}
	}
}

void Physics::update(float deltaTime, std::string method)
{
	auto motion = [&]() -> void // mets à jour vitesses et positions des molécules
	{
		for (auto& molecule : m_moleculeBodyList)
		{
			molecule->setVelocity(molecule->getVelocity() + molecule->getAcceleration() * deltaTime);
			molecule->setPosition(molecule->getPosition() + molecule->getVelocity() * deltaTime);

			if (method == "Backward Time-Driven")
				backtrackToWallCollision(molecule);
		}
	};

	if (method == "Forward Time-Driven" || method == "Backward Time-Driven")
	{
		// Déteciton des collisions puis mise à jour des vélocités en conséquence
		updateMapCollisions(method);
		updateMoleculesCollisions(method);
		// Mets à jour les positions
		motion();
	}

	else if (method == "Event-Driven")
	{
		if (m_nextEvent != nullptr) // si ce n'est pas la première itération
		{
			if (m_nextEvent->wall == false)
				computeNewVelocities(m_nextEvent->body1, m_nextEvent->body2);
			else
				updateMapCollisions(method);
		}
		computeNextEvents();
		deltaTime = m_nextEvent->time;
		//printf("Next event time : %f : ", deltaTime);
		//printf("Wall? : %d\n", m_nextEvent->wall);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		// Mets à jour les positions
		motion();
	}
}

void Physics::setMoleculeBodyList(std::vector<Body*> moleculeBodyList)
{
	m_moleculeBodyList = moleculeBodyList;
}

const std::vector<Body*> Physics::getMoleculeBodyList() const
{
	return m_moleculeBodyList;
}
