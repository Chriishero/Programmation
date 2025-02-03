#include "employe.hpp"
#include <iostream>
#include <string>

Employe::Employe(std::string last_name, std::string first_name, double salary) noexcept : _last_name(last_name), _first_name(first_name), _salary(salary)
{}

std::string Employe::get_first_name() const noexcept
{
   return _first_name; 
}

double Employe::get_salary() const noexcept
{
   return _salary; 
}

std::ostream& operator<<(std::ostream& os, const Employe& e) noexcept
{
    os << "Last Name : " << e._last_name << "\nFirst Name : " << e._first_name << "\nSalary : " << e._salary << "e";
    return os;
}

bool operator==(const Employe& e, const Employe& other) noexcept
{
    return e._salary == other._salary;
}

bool operator!=(const Employe& e, const Employe& other) noexcept
{
    return !(e._salary == other._salary);
}

bool operator>(const Employe& e, const Employe& other) noexcept
{
    return e._salary > other._salary;
}

bool operator<(const Employe& e, const Employe& other) noexcept
{
    return !(e._salary > other._salary);
}

bool salary_sort(const Employe& e, const Employe& other) noexcept // cette fonction de comparaison permettra de donner à std::sort, la règle de trier par salaire en utilisant l'opérateur '>'
{
    return e.get_salary() > other.get_salary();
}