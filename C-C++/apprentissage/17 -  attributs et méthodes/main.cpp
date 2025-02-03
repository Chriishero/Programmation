#include "window.hpp"
#include <iostream>

int main()
{
    Window app{"Mon programme GUI", 640, 480}; // appelle au constructeur avec paramètre (std::string t, int w, int h) dans l'objet 'app'

    app.run(); // Dans l'objet 'app' de la classe 'Window', j'appelle la méthode (fonction) 'run'

    return 0;
}