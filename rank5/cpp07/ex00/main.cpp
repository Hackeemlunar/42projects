#include "whatever.hpp"

#include <iostream>
#include <string>

int main(void)
{
    int a = 2;
    int b = 3;

    ::swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
    std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;

    std::string c = "chaine1";
    std::string d = "chaine2";

    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
    std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;

    int equal1 = 42;
    int equal2 = 42;

    std::cout << "min( equal, equal ) returns second: "
              << (&::min(equal1, equal2) == &equal2) << std::endl;
    std::cout << "max( equal, equal ) returns second: "
              << (&::max(equal1, equal2) == &equal2) << std::endl;

    return 0;
}
