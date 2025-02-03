#ifndef __ENGLISH__
    #define __ENGLISH__
    #include "someone.hpp"
    #include <string>

    class English : public Someone
    {
        using Someone::Someone; // utilisation de tous les attributs et méthode de la classe parent 'Someone'

        public : 
            void sayGoodNight() const noexcept override; // override permet de reféfinir la méthode 'sayGoodNight()' déjà initialisé en tant que méthode virtuel dans 'Someone'
            // il est impossible de changer la signature de la méthode virtuel de base, les mêmes paramètre doivent être mis
    };

#endif