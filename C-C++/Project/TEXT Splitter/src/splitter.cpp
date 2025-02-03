#include "../include/splitter.hpp"
#include "../include/split_methode.hpp"
#include <iostream>
#include <string>
#include <fstream>

std::string content;
std::string if_content;
int n_page = 0;
//std::ifstream read{"TEXT/bodybuilding.txt"};

int i = 0;

Splitter::Splitter(std::string txt_path, Methode split_methode, std::string save_path, int page_interval) noexcept : _txt_path(txt_path), _split_methode(split_methode), _save_path(save_path), _page_interval(page_interval)
{
    _save_path = "split/"; // Au lancement du constructeur, le chemin de sauvegarde sera dans le dossie 'split'
}

void Splitter::save_txt(const std::string content) const noexcept
{
    std::cout << content << std::endl;

    i++;
    
    std::ofstream write{_save_path + std::to_string(i) + ".txt"};
    write << content;
}

void Splitter::split_txt() const noexcept
{
    std::ifstream read{_txt_path};

    if (read)
    {
        if (_split_methode == Methode::word)
        {
            while(std::getline(read, content, ' '))             
            {
                save_txt(content);
            }
        }
        else if (_split_methode == Methode::sentence)
        {
            while(std::getline(read, content, '.'))             
            {
                save_txt(content);
            }
        }
        else if (_split_methode == Methode::page)
        {
            while(std::getline(read, if_content))             
            {
                if ((if_content.contains("Page") || if_content.contains("page")))
                {
                    for (auto i = 0; i < 10000; i++)
                    {
                        if (if_content.contains(i))
                        {
                            content += if_content + "\n";
                            save_txt(content);
                            content = "";
                            break;
                        }
                    }
                }
                else
                {
                    content += if_content + "\n";
                }
            }
        } 
        else if (_split_methode == Methode::page_interval)
        {
            std::ifstream count_page{_txt_path};
            while (std::getline(count_page, if_content))
            {
                if ((if_content.contains("Page") || if_content.contains("page"))) // compte le nombre de page dans le .txt
                {
                    for (auto i = 0; i < 10000; i++)
                    {
                        if (if_content.contains(i))
                        {
                            n_page++;
                            break;
                        }
                    }
                }
            }
            int interval = n_page / _page_interval;
            int current_page = 0;

            while(std::getline(read, if_content))             
            {
                if ((if_content.contains("Page") || if_content.contains("page")))
                {
                    for (auto i = 0; i < 10000; i++)
                    {
                        if (if_content.contains(i))
                        {
                            content += if_content + "\n";
                            current_page++;

                            if (current_page % _page_interval == 0 && current_page <= interval * _page_interval) // si la page actuel est un multiple de l'interval, alors
                            {
                                save_txt(content);
                                content = "";
                            }

                            else if (current_page > interval * _page_interval && current_page - interval * _page_interval == n_page % _page_interval) // si la page actuel - le multiple max de l'interval = au reste du nbr de page % l'interval, alors
                            {
                                save_txt(content);
                                content = "";
                            }

                            break;
                        }
                    }
                }
                else
                {
                    content += if_content + "\n";
                }
            }
        }
    }
        
    else{std::cout << "Le fichier n'a pas pu être ouvert." << std::endl;}
}
