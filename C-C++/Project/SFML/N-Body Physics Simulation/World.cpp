#include "World.h"

World::World(int nBody) : m_nBody(nBody)
{
}

void World::create()
{
	for (int i = 0; i < m_nBody; i++) {
		if(m_vecBody.empty())
			m_body = new Body(50, sf::Vector2f(1200/2, 920/2), sf::Vector2f(1.0f, 1.0f), 10);
		else {
			auto prevPosition = m_vecBody[i - 1]->getm_position();
			auto prevSize = m_vecBody[i - 1]->getm_size();

			m_body = new Body(prevSize, sf::Vector2f(prevPosition.x + prevSize, prevPosition.y + prevSize), 
							sf::Vector2f(1.0f, 1.0f), 10);
		}
		m_body->begin();
		m_vecBody.push_back(m_body);
	}
}

void World::setGui(tgui::GuiSFML& gui)
{
	m_r1Temp = m_vecBody[0]->getm_size();
	m_r2Temp = m_vecBody[1]->getm_size();
	m_x1Temp = m_vecBody[0]->getm_position().x;
	m_x2Temp = m_vecBody[1]->getm_position().x;
	m_y1Temp = m_vecBody[0]->getm_position().y;
	m_y2Temp = m_vecBody[1]->getm_position().y;
	m_dx1Temp = m_vecBody[0]->getm_velocity().x;
	m_dx2Temp = m_vecBody[1]->getm_velocity().x;
	m_dy1Temp = m_vecBody[0]->getm_velocity().y;
	m_dy2Temp = m_vecBody[1]->getm_velocity().y;
	m_m1Temp = m_vecBody[0]->getm_weight();
	m_m2Temp = m_vecBody[1]->getm_weight();

	std::vector<std::shared_ptr<tgui::Slider>> sliderVec{};
	std::vector<float*> varVec{&m_r1Temp, &m_r2Temp, &m_x1Temp, &m_x2Temp, &m_y1Temp, &m_y2Temp, 
								& m_dx1Temp,& m_dx2Temp,& m_dy1Temp,& m_dy2Temp,& m_m1Temp,& m_m2Temp };
	std::vector<std::string> nameVarVec{ "r1", "r2", "x1", "x2", "y1", "y2", "dx1", "dx2", "dy1", "dy2", "m1", "m2" };

	for (int i = 0; i < varVec.size() / 2; i++) {
		for (int j = 0; j < 2; j++) {
			int index = i * 2 + j;
			if (index >= varVec.size()) break;

			auto slider = tgui::Slider::create(0, 1000);
			slider->setValue(*varVec[index]);
			slider->setPosition({ 5 + 165 * j, 0 + 50 * i});
			slider->setSize({ 150, 20 });
			gui.add(slider);

			auto label = tgui::Label::create(nameVarVec[index]);
			label->setPosition({ 5 + 165 * j, 0 + 50 * i + 25 });
			gui.add(label);

			slider->onValueChange([label, ptr = varVec[index], name = nameVarVec[index], i, j](float value) {
				label->setText(name + ": " + std::to_string(value));
				*ptr = value;
			});
		}
	}
	auto button = tgui::Button::create("Update");
	button->setPosition({ 0, 25 * (varVec.size() + 1)});
	button->setSize({ 200, 40 });
	gui.add(button);
	button->onPress([=]() {
		m_vecBody[0]->setm_size(m_r1Temp);
		m_vecBody[1]->setm_size(m_r2Temp);
		m_vecBody[0]->setm_position(sf::Vector2f(m_x1Temp, m_y1Temp));
		m_vecBody[1]->setm_position(sf::Vector2f(m_x2Temp, m_y2Temp));
		m_vecBody[0]->setm_velocity(sf::Vector2f(m_dx1Temp, m_dy1Temp));
		m_vecBody[1]->setm_velocity(sf::Vector2f(m_dx2Temp, m_dy2Temp));
		m_vecBody[0]->setm_weight(m_m1Temp);
		m_vecBody[1]->setm_weight(m_m2Temp);
		m_vecBody[0]->begin();
		m_vecBody[1]->begin();
	});
}

void World::motion()
{
	float r1 = m_vecBody[0]->getm_size();
	float r2 = m_vecBody[1]->getm_size();
	float x1 = m_vecBody[0]->getm_position().x;
	float x2 = m_vecBody[1]->getm_position().x;
	float y1 = m_vecBody[0]->getm_position().y;
	float y2 = m_vecBody[1]->getm_position().y;
	float dx1 = m_vecBody[0]->getm_velocity().x;
	float dx2 = m_vecBody[1]->getm_velocity().x;
	float dy1 = m_vecBody[0]->getm_velocity().y;
	float dy2 = m_vecBody[1]->getm_velocity().y;
	float m1 = m_vecBody[0]->getm_weight();
	float m2 = m_vecBody[1]->getm_weight();
	
}

void World::update(float deltaTime)
{
	motion();
	for (int i = 0; i < m_nBody; i++) {
		m_vecBody[i]->update(deltaTime);
	}
}

void World::render(Renderer& renderer)
{
	for (int i = 0; i < m_nBody; i++) {
		m_vecBody[i]->render(renderer);
	}
}
