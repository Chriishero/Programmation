#include "../include/labyrinthe.hpp"
#include <iostream>
#include <vector>
#include <ostream>
#include <random>
#include <algorithm>

Labyrinthe::Labyrinthe(int height, int width) noexcept : n_height(height), n_width(width)
{
    for (auto i = 1; i < (height * width + 1); i++)
    {
        n_grille.push_back('#');
        n_grille.push_back(' ');

        if(i % n_width == 0 && i >= n_width)
        {
            n_grille.push_back('#');
            n_grille.push_back('\n');
            for (auto i = 0; i < width*2+1; i++)
            {
                n_grille.push_back('#');
            }
            n_grille.push_back('\n');
        }
    }
}

void Labyrinthe::createLabyrinthe() noexcept
{
    int Ypos = 0;
    int Xpos = 1;

    n_startCase = {Ypos, Xpos};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 4);

    bool newCase = false;
    bool findExit = false;

    while(1)
    {
        if((((*this)(Ypos, Xpos+1) == '#' && (*this)(Ypos, Xpos+2) == ' ') || ((*this)(Ypos, Xpos-1) == '#' && (*this)(Ypos, Xpos-2) == ' ') ||
         ((*this)(Ypos+1, Xpos) == '#' && (*this)(Ypos+2, Xpos) == ' ') || ((*this)(Ypos-1, Xpos) == '#' && (*this)(Ypos-2, Xpos) == ' ')) && newCase == false)
        {
            std::cout << "IL y a des potentiellement chemins accessibles : " << Ypos << "," << Xpos << std::endl;
            int n_timeTry = 0;
            while(1)
            {
                int random = distrib(gen);
                int testYPos = Ypos;
                int testXPos = Xpos;
                int wallYPos = Ypos;
                int wallXPos = Xpos;
                switch (random)
                {
                case 1:
                    testXPos += 2;
                    wallXPos += 1;
                    break;
                case 2:
                    testXPos -= 2;
                    wallXPos -= 1;
                    break;
                case 3:
                    testYPos += 2;
                    wallYPos += 1;
                    break;
                case 4:
                    testYPos -= 2;
                    wallYPos -= 1;
                    break;
                }
                if ((*this)(testYPos, testXPos) == 'S' && findExit == false)
                {
                    findExit = true;
                    (*this)(wallYPos, wallXPos) = ' ';
                    n_exitCase = {wallYPos, wallXPos};
                }

                if((*this)(testYPos, testXPos) == ' ' && (*this)(wallYPos, wallXPos) == '#')
                {
                    std::vector<int> pos = {testYPos, testXPos};
                    if(std::find(std::begin(n_markCase), std::end(n_markCase), pos) == std::end(n_markCase))
                    {
                        n_markCase.push_back(pos);
                        (*this)(wallYPos, wallXPos) = ' ';

                        Ypos = testYPos;
                        Xpos = testXPos;

                        auto back = {Ypos, Xpos};
                        n_backPos.push_back(back);

                        std::cout << *this << std::endl;

                        break;
                    }
                    else if (n_timeTry == 4)
                    {
                        std::cout << "Aucun chemin accessible." << std::endl;
                        newCase = true;
                        break;
                    }
                    
                    else
                    {
                        n_timeTry++;
                    }
                }
            }
        }
        else
        {
            newCase = false;
            std::cout << Ypos << "," << Xpos << " ne contient plus d'endroit à explorer." << std::endl; 
            n_backPos.pop_back();

            if (n_backPos.empty())
            {
                std::cout << "Fin du creusage." << std::endl;
                break;
            }

            std::cout << "Backtracking restant : ";
            for (auto &&i : n_backPos)
            {
                for (auto &&p : i)
                {
                    std::cout << p << " | ";   
                }
            }

            auto back = n_backPos.back();
            Ypos = back[0];
            Xpos = back[1];
            std::cout << std::endl << Ypos << "," << Xpos << " est le prochain à tester." << std::endl; 
        }
    }
}
void Labyrinthe::solveLabyrinthe() noexcept
{
    n_backPos.clear();
    n_markCase.clear();

    int Ypos = 0;
    int Xpos = 1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 4);

    bool newCase = false;

    while(1)
    {
        if(((*this)(Ypos, Xpos+1) == ' ' || (*this)(Ypos, Xpos-1) == ' ' || (*this)(Ypos+1, Xpos) == ' ' || (*this)(Ypos-1, Xpos) == ' ') && newCase == false)
        {
            std::vector<int> n_timeTry;
            while(1)
            {
                int random = distrib(gen);
                int testYPos = Ypos;
                int testXPos = Xpos;

                switch (random)
                {
                case 1:
                    testXPos += 1;
                    break;
                case 2:
                    testXPos -= 1;
                    break;
                case 3:
                    testYPos += 1;
                    break;
                case 4:
                    testYPos -= 1;
                    break;
                }
                if(testYPos == n_exitCase[0] && testXPos == n_exitCase[1])
                {
                    Ypos = testYPos;
                    Xpos = testXPos;
                    (*this)(Ypos, Xpos) = '.';
                    std::cout << "La sortie a été trouvé." << std::endl;
                    return;
                }
                if((*this)(testYPos, testXPos) == ' ')
                {   
                    Ypos = testYPos;
                    Xpos = testXPos;
                    (*this)(Ypos, Xpos) = '.';

                    auto back = {Ypos, Xpos};
                    n_backPos.push_back(back);
                    n_markCase.push_back(back);

                    std::cout << *this << std::endl;

                    break;
                }
                else if (std::find(std::begin(n_timeTry), std::end(n_timeTry), 1) != std::end(n_timeTry) && std::find(std::begin(n_timeTry), std::end(n_timeTry), 2) != std::end(n_timeTry) && 
                    std::find(std::begin(n_timeTry), std::end(n_timeTry), 3) != std::end(n_timeTry) && std::find(std::begin(n_timeTry), std::end(n_timeTry), 4) != std::end(n_timeTry))
                    {
                    std::cout << "Aucun chemin accessible : " << testYPos << "," << testXPos << std::endl;
                    newCase = true;
                    break;
                }
                else
                {
                    std::cout << "Non accessible : " << testYPos << "," << testXPos << " : " << (*this)(testYPos, testXPos) << std::endl;
                    n_timeTry.push_back(random);
                }
            }
        }
        else
        {
            newCase = false;
            std::cout << Ypos << "," << Xpos << " ne contient plus d'endroit à explorer." << std::endl; 
            std::cout << Ypos+1 << "," << Xpos << " : " << (*this)(Ypos+1, Xpos) << std::endl;
            std::cout << Ypos-1 << "," << Xpos << " : " << (*this)(Ypos-1, Xpos) << std::endl;
            std::cout << Ypos << "," << Xpos+1 << " : " << (*this)(Ypos, Xpos+1) << std::endl;
            std::cout << Ypos << "," << Xpos-1 << " : " << (*this)(Ypos, Xpos-1) << std::endl;
            n_backPos.pop_back();

            std::cout << "Backtracking restant : ";
            for (auto &&i : n_backPos)
            {
                for (auto &&p : i)
                {
                    std::cout << p << " | ";   
                }
            }

            auto back = n_backPos.back();
            Ypos = back[0];
            Xpos = back[1]; 
        }
    }
}

std::vector<int> Labyrinthe::getExitCase() const noexcept
{
    return n_exitCase;
}
std::vector<int> Labyrinthe::getStartCase() const noexcept
{
    return n_startCase;
}

char& Labyrinthe::operator()(int height, int width)
{
    char& sCase = n_grille[width + ((n_width*2+2)*height)];

    if (height > n_height*2-1)
    {
        sCase = 'S';
    }
    
    return sCase;
}

std::ostream& operator<<(std::ostream& os, Labyrinthe& l)
{
    for (auto &&i : l.n_grille)
    {
        os << i;
    }
    return os;
}