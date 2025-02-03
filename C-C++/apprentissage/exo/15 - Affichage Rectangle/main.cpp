#include <iostream>


void printRectangle(int height, int width)
{
    for (auto i = 0; i < height; i++)
    {
        for (auto i = 0; i < width; i++)
        {
            std::cout << "*";
        }
        
        std::cout << std::endl;
    }
    
}

int main()
{
    printRectangle(5, 6);

    return 0;
}