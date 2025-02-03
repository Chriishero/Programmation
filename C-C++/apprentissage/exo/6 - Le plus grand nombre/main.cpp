#include <iostream>
#include <array>
#include <algorithm>

int main()
{
    std::array<double, 3> n_array{};

    std::cout << "Entrez 3 nombres (a,b,c) : ";
    std::cin >> n_array[0];
    std::cin.ignore(255, ',');
    std::cin >> n_array[1];
    std::cin.ignore(255, ',');
    std::cin >> n_array[2];

    std::sort(std::begin(n_array), std::end(n_array));

    std::cout << "Le plus grand nombre est : " << n_array.back() << std::endl;

    return 0;
}