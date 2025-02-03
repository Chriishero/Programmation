#include <iostream>

/*
> Écrire un programme de rendu de monnaie. En saisisssant le montant total des achats puis la somme 
  donnée, indiquer la monnaie à rendre (en billets de 20€, 10€, 5€ et pièces de 2€ et 1€)

> Indications : 
    - S'assurer que la somme donnée est bien supérieure à la somme des achats
    - Gérer le cas où on aurait payé un montant égal aux achats
    - Rendre le moins de billets/pièces possible (25€ de monnaie -> 1 billet de 20€ + 1 billet de 5€)
    - L'opérateur % (modulo) sera utile pour cet exercice

    14%10 = 4
*/

int main()
{
    bool monnaieToF{false};
    int monnaie_rendre;

    while (monnaieToF == false)
    {
        std::cout << "Saisissez le montant total de vos achats : ";
        int montantT{0};
        std::cin >> montantT;
        std::cin.ignore(255, '\n');

        std::cout << "Saisissez la somme donnee : ";
        int sommeD;
        std::cin >> sommeD;  

        if (sommeD > montantT)
        {
            monnaie_rendre = sommeD - montantT;
            std::cout << "La monnaie a rendre est de : " << monnaie_rendre << std::endl;
            
            int nbr_billet20{monnaie_rendre/20};
            if (nbr_billet20 > 0)
            {
                std::cout << nbr_billet20 << " billet(s) de 20e\n";
            }
            
            int nbr_billet10 = monnaie_rendre % 20 / 10;
            if (nbr_billet10 > 0)
            {
                std::cout << nbr_billet10 << " billet de 10e\n";
            }

            int nbr_billet5 = monnaie_rendre % 10 / 5;
            if (nbr_billet5 > 0)
            {
                std::cout << nbr_billet5 << " billet de 5e\n";
            }

            int nbr_2 = monnaie_rendre % 5 / 2;
            if (nbr_2 > 0)
            {
                std::cout << nbr_2 << " piece de 2e\n";
            }
            int nbr_1 = monnaie_rendre % 20 % 10 % 5 % 2 / 1;
            if (nbr_1 > 0)
            {
                std::cout << nbr_1 << " piece de 1e\n";
            }

            //std::cout << nbr_billet20 << " billet(s) de 20e\n" << nbr_billet10 << " billet de 10e\n" << nbr_billet5 << " billet de 5e\n" << nbr_2 << " piece(s) de 2e\n" << nbr_1 << " piece de 1e " << std::endl;

            break; 
             
        }
        
        else if (sommeD == montantT)
        {
            std::cout << "Vous avez donne le montant exact : " << sommeD << "e";
            break;
        }
        
        else
        {
            std::cout << "La somme donnee doit etre superieur au montant total des achats." << std::endl;
            continue;
        }
    }

    return 0;
}