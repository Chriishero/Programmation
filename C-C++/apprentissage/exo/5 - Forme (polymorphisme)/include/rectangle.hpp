#ifndef __RECTANGLE__
    #define __RECTANGLE__
    #include "forme.hpp"

    class Rectangle : public Forme
    {
        Rectangle() = delete;

        public:
            Rectangle(float longueur, float largeur) noexcept;
            void aire() const noexcept override;

        protected:
            float _longueur;
            float _largeur;

    };

#endif