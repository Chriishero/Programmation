#ifndef __POINT__
    #define __POINT__

    /*
        struct : données publiques (par défaut)
            Utile pour un regroupement de données
        class : données privées (par défaut)
            Utile s'il y a des vérifications à faire

        Niveaux d'accès : public, private, protected
    */

    class Point // une classe équivaut à un boîte noire
    {
        public:
            Point(); // constructeur
            // Point(const Point& p); constructeur de copie qui fait référence au constructeur Point();
            // Point(Point&& p); constructeur de déplacement : transmet la responsabilité des données à une autre variable sans effectuer de copie
            ~Point(); // destructeur
    };

#endif