#include "easyfind.hpp"

#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template <typename T>
static void findAndPrint(const char *label, T &container, int value)
{
    try
    {
        typename T::iterator it = easyfind(container, value);

        std::cout << label << ": found " << *it << " at index "
                  << std::distance(container.begin(), it) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << label << ": " << e.what() << std::endl;
    }
}

template <typename T>
static void findConstAndPrint(const char *label, const T &container, int value)
{
    try
    {
        typename T::const_iterator it = easyfind(container, value);

        std::cout << label << ": found " << *it << " at index "
                  << std::distance(container.begin(), it) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << label << ": " << e.what() << std::endl;
    }
}

int main()
{
    std::vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);
    vector.push_back(20);
    vector.push_back(40);

    std::list<int> list(vector.begin(), vector.end());
    std::deque<int> deque(vector.begin(), vector.end());

    findAndPrint("vector, first 20", vector, 20);
    findAndPrint("vector, last 40", vector, 40);
    findAndPrint("vector, missing 99", vector, 99);

    findAndPrint("list, first 20", list, 20);
    findAndPrint("list, missing 99", list, 99);

    findAndPrint("deque, first 20", deque, 20);
    findAndPrint("deque, missing 99", deque, 99);

    const std::vector<int> constVector(vector);
    findConstAndPrint("const vector, 30", constVector, 30);
    findConstAndPrint("const vector, missing 99", constVector, 99);

    std::vector<int> empty;
    findAndPrint("empty vector, 42", empty, 42);

    std::vector<int> negatives;
    negatives.push_back(-10);
    negatives.push_back(-20);
    negatives.push_back(-30);
    findAndPrint("vector, -20", negatives, -20);

    return 0;
}
