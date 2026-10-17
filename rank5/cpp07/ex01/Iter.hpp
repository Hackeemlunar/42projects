#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>
#include <string>

template <typename T>

void printElement(const T &elem)
{
    std::cout << elem << std::endl;
}

template <typename T>

void iter(T* array, size_t length, void (*func)(T&))
{
    if (!array || length == 0 || !func)
        std::cerr << "Invalid input to iter function." << std::endl;
    for (size_t i = 0; i < length; ++i)
    {
        func(array[i]);
    }
}
template <typename T>

void iter(const T* array, size_t length, void (*func)(const T&))
{
    if (!array || length == 0 || !func)
        std::cerr << "Invalid input to iter function." << std::endl;
    for (size_t i = 0; i < length; ++i)
    {
        func(array[i]);
    }
}

#endif