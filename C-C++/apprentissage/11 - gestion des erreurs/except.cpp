#include <iostream>

int main()
{
    try // code qui pourrait déclencher l'exception
    {
        throw std::invalid_argument("Pas le bon argument"); // throw permet de déclencher une exception
        throw std::exception();
    }
    
    catch(const std::invalid_argument& err)
    {
        std::cout << err.what() << std::endl;
    }

    catch(const std::exception& err) // capture l'exception, std::type de l'exception (exception : tous les types d'exception) (variable, err ici)
    {
        std::cout << "Une erreur s'est produite." << std::endl;
    }


    return 0;
}