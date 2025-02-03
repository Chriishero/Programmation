
#include <iostream>
#include <string>
#include <array> // Entête pour implémenter les tableaux à taille fixe
#include <vector> // Entête pour implémenter les tableaux à taille dynamique

/*
    Tableau de taille fixe : stock un nombre fixe de valeurs
    Tableaux de taille dynamique : la taille du tableau va varier en fonction du nombre d'élément qu'il stock

    Méthode spécifique à std::array : 
      fill()  : Remplie le tableau avec un valeur spécifique
      at()    : Fait la même chose que les '[]' pour spéficier un indice
      size()  : récupère la taille du tableau
      empty() : vérifie si le tableau est vide
      front() : renvoie le premier élément
      back()  : renvoie le dernier élément
      push_back()  : ajoute un élément à la fin
      push_front() : ajoute un élément au début
      pop_back()   : retire le dernier élément
      pop_front()  : retire le premier élément
      clear()      : efface tout le contenu du tableau

     vector.erase(vector.begin() + index) : efface l'élément du tableau associé à l'index   

    Méthode libre de la bibliothèque standard :
      std::size(), std::empty()

*/

int main()
{
    std::vector<std::string> arr_vector{"Hi"};
    arr_vector.push_back("Bonjour");

    std::array<int, 5> arr{1, 2, 3, 4, 5}; // le '5' définie le nombre de valeur que pourra stocker le tableau

    for(const auto& element : arr)
    {
        std::cout << element << std::endl;
    }

    arr.fill(2);

    for(size_t i{0}; i < arr.size(); i++) // Fait la même chose que la boucle for précedente en utlisant la méthode size() qui récupère la taille du tableau
    // arr.size() est équivalent à std::size(arr)
    {
        std::cout << arr[i] << std::endl;
    }

    std::cout << "Premier element du tableau : " << arr[0] << std::endl; // les '[]' permettent de spécifier l'indice de l'élément du tableau qu'on veut renvoyer, ici le premier (0)
    arr[0] = 10; // modifie un élément du tableau à partir de son indice
    std::cout << "Premier element du tableau : " << arr[0] << std::endl;

    return 0;
}