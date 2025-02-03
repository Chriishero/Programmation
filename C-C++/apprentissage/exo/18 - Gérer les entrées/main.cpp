#include <iostream>
#include <limits>

int main()
{
    auto response = [](auto& n, auto mini_value, auto max_value) -> void{
        while(!(std::cin >> n) || n < mini_value || n > max_value)
        {
            if(std::cin.eof())
            {
                throw std::runtime_error("Le flux a été fermé."); // jète une exception si le flux est fermé
            }
            else if(std::cin.fail()) // si l'opération ne peut pas être fait, comme une erreur de type
            {
                std::cout << "Entré invalide." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // définie la limite 'numeric_limits' de type 'streamsize' pour les flux, comme étant le max de '\n' que peut recevoir un flux
            }
            else
            {
                std::cout << "Ce doit être compris entre " << mini_value << " et " << max_value << std::endl;
            }
        }


    };

    int jour = 0;
    std::cout << "Quel jour es-tu né ? ";
    response(jour, 1, 31);

    int mois = 0;
    std::cout << "Quel mois ? ";
    response(mois, 1, 12);

    int annee = 0;
    std::cout << "Quelle année ? ";
    response(annee, 1900, 2024);

    double taille = 0;
    std::cout << "Quelle taille ? ";
    response(taille, 1.0, 3.0);

    std::cout << "Tu es né le " << jour << "/" << mois << "/" << annee << "et tu mesures " << taille << "m." << std::endl;

    return 0;
}