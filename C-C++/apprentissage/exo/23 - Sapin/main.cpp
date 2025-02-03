#include <iostream>

int firMaxSize = 100;
int firMinSize = 10;

void tryType(int& value)
{
    while(!(std::cin >> value))
    {
        std::cout << "Incorrect value." << std::endl;
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Enter the fir size (" << firMinSize << " - " << firMaxSize << ") : " << std::endl;
    }
}

int main()
{
    int firSize = 0;
    char firChar = '*';

    while (true)
    {
        std::cout << "Enter the fir size (" << firMinSize << " - " << firMaxSize << ") : " << std::endl;
        tryType(firSize);

        if(firSize < firMinSize || firSize > firMaxSize)
        {
            std::cout << "Incorrect value." << std::endl;
            continue;
        }
        else
        {
            break;
        }
    }

    for (auto i = 2; i < firSize+1; i+=2)
    {
        int nSpace = firSize - i;

        for (auto i3 = 0; i3 < 2; i3++)
        {
            for (auto i = 0; i < nSpace/2; i++)
            {
                std::cout << " ";
            }
            if(i3 < 1)
            {
                for (auto i2 = 0; i2 < i; i2++)
                {
                    std::cout << firChar ;
                }
            }
        }
        std::cout << std::endl;
    }
}