#include "splitter.hpp"
#include "split_methode.hpp"
#include <iostream>
#include <fstream>

Splitter:Splitter(std::string pdf_path, Methode split_methode, std::string save_path) noexcept : _pdf_path(pdf_path), 
_split_methode(split_methode), _save_path(save_path)
{
    _save_path = "split/"; // Au lancement du constructeur, le chemin de sauvegarde sera dans le dossie 'split'
}

void read_pdf() const noexcept
{
    auto doc = ; // lis le pdf
}

void split_pdf() const noexcept
{

}

void save_pdf() const noexcept
{

}


