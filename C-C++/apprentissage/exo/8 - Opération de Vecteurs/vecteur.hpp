#ifndef __VECTEUR__
    #define __VECTEUR__
    #include <ostream>
    #include <string>

    class Vecteur
    {
        public:
            Vecteur(std::string name, int x, int y, std::string direction, std::string sens) noexcept;

            Vecteur operator+(const Vecteur& other) const;
            Vecteur operator-(const Vecteur& other) const;
            double operator*(const Vecteur& other) const;
 
        private:
            std::string _name;
            int _x;
            int _y;
            std::string _direction;
            std::string _sens;
            double _norme;
            
        friend Vecteur operator*(const Vecteur& v, int k);
        friend Vecteur operator*(int k, const Vecteur& v);
        friend std::ostream& operator<<(std::ostream& os, const Vecteur& v);

    };

#endif