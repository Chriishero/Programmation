#ifndef __LABYRINTHE__
    #define __LABYRINTHE__

    #include <vector>
    #include <ostream>

    class Labyrinthe
    {
        public:
            Labyrinthe(int height, int width) noexcept;

            void createLabyrinthe() noexcept;
            void solveLabyrinthe() noexcept;

            std::vector<int> getExitCase() const noexcept;
            std::vector<int> getStartCase() const noexcept;

            char& operator()(int height, int width);


        private:
            std::vector<char> n_grille;
            std::vector<int> n_exitCase;
            std::vector<int> n_startCase;

            std::vector<std::vector<int>> n_backPos;
            std::vector<std::vector<int>> n_markCase;

            int n_height;
            int n_width;

        friend std::ostream& operator<<(std::ostream& os, Labyrinthe& l);
    };
#endif

