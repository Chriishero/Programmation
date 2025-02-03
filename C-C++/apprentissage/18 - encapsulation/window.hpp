#ifndef __WINDOW__
    #define __DEFINE__
    #include <string>

/*
    Accesseur (lecture) : 
     type GetterName() const;
     Un accesseur sert à rendre accessible en lecture un attribut privé, ex : sous une certaine condition, initialiser un accesseur

    Modificateur (écriture) : 
     type SetterName(attribut)
     Idem
*/

    class Window
    {
        public:
            Window(std::string title);
            std::string get_title() const; // on implémente les accesseur (lecture) avec un get, ce n'est pas obligatoire
            void set_title(const std::string title); // on implémente les modificateur (écriture) avec un set, ce n'est pas obligatoire
        private:
            std::string _title;
    };

#endif