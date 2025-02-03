#include "matrice.hpp"
#include <iostream>

Matrice::Matrice(int n_lignes, int n_colonnes) noexcept : m_n_lignes(n_lignes), m_n_colonnes(n_colonnes)
{
    for (auto i = 0; i < n_lignes*n_colonnes; i++)
    {
        matrice.push_back(0);
    }
}

void Matrice::getSize() const noexcept
{
    std::cout << "La matrice à une dimension de " << m_n_lignes << " lignes et " << m_n_colonnes << " colonnes." << std::endl;
}

Matrice Matrice::ligne(int n_ligne) noexcept
{
    Matrice ligne{1, m_n_colonnes};

    for (auto i = 0; i < m_n_colonnes; i++)
    {
        ligne(0, i) = (*this)(n_ligne, i);
    }
    return ligne;
}
Matrice Matrice::colonne(int n_colonne) noexcept
{
    Matrice colonne{m_n_lignes, 1};

    for (auto i = 0; i < m_n_lignes; i++)
    {
        colonne(i, 0) = (*this)(i, n_colonne);
    }
    return colonne;
}

double& Matrice::operator()(int ligne, int colonne)
{
    if(ligne+1 > m_n_lignes || ligne < 0 || colonne+1 > m_n_colonnes || colonne < 0)
    {
        throw std::out_of_range("Indices hors limites.");
    }
    return matrice[(colonne) + m_n_colonnes*ligne];
}

Matrice Matrice::operator+=(Matrice& other)
{
    if(m_n_lignes != other.m_n_lignes || m_n_colonnes != other.m_n_colonnes)
    {
        throw std::length_error("Les matrices ne sont pas de la même dimension.");
    }

    //Matrice result(m_n_lignes, m_n_colonnes);
    for (auto i = 0; i < m_n_lignes; i++)
    {
        for (auto j = 0; j < m_n_colonnes; j++)
        {
            (*this)(i, j) += other(i, j);
        }
    }
    
    //std::swap(*this, result);

    return *this;
}

Matrice Matrice::operator+(Matrice& other)
{
    Matrice result(m_n_lignes, other.m_n_colonnes);

    result = *this;
    result += other;

    return result; 
}

Matrice Matrice::operator*=(Matrice& other)
{
    if(m_n_colonnes != other.m_n_lignes)
    {
        throw std::length_error("La matrice1 doit avoir le même nombre de colonne que la matrice2 a de ligne");
    }

    Matrice result(m_n_lignes, other.m_n_colonnes);

    for (auto k = 0; k < result.m_n_lignes; k++) // calcule le produit de la matrice 'this' sur la matrice 'other'
    {
        for (auto i = 0; i < result.m_n_colonnes; i++)
        {
            for (auto j = 0; j < m_n_colonnes; j++)
            {
                result(k, i) += (*this)(k, j) * other(j, i); 
            }
        }
    }

    std::swap(*this, result);
    
    return *this; 
}

Matrice Matrice::operator*(Matrice& other)
{   
    Matrice result(m_n_lignes, other.m_n_colonnes);

    result = *this;
    result *= other;

    return result; 
}

Matrice Matrice::operator*=(int n)
{
    for (size_t i = 0; i < std::size(matrice); i++)
    {
        matrice[i] *= n;
    }

    return *this;
}

Matrice operator*(Matrice m, double n)
{
    return m *= n;
}

std::ostream& operator<<(std::ostream& os, const Matrice& m)
{
    for (auto i = 0; i < m.m_n_colonnes*m.m_n_lignes; i++)
    {
        if(i % m.m_n_colonnes == 0 && i != 0)
        {
            os << "\n";
        }
        os << m.matrice[i] << ", ";
    }
    
    return os;
}