#include "../include/grille.hpp"
#include <iostream>

Grille::Grille(int height, int width) noexcept : n_height(height), n_width(width)
{
    for (auto i = 0; i < width*height; i++)
    {
        if (i == width*height/2 - width/2)
        {
            n_grille.push_back('#');
        }
        else
        {
            n_grille.push_back(' ');
        }
    }
}

void Grille::showGrille() const noexcept
{
    for (auto i = 0; i < n_width+2; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl << "|";
    
    for (auto i = 1; i < n_width*n_height+1; i++)
    {
        std::cout << n_grille[i-1];
        if(i % n_width == 0 && i >= n_width)
        {
            std::cout << "|"<< std::endl;
            if(i != n_height*n_width)
            {
                std::cout << "|";
            }
        }
    }
    for (auto i = 0; i < n_width+2; i++)
    {
        std::cout << "-";
    }
}

void Grille::testAroundCase(int h, int w, int& Ncells_around, char state)
{
    if(w > 0 && w < n_width-1)
    {
        if((*this)(h, w-1) == '#' || (*this)(h, w-1) == state)
        {
            Ncells_around++;
        }
        if ((*this)(h, w+1) == '#' || (*this)(h, w+1) == state)
        {
            Ncells_around++;
        }
    }
    if (h > 0 && h < n_height-1)
    {
        if ((*this)(h-1, w) == '#' || (*this)(h-1, w) == state)
        {
            Ncells_around++;
        }
        if ((*this)(h+1, w) == '#' || (*this)(h+1, w) == state)
        {
            Ncells_around++;
        }
    }
    if(h > 0 && h < n_height-1 && w > 0 && w < n_width-1)
    {
        if ((*this)(h-1, w+1) == '#' || (*this)(h-1, w+1) == state)
        {
            Ncells_around++;
        }
        if ((*this)(h-1, w-1) == '#' || (*this)(h-1, w-1) == state)
        {
            Ncells_around++;
        }
        if ((*this)(h+1, w+1) == '#' || (*this)(h+1, w+1) == state)
        {
            Ncells_around++;
        }
        if ((*this)(h+1, w-1) == '#' || (*this)(h+1, w-1) == state)
        {
            Ncells_around++;
        }
    }
}

void Grille::detectCells() noexcept
{
    for (auto h = 0; h < n_height; h++)
    {
        for (auto w = 0; w < n_width; w++)
        {
            if((*this)(h, w) == '#')
            {
                int Ncells_around = 0;
                //std::cout << "la cellule à la position : " << h << "," << w << " est vivante : " << (*this)(h, w) << std::endl;

                testAroundCase(h, w, Ncells_around, 'D');
                if(Ncells_around < 2 || Ncells_around > 3)
                {
                    //std::cout << "la cellule à la position : " << h << "," << w << " va mourir : " << Ncells_around << std::endl;
                    killCell(h, w);
                }
            }
            else if((*this)(h, w) == ' ')
            {
                int Ncells_around = 0;

                testAroundCase(h, w, Ncells_around, 'D');
                if(Ncells_around == 3)
                {
                    reanimateCell(h, w);
                }
            }
        }
    }
    for (auto &&i : n_grille)
    {
        if (i == 'V')
        {
            i = '#';
        }
        else if (i == 'D')
        {
            i = ' ';
        }
    }
    
}
void Grille::killCell(int ligne, int colonne) noexcept
{
    (*this)(ligne, colonne) = 'D';
}
void Grille::reanimateCell(int ligne, int colonne) noexcept
{
    (*this)(ligne, colonne) = 'V';
}

char& Grille::operator()(int ligne, int colonne)
{
    if(ligne+1 > n_height || ligne < 0 || colonne+1 > n_width || colonne < 0)
    {
        std::cout << ligne << "," << colonne << std::endl;
        throw std::out_of_range("Indice hors limite.");
    }

    return n_grille[colonne + n_width*ligne];
}

std::ostream& operator<<(std::ostream& os, Grille& g)
{
    for (auto i = 0; i < g.n_width+2; i++)
    {
        os << "-";
    }
    os << std::endl << "|";
    
    for (auto i = 1; i < g.n_width*g.n_height+1; i++)
    {
        os << g.n_grille[i-1];
        if(i % g.n_width == 0 && i >= g.n_width)
        {
            os << "|"<< std::endl;
            if(i != g.n_height*g.n_width)
            {
                os << "|";
            }
        }
    }
    for (auto i = 0; i < g.n_width+2; i++)
    {
        os << "-";
    }
    return os;
}