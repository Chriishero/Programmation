#ifndef __MATRICE__
    #define __MATRICE__

    #include <ostream>
    #include <vector>

    class Matrice
    {
        public:
            Matrice(int n_lignes, int n_colonnes) noexcept;

            void getSize() const noexcept;
            Matrice ligne(int n_ligne) noexcept;
            Matrice colonne(int n_colonne) noexcept;

            double& operator()(int ligne, int colonne);
            Matrice operator+=(Matrice& other);
            Matrice operator+(Matrice& other);

            Matrice operator*=(Matrice& other);
            Matrice operator*(Matrice& other);

            Matrice operator*=(int n);

        private:
            int m_n_lignes;
            int m_n_colonnes;
            std::vector<double> matrice;

        friend Matrice operator*(Matrice m, double n);

        friend std::ostream& operator<<(std::ostream& os, const Matrice& m);
    };

#endif