#include "Array.hpp"

#include <iostream>
#include <string>

static void printArray(const Array<int> &array, const char *label)
{
    std::cout << label << " (size " << array.size() << "):";
    for (unsigned int i = 0; i < array.size(); ++i)
        std::cout << " " << array[i];
    std::cout << std::endl;
}

int main()
{
    Array<int> empty;
    std::cout << "empty.size() = " << empty.size() << std::endl;

    Array<int> a(5);
    for (unsigned int i = 0; i < a.size(); ++i)
        a[i] = static_cast<int>(i + 1);
    printArray(a, "a");

    Array<int> copy(a);
    copy[0] = 42;
    printArray(a, "a after modifying copy");
    printArray(copy, "copy after modifying copy");

    Array<int> assigned;
    assigned = a;
    assigned[1] = 99;
    printArray(a, "a after modifying assigned");
    printArray(assigned, "assigned after modifying assigned");

    Array<int> self(2);
    self[0] = 1;
    self[1] = 2;
    Array<int> *selfPtr = &self;
    self = *selfPtr;
    printArray(self, "self-assigned");

    try
    {
        std::cout << a[5] << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "non-const out of bounds: " << e.what() << std::endl;
    }

    const Array<int> constArray(a);
    try
    {
        std::cout << constArray[5] << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "const out of bounds: " << e.what() << std::endl;
    }

    try
    {
        std::cout << a[static_cast<unsigned int>(-1)] << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "negative index: " << e.what() << std::endl;
    }

    Array<int> zeros(4);
    std::cout << "default values:";
    for (unsigned int i = 0; i < zeros.size(); ++i)
        std::cout << " " << zeros[i];
    std::cout << std::endl;

    Array<std::string> strings(2);
    strings[0] = "hello";
    strings[1] = "world";
    std::cout << "strings (size " << strings.size() << "): "
              << strings[0] << " " << strings[1] << std::endl;

    return 0;
}
