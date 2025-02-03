#include "window.hpp"
#include <iostream>
#include <string>

Window::Window(std::string t, int w, int h) : title(t), width(w), height(h) // dans l'attribut 'title' de ma classe Window, j'injecte le contenue de la variable 't', etc
// Window::Window() noexcept, dans le cas où on est certain qu'il n'y aura pas d'exception levé
{
    // title(t) est équivalent à this->title = t;
}

void Window::run() const noexcept// implémentation de le méthode (fonction) run
{
    std::cout << "Affichage..." << std::endl;
}