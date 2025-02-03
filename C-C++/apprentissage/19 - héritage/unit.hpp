#ifndef __UNIT__
    #define __UNIT__
    #include <string>

    /*
    Classe A, Classe B
        Héritage : B est une sorte de A
        Composition : B fait parti de A

    'Character' est une sorte de 'Unit' : Héritag

    En héritage, une classe peut hériter de plusieurs classes et non d'une seule.
    */

    class Unit
    {
        public:
            Unit() = delete; // désactive le constructeur par défaut
            Unit(int id, const std::string& name) noexcept; // pour que le 'noexcept' fonctionne sur une variable 'string', elle doit être constante
            int get_id() const noexcept; // getter de l'attribut '_id'
            std::string get_name() const noexcept; // getter de l'attribut '_name'

        private:
            int _id;
            std::string _name;
    };

#endif