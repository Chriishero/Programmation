#ifndef __JC_TIME__
    #define __JC_TIME__

    // #include <cstddef> // inclue le type std::size_t (pas nécessaire)
    #include <ostream> // inclue les types de flux comme std::ostream

    /*  
        Opérateurs de flux        : <<, >>
        Opérateurs arithmétique s  : +, -, *, /, %
        Opérateurs de comparaison : ==, !=, >, <, >=, <=        
        
        Opérateurs d'affectations intégrés : +=, -=, *=, /=, %=
        Pour ceux-là, il faudrait renvoyer une référence vers l'objet courant avec 'return *this'.

        type_retour operatorX(args);

        Amitié : autorisation exceptionnelle pour une fonction à accéder aux attributs privés de la classe
    */

    namespace jc
    {
        class Time
        {
            public:
                Time(std::size_t hours, std::size_t minutes, std::size_t secondes) noexcept;

                // Cette méthode de surcharge d'opérateur, définie comment le compilateur doit se comporter, si 2 objets sont additionné avec l'opérateur '+'
                Time operator+(const Time& other) const; // on travaille directement avec l'objet, donc la méthode de surcharge d'opérateur est définie DANS la classe
                // on renvoie une copie, car par référence, si on est sur des objets temporaires, on pourrait essayer d'accéder à des éléments supprimés

            private:
                std::size_t _hours;
                std::size_t _minutes;
                std::size_t _secondes;

            // La méthode doit être accessible depuis l'extérieur, donc elle n'est ni dans public, private ou protected
            friend std::ostream& operator<<(std::ostream& os, const Time& t); // 'friend' permet que dans le cas de cette méthode, on aura accès aux attributs privé de la classe 'Time'
            /*
            cette méthode renvoie le flux de sortie 'std::ostream' par référence '&', son nom est 'operator<<', l'opérateur en question est '<<', 
            qui prend en paramètre le flux 'std::ostream& os' et la donnée à passer dans le flux 'const Time& t'
            */ 

            friend Time operator+(const Time& t, int i); // définie comment faire pour l'ajoue d'un entier 'int i' au type personnalisé 'Time t'
            friend Time operator+(int i, const Time& t); // définie l'opération inverse, c'est nécessaire mathématiquement
        };
    }

#endif