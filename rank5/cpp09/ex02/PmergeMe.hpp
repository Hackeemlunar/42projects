#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <sys/time.h>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <sstream>

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int>  _deq;
    
    std::vector<int> generateJacobsthal(size_t max_val);
    void mergeInsertSortVec(std::vector<int>& arr);
    
    std::deque<int>  generateJacobsthalDeq(size_t max_val);
    void mergeInsertSortDeq(std::deque<int>& arr);

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void process(int argc, char** argv);
};

#endif
