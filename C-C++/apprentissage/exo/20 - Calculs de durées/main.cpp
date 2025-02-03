#include <iostream>
#include <string>
#include <tuple>

struct Duree{
    int secondes;
};

Duree setDuree(int secondes, int minutes, int heures)
{
    return Duree{secondes + minutes * 60 + heures * 3600};
}

int getSecondes(Duree d)
{
    return d.secondes;
}

std::tuple<int, int> getMinutes(Duree d)
{
    return std::make_tuple(d.secondes / 60, d.secondes % 60);
}

std::tuple<int, int, int> getHeures(Duree d)
{
    int heures = d.secondes / 3600;
    int minutes = d.secondes % 3600 / 60;
    int secondes = d.secondes % 3600 % 60;
    return std::make_tuple(heures, minutes, secondes); 
}

Duree operator+(const Duree& d, const Duree& d2)
{
    return Duree{d.secondes + d2.secondes};
}
Duree operator-(const Duree &d)
{
    return Duree{-d.secondes};
}
Duree operator-(const Duree &d, const Duree &d2)
{
    return d + (-d2);
}

bool operator==(const Duree &d, const Duree &d2)
{
    return d.secondes == d2.secondes;
}
bool operator!=(const Duree &d, const Duree &d2)
{
    return !(d == d2);
}
bool operator>(const Duree &d, const Duree &d2)
{
    return d.secondes > d2.secondes;
}
bool operator<(const Duree &d, const Duree &d2)
{
    return d.secondes < d2.secondes;
}
bool operator>=(const Duree &d, const Duree &d2)
{
    return d > d2 || d == d2;
}
bool operator<=(const Duree &d, const Duree &d2)
{
    return !(d > d2);
}
std::ostream& operator<<(std::ostream& os, const Duree &d)
{
    auto [heures, minutes, secondes] = getHeures(d);
    return os << std::to_string(heures) << ":" << std::to_string(minutes) << "'" << std::to_string(secondes) << '"';
}


int main()
{
    Duree d = setDuree(36, 10, 0);
    Duree d2 = setDuree(50, 23, 2);

    std::cout << d << std::endl;
    std::cout << d2 << std::endl;
    std::cout << d + d2 << std::endl;
    std::cout << d2 - d << std::endl;

    if(d < d2)
    {
        std::cout << d << " est plus petit que " << d2;
    }

    return 0;
}