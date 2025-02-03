#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main()
{
    std::string sentence = "You are a delusional existence.";
    std::vector<std::string> words;

    auto begin = std::begin(sentence);
    auto space { std::find_if(begin, std::end(sentence), isspace) };

    for (auto i = 0; i < std::count(std::begin(sentence), std::end(sentence), ' ') ; i++)
    {
        std::string word { begin, space };
        words.push_back(word);

        begin = ++space;
        if(std::count(begin, std::end(sentence), ' ') > 0)
        {
            space = std::find_if(begin, std::end(sentence), isspace);
        }
    }
    std::string word { space, std::end(sentence)};
    words.push_back(word);

    for (const auto &w : words)
    {
        std::cout << w << std::endl;
    }
    

    return 0;
}