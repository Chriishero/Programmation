#include "vecteur.hpp"
#include <iostream>
#include <string>
#include <cmath> // inclue des opérations mathématique tel que la racine carré

Vecteur::Vecteur(std::string name, int x, int y, std::string direction, std::string sens) noexcept : _name(name), _x(x), _y(y), _direction(direction), _sens(sens)
{
    _norme = sqrt(_x*_x + _y*_y);
}

Vecteur Vecteur::operator+(const Vecteur& other) const
{
    int x = other._x - _x;
    int y = other._y - _y;

    std::cout << _name << " + " << other._name << " =" << std::endl;

    if ((_direction == "horizontal" && other._direction == "vertical") || (_direction == "vertical" && other._direction == "horizontal") || _direction == "diagonal" || other._direction == "diagonal")
    {
        if (sqrt(_x*_x + _y*_y) < 0)
        {
            Vecteur show{_name + other._name, x, y, "diagonal", "bas"};
            return show;
        }
        else
        {
            Vecteur show{_name + other._name, x, y, "diagonal", "haut"};
            return show;
        } 
    }
    else
    {
        if (_direction == "horizontal")
        {
            if (sqrt(x*x + y*y) < 0)
            {
                Vecteur show{_name + other._name, x, y, _direction, "gauche"};
                return show;
            }
            else
            {
                Vecteur show{_name + other._name, x, y, _direction, "droite"};
                return show;
            } 
        }
        else
        {
            if (sqrt(x*x + y*y) < 0)
            {
                Vecteur show{_name + other._name, x, y, _direction, "bas"};
                return show;
            }
            else
            {
                Vecteur show{_name + other._name, x, y, _direction, "haut"};
                return show;
            }
        }
        
    }
}

Vecteur Vecteur::operator-(const Vecteur& other) const
{
    int x = _x - other._x;
    int y = _y - other._y;

    std::cout << _name << " - " << other._name << " =" << std::endl;

    if ((_direction == "horizontal" && other._direction == "vertical") || (_direction == "vertical" && other._direction == "horizontal") || _direction == "diagonal" || other._direction == "diagonal")
    {
        if (sqrt(_x*_x + _y*_y) < 0)
        {
            Vecteur show{_name + other._name, x, y, "diagonal", "bas"};
            return show;
        }
        else
        {
            Vecteur show{_name + other._name, x, y, "diagonal", "haut"};
            return show;
        } 
    }
    else
    {
        if (_direction == "horizontal")
        {
            if (sqrt(x*x + y*y) < 0)
            {
                Vecteur show{_name + other._name, x, y, _direction, "gauche"};
                return show;
            }
            else
            {
                Vecteur show{_name + other._name, x, y, _direction, "droite"};
                return show;
            } 
        }
        else
        {
            if (sqrt(x*x + y*y) < 0)
            {
                Vecteur show{_name + other._name, x, y, _direction, "bas"};
                return show;
            }
            else
            {
                Vecteur show{_name + other._name, x, y, _direction, "haut"};
                return show;
            }
        }
        
    }
}

double Vecteur::operator*(const Vecteur& other) const
{
    std::cout << "Produit scalaire entre " << _name << " et " << other._name << " : " << std::endl;
    std::cout << _x << " * " << other._y << " + " << other._x << " * " << _y << " = ";
    return _x * other._y + other._x * _y;
}

Vecteur operator*(const Vecteur& v, int k)
{
    std::string sens = "";

    std::cout << v._name << " * " << k << "=" << std::endl;

    if(k > 0)
    {
        sens = v._sens;
    }
    else if(k < 0)
    {
        if (v._sens == "bas")
        {
            sens = "haut";
        }
        else if (v._sens == "haut")
        {
            sens = "bas";
        }
        else if (v._sens == "droite")
        {
            sens = "gauche";
        }
        else if (v._sens == "gauche")
        {
            sens = "droite";
        }
    }
    return Vecteur{v._name + "k", v._x * k, v._y * k, v._direction, sens};
}

Vecteur operator*(int k, const Vecteur& v)
{
    return v * k;
}

std::ostream& operator<<(std::ostream& os, const Vecteur& v)
{   
    os << "Nom : " << v._name << "\nCoordonnees : " << "(" << v._x << "," << v._y << ")" <<"\nNorme : " << v._norme << "\nDirection : " << v._direction << "\nSens : " << v._sens;
    return os;
}