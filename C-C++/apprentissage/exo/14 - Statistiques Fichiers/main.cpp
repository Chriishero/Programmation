#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int main()
{
    std::ifstream read{"file.txt"};
    std::string content;
    std::string line;
    std::string words;

    int nLine = 0;
    int nWord = 0;
    int nChar = 0;

    if(read.is_open())
    {
        while(std::getline(read, line))
        {
            content += line;
            nLine++;
            for (auto const c : line)
            {
                if(!std::isspace(c))
                {
                    nChar++;
                }
            }
        }
    }

    auto begin = std::begin(content);
    auto end = std::end(content);
    auto space = std::find_if(begin, end, isspace);

    for (auto i = 0; i < std::count(begin, end, ' ') + nLine-1; i++)
    {
        nWord++;

        begin = space++;
        space = std::find_if(begin, end, isspace);
    }
    nWord++;

    std::cout << "Le fichier contient :\n" << "\n" << nLine << " lignes.\n" << nWord << " mots.\n" << nChar << " caracteres." << std::endl;

    return 0;
}