#ifndef __SOMEONE__
    #define __SOMEONE__
    #include <string>

/*
    Classe abstraite : classe où il est impossible de créer des objets
    Pour instancier une classe abstraite, il faut qu'au moin une méthode soit virtuelle pure, avec un = 0 à la fin, pour représenter la valeur nulle

    Interface : toutes ses méthodes sont virtuelles pures

    Si une interface/classe abstraite est implémenté, il est obligé de redéfinir toutes les méthodes virtuelles pures dans d'autre sous-classes
*/

    class Someone // classe abstraite
    {
        public:
            Someone() = delete;
            Someone(const std::string& name) noexcept;
            // virtual ~Someone() = 0; quand on initialise une méthode virtuel, il est mieux d'aussi initialisé une déstructeur virtuel, pour que ça soit aux sous-classes de se charger de sa destruction
            virtual void sayGoodNight() const noexcept = 0; // définie la méthode en tant que virtual, elle pourra être réutilisé de manière indépendante dans d'autres classes enfants
            // le = 0 permet de rendre cette méthode virtuel pure, la méthode n'a donc plus besoin de faire une action spécifique pour cette classe abstaite

        protected: // Protected autorise l'accès à ces attributs, pour la classe principale 'Someone' et toutes ses sous-classe, alors que 'private' ne l'autorise que pour la classe principale
            std::string _name;
    };

#endif