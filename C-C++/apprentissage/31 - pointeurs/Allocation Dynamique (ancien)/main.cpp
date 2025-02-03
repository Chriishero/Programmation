#include <iostream>

/*
    L'allocation dynamique permet d'allouer de la mémoire et de la rendre pour éviter les fuites de mémoires (mémoires qui restent dans la RAM et peut s'accumuler).

    new : alloue la mémoire en calculant automatiquement le nombre d'octet à allouer
    del : rend la mémoire
*/

void displayArray(int* array, int size)
{
    for (auto i = 0; i < size; i++)
    {
        std::cout << array[i] << std::endl;
    }
}

int main()
{
    int number = 0;
    std::cin >> number;
    std::cin.ignore(); // ignore le retour à la ligne

    int* array = new int[number]; // alloue 'number' fois un entier pour ce tableau de taille 'number'

    for (auto i = 0; i < number; i++)
    {
        array[i] = i;
    }
    
    displayArray(array, number);

    std::cin.ignore();

    delete[] array; // les '[]' sont nécessaire si ils ont été utilisé pour l'allocation

    return 0;
}