#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> numbers { 2, 1, 52, 5, 100};

    if(std::any_of(std::begin(numbers), std::end(numbers), [](int number) -> bool{ return number < 0;})) // utilise une fonction lambda pour vérifier si un nombre est négatif
    {
        std::cout << "Au moins un nombre est négatif";
    }
    else{
        std::cout << "Tous les nombres sont positifs";
    }

    return 0;
}