#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main()
{
    std::vector<int> numbers {45, -55, 5, 100, -50, -1};

    std::sort(std::begin(numbers), std::end(numbers), [](int a, int b) -> bool{
        return std::abs(a) < std::abs(b);
    });

    std::for_each(std::begin(numbers), std::end(numbers), [](int number) -> void {
        std::cout << number << std::endl;
    });

    return 0;
}