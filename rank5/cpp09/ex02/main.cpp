#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error\n";
        return 1;
    }
    
    PmergeMe sorter;
    sorter.process(argc, argv);
    
    return 0;
}
