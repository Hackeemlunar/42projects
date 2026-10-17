
#include "Array.hpp"
#include <iostream>

int main()
{
    Array<int> a(5);
    for (unsigned int i = 0; i < 5; i++)
        a[i] = i;

    std::cout << "Array a: ";
    for (unsigned int i = 0; i < 5; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    Array<int> b(a);
    std::cout << "Array b (copy of a): ";
    for (unsigned int i = 0; i < 5; i++)
        std::cout << b[i] << " ";
    std::cout << std::endl;

    Array<int> c;

    c = a;
    std::cout << "Array c (assigned from a): ";
    for (unsigned int i = 0; i < 5; i++)
        std::cout << c[i] << " ";
    std::cout << std::endl;

    return 0;
}
