#include <iostream>
#include <string>

/* 
    std::cout << variable.lenght(); affiche la longueur de "variable"

    int n{15}; n <- 15
    int &refN{n}; refN <- n : & permet d'initialiser une référence
*/

void set_numbers(int& a, int& b); // permet de faire connaitre au compilateur l'existence de la fonction avant son initialisation, on peut donc l'appeler avant de l'avoir initialisé

void set_numbers(int& a, int& b) // & fais référence aux paramètres (n, m ici), donc n et m sont directement modifié, alors que sans le &, a et b ne serait que des COPIES de n et m
{
    a -= 6;
    b += 2;
}

int main()
{
    int n{5};
    int m{8};

    std::cout << n << " " << m << std::endl;

    set_numbers(n, m);

    std::cout << n << " " << m << std::endl;

    return 0;
}