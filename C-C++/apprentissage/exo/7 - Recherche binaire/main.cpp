#include <iostream>
#include <array>

int main()
{
    std::array<int, 5> n_array{1,2,3,4,5};
    int left = n_array.front();
    int right = n_array.back();
    int middle = (right-1)/2;

    int element = 5;

    while (1)
    {
        if(element == middle && middle <= right && middle >= left)
        {
            std::cout << "Trouve." << std::endl;
            break;
        }
        else if (element > middle)
        {
            middle++;
        }
        else if(element < middle)
        {
            middle--;
        }
        else if(middle > right || middle < left)
        {
            std::cout << "Pas present." << std::endl;
            break;
        }
    }

    return 0;
}