#include "PmergeMe.hpp"

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/time.h>
#include <utility>

/* ================== Helpers ================== */

static double elapsedMicroseconds(const struct timeval &start, const struct timeval &end)
{
    return (end.tv_sec - start.tv_sec) * 1000000.0
         + (end.tv_usec - start.tv_usec);
}

template <typename Container>
static void printSequence(const char *label, const Container &values)
{
    typename Container::const_iterator it = values.begin();
    std::size_t i = 0;

    std::cout << label << " ";
    while (it != values.end() && i < 5)
    {
        if (i != 0)
            std::cout << " ";
        std::cout << *it;
        ++it;
        ++i;
    }
    if (it != values.end())
        std::cout << " [...]";
    std::cout << std::endl;
}

/* ================== Canonical form ================== */

PmergeMe::PmergeMe() : _vec(), _deq()
{
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
}

/* ================== Vector Implementation ================== */

std::vector<int> PmergeMe::generateJacobsthal(std::size_t maxVal)
{
    std::vector<int> jacobsthal;

    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    std::size_t i = 2;
    while (true)
    {
        int next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];

        jacobsthal.push_back(next);
        if (next >= static_cast<int>(maxVal))
            break;
        ++i;
    }
    return jacobsthal;
}

void PmergeMe::mergeInsertSortVec(std::vector<int> &arr)
{
    if (arr.size() < 2)
        return;

    // STEP 1: Group the elements of X into pairs
    bool hasStraggler = false;
    int straggler = -1;
    if (arr.size() % 2 != 0)
    {
        hasStraggler = true;
        straggler = arr.back();
        arr.pop_back();
    }

    std::vector<std::pair<int, int> > pairs;
    for (std::size_t i = 0; i < arr.size(); i += 2)
        pairs.push_back(std::make_pair(arr[i], arr[i + 1]));

    // STEP 2: Determine the larger of the two elements in each pair
    for (std::size_t i = 0; i < pairs.size(); ++i)
    {
        if (pairs[i].first < pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }

    // STEP 3: Recursively sort the larger elements from each pair
    std::vector<int> winners;
    for (std::size_t i = 0; i < pairs.size(); ++i)
        winners.push_back(pairs[i].first);

    mergeInsertSortVec(winners);

    // Realign the pairs to keep the winners and losers together
    std::vector<int> pend;
    std::vector<bool> used(pairs.size(), false);
    for (std::size_t i = 0; i < winners.size(); ++i)
    {
        for (std::size_t j = 0; j < pairs.size(); ++j)
        {
            if (winners[i] == pairs[j].first && !used[j])
            {
                used[j] = true;
                pend.push_back(pairs[j].second);
                break;
            }
        }
    }

    // STEP 4: Create the main chain and pend
    std::vector<int> mainChain;

    // Since a1 >= b1 we can push b1 into the front of the main chain
    mainChain.push_back(pend[0]);
    for (std::size_t i = 0; i < winners.size(); ++i)
        mainChain.push_back(winners[i]);

    // STEP 5: Generate the order of insertion (Jacobsthal numbers)
    std::vector<int> jacobsthal = generateJacobsthal(pend.size());

    // STEP 6: Insert the elements of the pend into the main chain
    // Use binary search to determine the position
    std::size_t lastInserted = 1;
    for (std::size_t i = 3; i < jacobsthal.size(); ++i)
    {
        std::size_t currentJacob = jacobsthal[i];

        if (currentJacob > pend.size())
            currentJacob = pend.size();

        for (std::size_t j = currentJacob; j > lastInserted; --j)
        {
            int element = pend[j - 1]; // Insert Jacob number first then indexes before it
            std::vector<int>::iterator it =
                std::lower_bound(mainChain.begin(), mainChain.end(), element);

            mainChain.insert(it, element);
        }
        lastInserted = currentJacob;
        if (lastInserted == pend.size())
            break;
    }

    // STEP 7: Do you remember the straggler? Now you can push it
    if (hasStraggler)
    {
        std::vector<int>::iterator it =
            std::lower_bound(mainChain.begin(), mainChain.end(), straggler);

        mainChain.insert(it, straggler);
    }

    arr = mainChain;
}

/* ================== Deque Implementation ================== */

std::deque<int> PmergeMe::generateJacobsthalDeq(std::size_t maxVal)
{
    std::deque<int> jacobsthal;

    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    std::size_t i = 2;
    while (true)
    {
        int next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];

        jacobsthal.push_back(next);
        if (next >= static_cast<int>(maxVal))
            break;
        ++i;
    }
    return jacobsthal;
}

void PmergeMe::mergeInsertSortDeq(std::deque<int> &arr)
{
    if (arr.size() < 2)
        return;

    // STEP 1: Group the elements of X into pairs
    bool hasStraggler = false;
    int straggler = -1;
    if (arr.size() % 2 != 0)
    {
        hasStraggler = true;
        straggler = arr.back();
        arr.pop_back();
    }

    std::deque<std::pair<int, int> > pairs;
    for (std::size_t i = 0; i < arr.size(); i += 2)
        pairs.push_back(std::make_pair(arr[i], arr[i + 1]));

    // STEP 2: Determine the larger of the two elements in each pair
    for (std::size_t i = 0; i < pairs.size(); ++i)
    {
        if (pairs[i].first < pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }

    // STEP 3: Recursively sort the larger elements from each pair
    std::deque<int> winners;
    for (std::size_t i = 0; i < pairs.size(); ++i)
        winners.push_back(pairs[i].first);

    mergeInsertSortDeq(winners);

    // Realign the pairs to keep the winners and losers together
    std::deque<int> pend;
    std::deque<bool> used(pairs.size(), false);
    for (std::size_t i = 0; i < winners.size(); ++i)
    {
        for (std::size_t j = 0; j < pairs.size(); ++j)
        {
            if (winners[i] == pairs[j].first && !used[j])
            {
                used[j] = true;
                pend.push_back(pairs[j].second);
                break;
            }
        }
    }

    // STEP 4: Create the main chain and pend
    std::deque<int> mainChain;

    // Since a1 >= b1 we can push b1 into the front of the main chain
    mainChain.push_back(pend[0]);
    for (std::size_t i = 0; i < winners.size(); ++i)
        mainChain.push_back(winners[i]);

    // STEP 5: Generate the order of insertion (Jacobsthal numbers)
    std::deque<int> jacobsthal = generateJacobsthalDeq(pend.size());

    // STEP 6: Insert the elements of the pend into the main chain
    // Use binary search to determine the position
    std::size_t lastInserted = 1;
    for (std::size_t i = 3; i < jacobsthal.size(); ++i)
    {
        std::size_t currentJacob = jacobsthal[i];

        if (currentJacob > pend.size())
            currentJacob = pend.size();

        for (std::size_t j = currentJacob; j > lastInserted; --j)
        {
            int element = pend[j - 1]; // Insert Jacob number first then indexes before it
            std::deque<int>::iterator it =
                std::lower_bound(mainChain.begin(), mainChain.end(), element);

            mainChain.insert(it, element);
        }
        lastInserted = currentJacob;
        if (lastInserted == pend.size())
            break;
    }

    // STEP 7: Do you remember the straggler? Now you can push it
    if (hasStraggler)
    {
        std::deque<int>::iterator it =
            std::lower_bound(mainChain.begin(), mainChain.end(), straggler);

        mainChain.insert(it, straggler);
    }

    arr = mainChain;
}

/* ================== Processor ================== */

bool PmergeMe::process(int argc, char **argv)
{
    _vec.clear();
    _deq.clear();

    try
    {
        struct timeval start;
        struct timeval end;

        // Measure vector parsing and validation
        gettimeofday(&start, NULL);
        for (int i = 1; i < argc; ++i)
        {
            std::istringstream iss(argv[i]);
            std::string token;

            while (iss >> token)
            {
                for (std::size_t j = 0; j < token.size(); ++j)
                {
                    if (!std::isdigit(static_cast<unsigned char>(token[j])))
                        throw std::runtime_error("Error");
                }

                errno = 0;
                char *endptr = NULL;
                long value = std::strtol(token.c_str(), &endptr, 10);

                if (errno == ERANGE || endptr == token.c_str() || *endptr != '\0'
                    || value <= 0 || value > INT_MAX)
                    throw std::runtime_error("Error");
                _vec.push_back(static_cast<int>(value));
            }
        }
        if (_vec.empty())
            throw std::runtime_error("Error");
        gettimeofday(&end, NULL);
        double vecParseTime = elapsedMicroseconds(start, end);

        // Measure deque parsing
        gettimeofday(&start, NULL);
        for (std::size_t i = 0; i < _vec.size(); ++i)
            _deq.push_back(_vec[i]);
        gettimeofday(&end, NULL);
        double deqParseTime = elapsedMicroseconds(start, end);

        // Print the unsorted sequence
        printSequence("Before:", _vec);

        // Sort the vector
        gettimeofday(&start, NULL);
        mergeInsertSortVec(_vec);
        gettimeofday(&end, NULL);
        double vecSortTime = elapsedMicroseconds(start, end);

        // Sort the deque
        gettimeofday(&start, NULL);
        mergeInsertSortDeq(_deq);
        gettimeofday(&end, NULL);
        double deqSortTime = elapsedMicroseconds(start, end);

        // Print the sorted sequence
        printSequence("After:", _vec);

        // Print the times
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "Time to process a range of " << _vec.size()
                  << " elements with std::vector : "
                  << (vecParseTime + vecSortTime) << " us" << std::endl;
        std::cout << "Time to process a range of " << _deq.size()
                  << " elements with std::deque  : "
                  << (deqParseTime + deqSortTime) << " us" << std::endl;
    }
    catch (const std::exception &)
    {
        std::cerr << "Error" << std::endl;
        return false;
    }
    return true;
}
