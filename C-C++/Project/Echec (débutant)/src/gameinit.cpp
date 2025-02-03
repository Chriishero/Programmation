#include "../include/gameinit.hpp"
#include "../include/enum.hpp"
#include <iostream>
#include <map>
#include <string>

bool first_generation = true;

GameInit::GameInit() noexcept
{
    _initial_board_content = { {"a8", "@ "}, {"b8", "# "}, {"c8", "@ "}, {"d8", "# "}, {"e8", "@ "}, {"f8", "# "}, {"g8", "@ "}, {"h8", "# "},
                                {"a7", "# "}, {"b7", "@ "}, {"c7", "# "}, {"d7", "@ "}, {"e7", "# "}, {"f7", "@ "}, {"g7", "# "}, {"h7", "@ "},
                                {"a6", "@ "}, {"b6", "# "}, {"c6", "@ "}, {"d6", "# "}, {"e6", "@ "}, {"f6", "# "}, {"g6", "@ "}, {"h6", "# "},
                                {"a5", "# "}, {"b5", "@ "}, {"c5", "# "}, {"d5", "@ "}, {"e5", "# "}, {"f5", "@ "}, {"g5", "# "}, {"h5", "@ "},
                                {"a4", "@ "}, {"b4", "# "}, {"c4", "@ "}, {"d4", "# "}, {"e4", "@ "}, {"f4", "# "}, {"g4", "@ "}, {"h4", "# "},
                                {"a3", "# "}, {"b3", "@ "}, {"c3", "# "}, {"d3", "@ "}, {"e3", "# "}, {"f3", "@ "}, {"g3", "# "}, {"h3", "@ "},
                                {"a2", "@ "}, {"b2", "# "}, {"c2", "@ "}, {"d2", "# "}, {"e2", "@ "}, {"f2", "# "}, {"g2", "@ "}, {"h2", "# "},
                                {"a1", "# "}, {"b1", "@ "}, {"c1", "# "}, {"d1", "@ "}, {"e1", "# "}, {"f1", "@ "}, {"g1", "# "}, {"h1", "@ "} };
    // # = noir

    piece_initial_board_content = _initial_board_content;
    piece_initial_board_content["a1"] = "bR"; piece_initial_board_content["a2"] = "b ";
    piece_initial_board_content["b1"] = "bN"; piece_initial_board_content["b2"] = "b ";
    piece_initial_board_content["c1"] = "bB"; piece_initial_board_content["c2"] = "b ";
    piece_initial_board_content["d1"] = "bQ"; piece_initial_board_content["d2"] = "b ";
    piece_initial_board_content["e1"] = "bK"; piece_initial_board_content["e2"] = "b ";
    piece_initial_board_content["f1"] = "bB"; piece_initial_board_content["f2"] = "b ";
    piece_initial_board_content["g1"] = "bN"; piece_initial_board_content["g2"] = "b ";
    piece_initial_board_content["h1"] = "bR"; piece_initial_board_content["h2"] = "b ";

    piece_initial_board_content["a8"] = "wR"; piece_initial_board_content["a7"] = "w ";
    piece_initial_board_content["b8"] = "wN"; piece_initial_board_content["b7"] = "w ";
    piece_initial_board_content["c8"] = "wB"; piece_initial_board_content["c7"] = "w ";
    piece_initial_board_content["d8"] = "wQ"; piece_initial_board_content["d7"] = "w ";
    piece_initial_board_content["e8"] = "wK"; piece_initial_board_content["e7"] = "w ";
    piece_initial_board_content["f8"] = "wB"; piece_initial_board_content["f7"] = "w ";
    piece_initial_board_content["g8"] = "wN"; piece_initial_board_content["g7"] = "w ";
    piece_initial_board_content["h8"] = "wR"; piece_initial_board_content["h7"] = "w ";      
}

void GameInit::generate_board() noexcept
{
    for (const auto& [key, value] : piece_initial_board_content)
    {
        if(key.contains("8"))
        {
            std::cout << value;
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
    for (const auto& [key, value] : piece_initial_board_content)
    {
        if(key.contains("7"))
        {
            std::cout << value;
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
    for (const auto& [key, value] : piece_initial_board_content)
    {
        if(key.contains("6"))
        {
            std::cout << value;
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
    for (const auto& [key, value] : piece_initial_board_content)
        {
            if(key.contains("5"))
            {
                std::cout << value;
                std::cout << ' ';
            }
        }
    std::cout << std::endl;
    for (const auto& [key, value] : piece_initial_board_content)
        {
            if(key.contains("4"))
            {
                std::cout << value;
                std::cout << ' ';
            }
        }
    std::cout << std::endl;
    for (const auto& [key, value] : piece_initial_board_content)
        {
            if(key.contains("3"))
            {
                std::cout << value;
                std::cout << ' ';
            }
        }
    std::cout << std::endl;
    for (const auto& [key, value] : piece_initial_board_content)
        {
            if(key.contains("2"))
            {
                std::cout << value;
                std::cout << ' ';
            }
        }
    std::cout << std::endl;
    for (const auto& [key, value] : piece_initial_board_content)
        {
            if(key.contains("1"))
            {
                std::cout << value;
                std::cout << ' ';
            }
        }
    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
}

std::map<std::string, std::string> GameInit::get_board() const noexcept
{
    return piece_initial_board_content;
}