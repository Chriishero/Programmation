#include <iostream>
#include "matrice.hpp"

int main()
{
    Matrice m1{2, 3};
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 1;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m1(1, 2) = 3;
    /*
    1 , 2 , 1
    3 , 4 , 3
    */

    Matrice m2{3, 2};
    m2(0, 0) = 5;
    m2(0, 1) = 1;
    m2(1, 0) = 3;
    m2(1, 1) = 4;
    m2(2, 0) = 6;
    m2(2, 1) = 7;
    /*
    5 , 1 
    3 , 4
    6 , 7 
    */
    
    Matrice m3{2, 3};
    m3(0, 0) = 6;
    m3(0, 1) = 2;
    m3(0, 2) = 3;
    m3(1, 0) = 4;
    m3(1, 1) = 8;
    m3(1, 2) = 1;
    /*
    6 , 2 , 3
    4 , 8 , 1
    */

    std::cout << m1 * m2 << std::endl;
    /*
    17 , 16
    45 , 40
    */

    std::cout << "Addition : \n" << m1 + m3 << std::endl;
    /*
    7 , 4 , 4
    7 , 12 , 4
    */

    std::cout << "Multiplication par n : \n" << m1 * 2 << std::endl;
    /*
    2 , 4 , 6
    6 , 8 , 6
    */

    m1.getSize();

    std::cout << m1.ligne(0) << std::endl;
    std::cout << m1.colonne(1) << std::endl;
}