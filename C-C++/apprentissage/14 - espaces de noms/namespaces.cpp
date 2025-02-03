#include "utils.hpp" // le code doit compiler *.cpp 
#include <iostream>

/* 
  Un espace de nom sert à organiser son code
  
  std:: est l'espace de nom qui globalise l'ensemble de la bibliothéque standard du C++

  namespace 
  {

  } Permet de créer un espace de nom statique, qui est propre à ce fichier uniquement

  using namespace std::cout; Permet d'utiliser seulement cout << ""; en masquant l'espace de nom std

  Possibilité d'imbriquer les espaces de noms : 
  namespace nameA 
  {
    namespace nameB
    {

    }
  }

  inline namespace name{} donnée membre
*/

int main()
{
    Util::test();
    Util::subUtil::test2();

    return 0;
}