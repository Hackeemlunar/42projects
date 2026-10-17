#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
    *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

/* ================== Vector Implementation ================== */

std::vector<int> PmergeMe::generateJacobsthal(size_t max_val) {
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    size_t i = 2;
    while (true) {
        int next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
        jacobsthal.push_back(next);
        if (next >= (int)max_val) break;
        i++;
    }
    return jacobsthal;
}

void PmergeMe::mergeInsertSortVec(std::vector<int>& arr) {
    if (arr.size() < 2) return;
    
    // STEP 1: Group the elements of X into pairs
    bool hasStraggler = false;
    int straggler = -1;
    if (arr.size() % 2 != 0) {
        hasStraggler = true;
        straggler = arr.back();
        arr.pop_back();
    }
    
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size(); i += 2) {
        pairs.push_back(std::make_pair(arr[i], arr[i+1]));
    }
    
    // STEP 2: Determine the larger of the two elements in each pair
    for (size_t i = 0; i < pairs.size(); ++i) {
        if (pairs[i].first < pairs[i].second) {
            std::swap(pairs[i].first, pairs[i].second);
        }
    }
    
    // STEP 3: Recursively sort the larger elements from each pair
    std::vector<int> A;
    for (size_t i = 0; i < pairs.size(); ++i) {
        A.push_back(pairs[i].first);
    }
    
    mergeInsertSortVec(A);
    
    // Realign the pairs to keep the winners and losers together
    std::vector<int> pend;
    std::vector<bool> used(pairs.size(), false);
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (A[i] == pairs[j].first && !used[j]) {
                used[j] = true;
                pend.push_back(pairs[j].second);
                break;
            }
        }
    }
    
    // STEP 4: Create the Main chain and pend
    std::vector<int> main_chain;
    
    // Since a1 >= b1 we can push b1 into the front of the main chain
    main_chain.push_back(pend[0]); 
    for (size_t i = 0; i < A.size(); ++i) {
        main_chain.push_back(A[i]);
    }
    
    // STEP 5: Generate the order of insertion (Jacobsthal combinations)
    std::vector<int> jacobsthal = generateJacobsthal(pend.size());
    
    // STEP 6: Insert the elements of the pend into the main chain
    // Use binary search to determine the position
    size_t last_inserted = 1; 
    for (size_t i = 3; i < jacobsthal.size(); ++i) {
        size_t current_jacob = jacobsthal[i];
        if (current_jacob > pend.size()) {
            current_jacob = pend.size();
        }
        
        for (size_t j = current_jacob; j > last_inserted; --j) {
            int element = pend[j - 1]; // Insert Jacob number first then indexes before it
            std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), element);
            main_chain.insert(it, element);
        }
        last_inserted = current_jacob;
        if (last_inserted == pend.size()) break;
    }
    
    // STEP 7: Do you remember the struggler? now you can push it
    if (hasStraggler) {
        std::vector<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
        main_chain.insert(it, straggler);
    }
    
    arr = main_chain;
}

/* ================== Deque Implementation ================== */

std::deque<int> PmergeMe::generateJacobsthalDeq(size_t max_val) {
    std::deque<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    size_t i = 2;
    while (true) {
        int next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
        jacobsthal.push_back(next);
        if (next >= (int)max_val) break;
        i++;
    }
    return jacobsthal;
}

void PmergeMe::mergeInsertSortDeq(std::deque<int>& arr) {
    if (arr.size() < 2) return;
    
    // STEP 1: Group the elements of X into pairs
    bool hasStraggler = false;
    int straggler = -1;
    if (arr.size() % 2 != 0) {
        hasStraggler = true;
        straggler = arr.back();
        arr.pop_back();
    }
    
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size(); i += 2) {
        pairs.push_back(std::make_pair(arr[i], arr[i+1]));
    }
    
    // STEP 2: Determine the larger of the two elements in each pair
    for (size_t i = 0; i < pairs.size(); ++i) {
        if (pairs[i].first < pairs[i].second) {
            std::swap(pairs[i].first, pairs[i].second);
        }
    }
    
    // STEP 3: Recursively sort the larger elements from each pair
    std::deque<int> A;
    for (size_t i = 0; i < pairs.size(); ++i) {
        A.push_back(pairs[i].first);
    }
    
    mergeInsertSortDeq(A);
    
    // Realign the pairs to keep the winners and losers together
    std::deque<int> pend;
    std::deque<bool> used(pairs.size(), false);
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (A[i] == pairs[j].first && !used[j]) {
                used[j] = true;
                pend.push_back(pairs[j].second);
                break;
            }
        }
    }
    
    // STEP 4: Create the Main chain and pend
    std::deque<int> main_chain;
    
    // Since a1 >= b1 we can push b1 into the front of the main chain
    main_chain.push_back(pend[0]); 
    for (size_t i = 0; i < A.size(); ++i) {
        main_chain.push_back(A[i]);
    }
    
    // STEP 5: Generate the order of insertion (Jacobsthal combinations)
    std::deque<int> jacobsthal = generateJacobsthalDeq(pend.size());
    
    // STEP 6: Insert the elements of the pend into the main chain
    // Use binary search to determine the position
    size_t last_inserted = 1; 
    for (size_t i = 3; i < jacobsthal.size(); ++i) {
        size_t current_jacob = jacobsthal[i];
        if (current_jacob > pend.size()) {
            current_jacob = pend.size();
        }
        
        for (size_t j = current_jacob; j > last_inserted; --j) {
            int element = pend[j - 1]; // Insert Jacob number first then indexes before it
            std::deque<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), element);
            main_chain.insert(it, element);
        }
        last_inserted = current_jacob;
        if (last_inserted == pend.size()) break;
    }
    
    // STEP 7: Do you remember the struggler? now you can push it
    if (hasStraggler) {
        std::deque<int>::iterator it = std::lower_bound(main_chain.begin(), main_chain.end(), straggler);
        main_chain.insert(it, straggler);
    }
    
    arr = main_chain;
}

/* ================== Processor ================== */

void PmergeMe::process(int argc, char** argv) {
    try {
        struct timeval start, end;
        
        // Measure vector parsing
        gettimeofday(&start, NULL);
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg.empty()) continue;
            std::istringstream iss(arg);
            std::string token;
            while (iss >> token) {
                for (size_t j = 0; j < token.size(); ++j) {
                    if (!std::isdigit(token[j]) && !(j == 0 && token[j] == '+')) {
                        throw std::invalid_argument("Error");
                    }
                }
                long val = std::atol(token.c_str());
                if (val <= 0 || val > 2147483647) throw std::invalid_argument("Error");
                _vec.push_back(static_cast<int>(val));
            }
        }
        if (_vec.empty()) throw std::invalid_argument("Error");
        gettimeofday(&end, NULL);
        double vec_parse_time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

        // Measure deque parsing
        gettimeofday(&start, NULL);
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg.empty()) continue;
            std::istringstream iss(arg);
            std::string token;
            while (iss >> token) {
                long val = std::atol(token.c_str());
                _deq.push_back(static_cast<int>(val));
            }
        }
        gettimeofday(&end, NULL);
        double deq_parse_time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

        // Print Before
        std::cout << "Before: ";
        for (size_t i = 0; i < _vec.size(); ++i) {
            std::cout << _vec[i] << " ";
            if (i == 4 && _vec.size() > 5) {
                std::cout << "[...]";
                break;
            }
        }
        std::cout << "\n";

        // Sort Vector
        gettimeofday(&start, NULL);
        mergeInsertSortVec(_vec);
        gettimeofday(&end, NULL);
        double vec_sort_time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

        // Sort Deque
        gettimeofday(&start, NULL);
        mergeInsertSortDeq(_deq);
        gettimeofday(&end, NULL);
        double deq_sort_time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

        // Print After
        std::cout << "After: ";
        for (size_t i = 0; i < _vec.size(); ++i) {
            std::cout << _vec[i] << " ";
            if (i == 4 && _vec.size() > 5) {
                std::cout << "[...]";
                break;
            }
        }
        std::cout << "\n";

        // Print times
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "Time to process a range of " << _vec.size() 
                  << " elements with std::vector : " << (vec_parse_time + vec_sort_time) << " us\n";
        std::cout << "Time to process a range of " << _deq.size() 
                  << " elements with std::deque  : " << (deq_parse_time + deq_sort_time) << " us\n";

    } catch (const std::exception& e) {
        std::cerr << "Error\n";
    }
}
