#include <iostream>
#include <limits>
#include <string>
#include <fstream>

struct InfoPerso
{
    std::string prenom;
    std::string nom;
    std::string sexe;
    int age;
};

template<typename T>
void safeInput(T & value)
{
    while(!(std::cin >> value))
    {
        std::cout << "Entrée invalide." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

template<typename T, typename Predicat>
void safeInput(T & value, Predicat predicat)
{
    while(!(std::cin >> value) || !predicat(value)) // tant que la valeur ne peut pas être contenue dans la variable 'value' (même type) et qu'elle respecte pas le prédicat d'être >= 0
    {
        std::cout << "Entrée invalide." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

InfoPerso askInfo()
{
    InfoPerso info{};

    std::cout << "Prénom ? ";
    safeInput(info.prenom);
    std::cout << "Nom ? ";
    safeInput(info.nom);
    std::cout << "Sexe ? ";
    safeInput(info.sexe);
    std::cout << "Age ? ";
    safeInput(info.age, [](int & age) {return age >= 0;}); // fonction lambda de paramètre 'info.age' qui permet de vérifier si l'age est >= 0

    return info;
}

std::string saveInfo(const InfoPerso& info)
{
    std::string fileName = info.prenom + '.' + info.nom + ".csv";
    std::ofstream write{fileName};
    write << info.prenom << "," << info.nom << "," << info.sexe << "," << info.age;

    return fileName;
}

int main()
{
    auto info = askInfo();

    std::cout << std::endl << " Ces données seront enregistrés dans le fichier : " << saveInfo(info);

    return 0;
}