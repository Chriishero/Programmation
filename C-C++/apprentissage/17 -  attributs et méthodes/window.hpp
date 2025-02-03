#ifndef __WINDOW__
    #define __WINDOW__
    
    #include <string>

/*
    Attribut : variable retrouvé dans une classe
    Méthode : fonction inscrite dans une classe
    Le constructeur est une fonction/méthode, qui peut donc posséder des paramètres

    Autant de constructeur qu'on veut peuvent être implémenté

    Mettre le plus possible d'info, comme des const et noexcept, pour être certain de pas en oublier, au risque d'en mettre en trop et de devoir les supprimer

*/

    class Window
    {
        public:
            Window() = default; // constructeur par défaut implicite, il n'est donc plus possible de s'occuper du constructeur avec Window::Window(){ }
            Window(std::string t, int w, int h); // constructeur avec des paramètres
            // Window() noexcept, dans le cas où on est certain qu'il n'y aura pas d'exception levé (string peut en lever sauf si elle est constante)
            void run() const noexcept; // création d'une méthode 'run' constante

        private: // les informations privées ne sont pas accessible, avec par exemple : std::cout << app.title; dans le script main
            std::string title; // attribut (variable) privé de la fonction 'Window'
            int width;
            int height;
    };

#endif