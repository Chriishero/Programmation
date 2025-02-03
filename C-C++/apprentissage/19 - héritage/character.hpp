#ifndef __CHARACTER__
    #define __CHARACTER_
    #include "unit.hpp" // inclure la classe parent
    #include <string>

    /*
    Classe A, Classe B
        Héritage : B est une sorte de A
        Composition : B fait parti de A

    'Character' est une sorte de 'Unit' : Héritage

    En héritage, une classe peut hériter de plusieurs classes et non d'une seule.

    Class B : public A{} : Les éléments publiques de la classe parente 'A', le seront également dans la classe enfant 'B'
    Class B : protected A{} : Les éléments publiques de la classe parente 'A', deviendront privés dans la classe enfant 'B'
    */

    class Character : public Unit // La classe enfant 'Character' est dérivé de la classe parent 'Unit' et hérite de tous ses composants
    {
        using Unit::Unit; // indication explicite que 'Character' utilise tous les constructeurs de la classe 'Unit'

        public:
            Character() = delete; // désactive le constructeur par défaut
            Character(int id, const std::string& name, int level) noexcept; 
            int get_level() const noexcept;

        private:
            int _level; // seul cet attribut doit être initialisé, car 'Character' a hérité des attribut '_id' et '_name' de la classe parent 'Unit'
    };

#endif