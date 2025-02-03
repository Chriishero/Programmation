#include <iostream>

/* 
    std::cout : affichage standard (en mémoire tampon, bufferisé)
    std::cerr : erreurs (affichage direct)
    std::clog : jounalisation (en mémoire tampon)

    std::endl : retour à la ligne (\n) + flush (vider et afficher la mémoire tampon
    std::flush

    \n : retour à la ligne 
    \t : tabulation
    \\ : afficher un antislash
*/
int main(){
    std::cout << "Hello World !" << std::endl; 
    std::cerr << "Hello Error !" << std::endl; 
    std::clog << "Hello Log !" << std::endl; 
    return 0;
}