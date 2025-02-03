#include "window.hpp"
#include <iostream>
#include <string>

Window::Window(std::string title) : _title(title)
{
}

std::string Window::get_title() const // Accesseur de l'attribut privé '_title'
{
    return this->_title; // this fait référence à l'instance courante en accédant à l'attribut privé '_title'
}

void Window::set_title(std::string title)
{
    if (title.length() > 20) // si la longueur du titre est > 20
    {
        throw std::invalid_argument("Le nom de la fenêtre est trop long et doit comporter 20 caractères maximum"); // lève une exception si le if est vérifié
    }
    
    this->_title = title; // dans l'attribut privé '_title', j'injecte le contenue de la variable title
}