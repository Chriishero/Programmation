#ifndef __TRIANGLE__
    #define __TRIANGLE__
    #include "forme.hpp"

    class Triangle : public Forme
    {
        Triangle() = delete;

        public:
            Triangle(float base, float hauteur) noexcept;
            void aire() const noexcept override;

        protected:
            float _base;
            float _hauteur;

    };

#endif