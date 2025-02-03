#include <iostream>
#include <string>
#include <tuple>
#include <fstream>
#include <limits>
#include <algorithm>
#include <vector>

std::vector<std::string> discographie;

void ajouterMorceaux(std::string commande)
{
    std::string morceau;
    std::string album;
    std::string artiste;

    std::string* ptr;
    auto begin = std::begin(commande);
    auto end = std::find(begin, std::end(commande), '|');

    auto i_barre = std::count(begin, std::end(commande), '|');

    for (auto i = 0; i < i_barre+1; i++)
    {
        switch (i)
        {
        case 0:
            ptr = &morceau;
            break;
        case 1:
            ptr = &album;
            break;
        
        case 2:
            ptr = &artiste;
            break;
        }
        
        *ptr = {begin, end};

        begin = ++end;
        end = std::find(begin, std::end(commande), '|');
    }
    if(morceau == " " || morceau == "")
    {
        morceau = "Morceau inconnu";
    }
    if(album == " " || album == "" || i_barre == 0)
    {
        album = "Album inconnu";
    }
    if(artiste == " " || artiste == "" || i_barre < 2)
    {
        artiste = "Artiste inconnu";
    }

    discographie.push_back(morceau);
    discographie.push_back(album);
    discographie.push_back(artiste);
}

void afficherDiscographie(std::string mode)
{
    if(mode == "morceaux")
    {
        std::vector<std::string> morceauxList;
        for (size_t i = 1; i < std::size(discographie)+1; i++)
        {
            if(i % 3 == 0)
            {
                std::string morceau = discographie[i-3] + " | " + discographie[i-2] + " | " + discographie[i-1];
                morceauxList.push_back(morceau);
            }
        }
        std::sort(std::begin(morceauxList), std::end(morceauxList));
        for (auto &&i : morceauxList)
        {
            std::cout << "--> ";
            std::cout << i << std::endl;
        }
    }
    else if (mode == "album")
    {
        std::vector<std::string> discographieAlbum;
        std::string album;
        bool is = false;

        for (size_t i = 1; i < std::size(discographie); i+=3)
        {
            for (auto &&a : discographieAlbum)
            {
               if(a.contains(discographie[i]))
               {
                    is = true;
                    album = a;
                    break;
               }
            }
            
            if(is == false)
            {
                album = "-->" + discographie[i] + "|" + discographie[i+1] + "\n  /--> " + discographie[i-1];
                discographieAlbum.push_back(album);
            }
            else
            {
                std::string newAlbum = album + "\n  /--> " + discographie[i-1];
                std::replace(std::begin(discographieAlbum), std::end(discographieAlbum), album, newAlbum);
                is = false;
            }
        }
        for (auto &&i : discographieAlbum)
        {
            std::cout << i << std::endl;
        }
    }
    else if (mode == "artiste")
    {
        std::vector<std::string> discographieArtist;
        std::string artist;
        bool is = false;

        for (size_t i = 2; i < std::size(discographie); i+=3)
        {
            for (auto &&a : discographieArtist)
            {
               if(a.contains(discographie[i]))
               {
                    is = true;
                    artist = a;
                    break;
               }
            }
            
            if(is == false)
            {
                artist = "-->" + discographie[i] + "\n  /-->" + discographie[i-1] + "\n    /--> " + discographie[i-2];
                discographieArtist.push_back(artist);
            }
            else
            {
                std::string newArtist;
                if(artist.contains(discographie[i-1]))
                {
                    newArtist = artist + "\n    /--> " + discographie[i-2];
                }
                else
                {
                    newArtist = artist + "\n  /-->" + discographie[i-1] + "\n    /--> " + discographie[i-2];
                }
                
                std::replace(std::begin(discographieArtist), std::end(discographieArtist), artist, newArtist);
                is = false;
            }
        }
        for (auto &&i : discographieArtist)
        {
            std::cout << i << std::endl;
        }
    }

}

void saveDiscographie(std::string saveName)
{
    std::ofstream out{saveName};

    for (auto &&i : discographie)
    {
        out << i;
        out << "|";
    }
}

void loadDiscographie(std::string fileName)
{
    discographie.clear();

    std::ifstream in{fileName};
    if(in.is_open())
    {
        std::string discographieFile;
        std::getline(in, discographieFile);

        auto begin = std::begin(discographieFile);
        auto end = std::find(begin, std::end(discographieFile), '|');

        auto i_barre = std::count(begin, std::end(discographieFile), '|');

        for (auto i = 0; i < i_barre+1; i++)
        {
            std::string morceaux {begin, end};
            discographie.push_back(morceaux);

            begin = ++end;
            end = std::find(begin, std::end(discographieFile), '|');
        }
    }
    else
    {
        std::cout << "Le fichier n'a pas pu être ouvert." << std::endl;
    }
    in.close();
}

int main()
{
    using namespace std::literals;

    while(1)
    {
        std::string commande;

        std::cout << "> ";
        std::getline(std::cin, commande);

        if(commande.starts_with("ajouter"s))
        {
            commande.replace(0, 8, "");
            ajouterMorceaux(commande);
            std::cout << "Le morceaux a été ajouté." << std::endl;
        }
        else if (commande.rfind("afficher", 0) == 0) // si le résultat de 'rfind', qui commence à la position 0, se trouve à la position 0
        {
            commande.replace(0, 9, "");
            if(commande == "morceaux" || commande == "album" || commande == "artiste")
            {
                afficherDiscographie(commande);
            }
            else
            {
                std::cout << "Erreur : Commande invalide." << std::endl;
            }
        }
        else if (commande.rfind("enregistrer", 0) == 0)
        {
            commande.replace(0, 12, "");
            saveDiscographie(commande);
            std::cout << "La discographie, " << commande << ", a été enregistré." << std::endl;
        }
        else if (commande.rfind("charger", 0) == 0)
        {
            commande.replace(0, 8, "");
            loadDiscographie(commande);
            std::cout << "La discographie, " << commande << ", a été chargé." << std::endl;
        }
        else if(commande == "quitter")
        {
            break;
        }
        else
        {
            std::cout << "Erreur : Commande invalide." << std::endl;
        }
    }

    return 0;
}