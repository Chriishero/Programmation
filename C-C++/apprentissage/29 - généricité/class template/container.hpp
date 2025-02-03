#ifndef __CONTAINER__
    #define __CONTAINER__

    /*
        Le template est définie pour la classe entière.

        Un tableau statique 'std::array' est en fait une classe avec un template définie : 
            template<typename T, int N>
            avec N le nombre de case attribué pour le tableau.
    */

    template <typename T, typename U>
    class DataContainer
    {
        public:
            DataContainer(T n, U m) : _n(n), _m(m) {}; // on peut toujours utiliser un type classique, comme 'int', etc
            T getN() const noexcept { return _n; }
            U getM() const noexcept { return _m; }

        private:
            T _n;
            U _m;
    };

#endif