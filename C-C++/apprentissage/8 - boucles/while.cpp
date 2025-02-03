#include <iostream>
#include <string>

/* 
    break : arrête la boucle, peu importe l'état de la vérification while
    continue : continue la boucle, sans prendre en compte les instructions suivantes
*/

int main()
{
    std::string sentence{"Hello world"};
    int i{0};

    /* 
    do {
        std::cout << sentence << std::endl;
        i++;  
    }
    while(i < 10);
    Ici, l'instruction sera d'abord effectué avec que la boucle ne fasse la vérification
    */

    while(i < 10)
    {
        std::cout << i << std::endl;
        i++;
    }

    return 0;
}