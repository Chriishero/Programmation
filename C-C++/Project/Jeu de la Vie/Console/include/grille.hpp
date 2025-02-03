#ifndef __GRILLE__
    #define __GRILLE__

    #include <vector>
    #include <ostream>

    class Grille
    {
        public:
            Grille(int height, int width) noexcept;
            void showGrille() const noexcept;

            void testAroundCase(int h, int w, int& Ncells_around, char state);
            void detectCells() noexcept;
            void killCell(int ligne, int colonne) noexcept;
            void reanimateCell(int ligne, int colonne) noexcept;

            char& operator()(int ligne, int colonne);

        private:
            int n_height;
            int n_width;

            std::vector<char> n_grille;

        friend std::ostream& operator<<(std::ostream& os, Grille& g);
    };

#endif