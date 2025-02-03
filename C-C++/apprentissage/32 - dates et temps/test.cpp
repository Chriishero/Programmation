#include <iostream>
#include <chrono>

int main()
{
    std::chrono::hours h{16};
    std::chrono::minutes m{54};

    std::cout << h + m << std::endl;

    return 0;
}