#include <iostream>
#include <string>

/* 
    break : arrête la boucle, peu importe l'état de la vérification while
    continue : continue la boucle, sans prendre en compte les instructions suivantes
*/

int main()
{
    std::string sentence{"Hello world"};

    for(const auto letter : sentence) // Pour chaque "letter" de "sentence"
    {
        std::cout << letter << std::endl;
    }

    for (auto i = 0; i < 10; i++) // fait exactement la même chose qu'une boucle while
    {
        std::cout << "i vaut : " << i << std::endl;
    }
    
    return 0;
}