#include <iostream>

/*
Pointeur Brut

    Faire référence avec '&' permet en fait de pointer vers la variable.

    Pour initialiser un pointeur, il faut utiliser un '*' : 
    int* n;
    int * n;
    int *n;

    Une variable est une information stocké en mémoire, alors qu'un pointeur stock l'adresse d'une autre variable.

    Une référence doit forcément référencer une variable, alors qu'un pointeur peut être null à sa déclaration, et on peut aussi changer ce sur quoi il pointe.
*/

void change_value(int* m) // le paramètre m pointe directement vers la variable qui sera utilisé
{
    *m = 77; // change la valeur de la variable pointé, le '*' est nécessaire
}

int main()
{
    int n = 38;
    int* pN = &n; // Le pointeur 'Pn' pointe à 'n' depuis son adresse avec '&'.

    int* ptr = nullptr; // déclare un pointeur null
    int m = 35;
    ptr = &m; // Le pointeur pointe sur l'adresse de n, on utlise donc pas de '*'

    std::cout << *ptr << std::endl;

    change_value(&n); // on doit passer par adresse la variable, car un pointeur contient une adresse

    std::cout << "n : " << n << std::endl;
    std::cout << "&n : " << &n << std::endl; // affiche l'adresse de la variable 'n' référencé avec '&'
    std::cout << "pN : " << pN << std::endl; // affiche l'adresse de la variable pointé, 'n' depuis le pointeur 'Pn'
    std::cout << "&pN : " << &pN << std::endl; // affiche l'adresse du pointeur 'pN' avec '&'
    std::cout << "*pN : " << *pN << std::endl; // avec le '*', on affiche la valeur de la variable pointé 'n' en déréférencant le pointeur

    return 0;
}