 #include <iostream>
 #include <string>

/*
Suffixes : 
    u, U (unsigned)
    f, F (flottant)
    l, L ('long int , long double)
    ll, LL (long long int)

Préfixes : 
    0b (binaire)
    0 (octal)
    0x (hexadécimal)
*/

 int main() {
    
    using namespace std::literals; // permet de rendre accessible certain suffixe, comme "s"

    auto some_string{"Hello !"s}; // s : std::string
    std::cout << some_string << std::endl;

    //bool is_secure{};
    int integer{255}; 
    std::cout << integer << std::endl;

    float float_number{14.0f};
    std::cout << float_number << std::endl;

    long long big_number{14'252'366};
    std::cout << big_number << std::endl;

    std::string string_c{"Hello World !"};
    std::cout << string_c << std::endl;

    string_c = "Bye";
    std::cout << string_c << std::endl;

    // const int{456}; cette variable est en lecture, sa valeur ne peut pas changer

    // auto some_code{true}; avec auto, le compilateur déduit directement le type de la variable




    return 0;
 }