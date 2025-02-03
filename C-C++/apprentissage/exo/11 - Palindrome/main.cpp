#include <iostream>
#include <string>

int main()
{
    std::string word = "Chaos;HeaddaeH;soahC";

    std::string leftHalf { std::begin(word), std::end(word) - std::size(word)/2 };
    std::string rightHalf { std::begin(word) + std::size(word)/2, std::end(word)};
    std::string sortRightHalf { std::rbegin(rightHalf), std::rend(rightHalf) };
    
    if(leftHalf == sortRightHalf)
    {
        std::cout << word << " est un palindrome";
    }
    else
    {
        std::cout << word << " n'est pas un palindrome";
    }

    return 0;
}