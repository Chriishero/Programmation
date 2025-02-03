#ifndef __CERCLE__
    #define __CERCLE__
    #include "forme.hpp"

    class Cercle : public Forme
    {
        Cercle() = delete;

        public:
            Cercle(float rayon) noexcept;
            void aire() const noexcept override;

        protected:
            float _rayon;

    };

#endif