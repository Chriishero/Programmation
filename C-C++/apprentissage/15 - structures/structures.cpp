#include <iostream>
#include <string>

struct Product
{
    std::string name;
    float price;
    bool available;
};


int main()
{
    using Product = struct Product;
    Product p{"Poid de 5kg", 2.5, true}; // les variables de la structure Product ont été initialisé

    std::cout << p.price << std::endl;

    return 0;
}