#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>
#include <iostream>

template <typename T>
void iter(T *array, std::size_t length, void (*func)(T &))
{
    if (!func || (!array && length > 0))
    {
        std::cout << "Invalid input to iter function." << std::endl;
        return;
    }

    for (std::size_t i = 0; i < length; ++i)
        func(array[i]);
}

template <typename T>
void iter(const T *array, std::size_t length, void (*func)(const T &))
{
    if (!func || (!array && length > 0))
    {
        std::cout << "Invalid input to iter function." << std::endl;
        return;
    }

    for (std::size_t i = 0; i < length; ++i)
        func(array[i]);
}

#endif
