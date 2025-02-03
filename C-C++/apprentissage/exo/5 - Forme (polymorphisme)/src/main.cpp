#include "../include/triangle.hpp"
#include "../include/cercle.hpp"
#include "../include/rectangle.hpp"
#include "../include/carre.hpp"
#include <iostream>

int main()
{
    Triangle tr{2, 5.2};
    Cercle cer{5};
    Rectangle rec{25.56, 66.2};
    Carre car{5455445.2};

    tr.aire();
    cer.aire();
    rec.aire();
    car.aire();

    return 0;
}