#include <iostream>
#include <string>
#include <stack>

/*
    Pile : conteneur de type LIFO, ensemble d'élément qu'on peut ajouter (empiler) et retirer (dépiler),
           dernier élement ajouté = premier à pouvoir être retirer de la pile.

    Seul le dernier élément inséré peut être lu ou retiré.

    size(), empty(), 
    push(), top(), pop()

    Il est impossible d'itérer tous les élément de la pile avec :
        for(const auto& element : stack){}
    Mais il est possible de le faire avec : 
        while(!stack.empty())
        {
            stack.top();
            stack.pop();
        }

*/

int main()
{
    std::stack<int> st;

    st.push(1); // Insére (empile) l'élément '1' en haut de la pile.
    std::cout << "Top : " << st.top() << std::endl; // top() permet d'afficher l'élément qui se trouve tout en haut de la pile

    st.push(55);
    std::cout << "Top : " << st.top() << std::endl;

    st.pop(); // Retire le dernier élément inséré sur la pile

    std::cout << "Taille : " << st.size() << std::endl;

    if(st.empty()) // si la pile est vide
    {
        std::cout << "La pile est vide." << std::endl;
    }

    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    st.push(6);
    st.push(7);

    while(!st.empty()) // Tant que la pile n'est pas vide
    {
        std::cout << st.top() << " "; // afficher l'élément tout en haut de la pile 'top()'
        st.pop();
    }

    return 0;
}