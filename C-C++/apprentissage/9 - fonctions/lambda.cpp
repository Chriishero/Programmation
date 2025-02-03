#include <iostream> 

/*
    Une fonction lambda est utile pour une opération utilisé seulement localement, comme dans un std::find_if.
    Elle peut-être stocké dans une variable si nécessaire.

    [](paramètre) <spécificateurs> -> <type de retour> { };
    Cette fonction lambda, n'a pas accès au donné depuis l'extérieur, sans [paramètre de capture]
    'auto' peut être utilisé comme type de paramètres.

    [=]() <spécificateurs> -> <type de retour> { }; : TOUT est capturé (COPIE) uniquement accessible en lecture seul
    [=]() mutable -> <type de retour> { }; : TOUT est capturé (COPIE) modifiable
    [&]() mutable -> <type de retour> { }; : TOUT est capturé (RÉFÉRENCE) modifiable

    [var]  : var capturé par COPIE
    [&var] : var capturé par RÉFÉRENCE

    Tout est cumulable 
*/

int main()
{
    int n{10};
    int m{20};

    std::cout << n << " - " << m << std::endl;

    auto func = [&n, m]() mutable -> void 
    {  
        n -= 10;
        m -= 10; 
        std::cout << n << " - " << m << std::endl;
        
    };

    func();

    std::cout << n << " - " << m << std::endl;

    return 0;
}