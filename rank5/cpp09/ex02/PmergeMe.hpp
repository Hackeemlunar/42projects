#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstddef>
#include <deque>
#include <vector>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::deque<int> _deq;

    std::vector<int> generateJacobsthal(std::size_t maxVal);
    void mergeInsertSortVec(std::vector<int> &arr);

    std::deque<int> generateJacobsthalDeq(std::size_t maxVal);
    void mergeInsertSortDeq(std::deque<int> &arr);

public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    bool process(int argc, char **argv);
};

#endif
