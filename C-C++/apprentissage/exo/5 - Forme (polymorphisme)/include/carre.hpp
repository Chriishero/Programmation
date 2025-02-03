#ifndef __CARRE__
    #define __CARRE__
    #include "forme.hpp"

    class Carre : public Forme
    {
        Carre() = delete;

        public:
            Carre(float cote) noexcept;
            void aire() const noexcept override;

        protected:
            float _cote;

    };

#endif