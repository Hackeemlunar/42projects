#include "easyfind.hpp"

const char *NotFoundException::what() const throw()
{
    return "easyfind: value not found in container";
}
