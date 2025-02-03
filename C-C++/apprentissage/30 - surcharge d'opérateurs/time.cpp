#include "time.hpp"
#include <iostream>

/*
    bool operator==(a, b){...}

    bool operator!=(a, b)
    {
        return !(a == b);
    }

    a <= b -----> a < b || a == b
    a >= b -----> !(a < b)
    a + b  -----> a += b
    
    si < surchargé, alors > est rapide à surcharger
*/

namespace jc
{
    Time::Time(std::size_t hours, std::size_t minutes, std::size_t secondes) noexcept : _hours(hours), _minutes(minutes), _secondes(secondes)
    {}

    Time Time::operator+(const Time& other) const // l'opérateur est issu de la classe 'Time', donc 'Time::operator+()'
    {
        return Time{_hours + other._hours, _minutes + other._minutes, _secondes + other._secondes}; // renvoie une valeur de temps 'Time'
    }

    Time operator+(const Time& t, int i) // permet l'ajoute d'une variable de type primitif à l'objet de type personnalisé
    {
        return Time{t._hours + i, t._minutes + i, t._secondes + i};
    }

    Time operator+(int i, const Time& t)
    {
        return t + i; // écris cela suffit, car 'i + t' revient à faire 't + i' et on a déjà définie l'opération inverse avec l'opérateur '+' juste avant
    }

    std::ostream& operator<<(std::ostream& os, const Time& t) // en dehors de la class, donc on écrit pas Time::operator<<()
    {
        os << t._hours << ':' << t._minutes << ':' << t._secondes; // renvoie vers le flux de sortie 'os <<'
        return os; 
    }
}
