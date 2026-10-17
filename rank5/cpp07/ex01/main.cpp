#include "Iter.hpp"

int main()
{
    int a[] = {1,2,3};
    const int b[] = {4,5,6};
    std::string s[] = {"hi","bye"};
    double d[] = {3.14, 2.71, 1.61};

   
    iter(a, 3, printElement<int>);
    iter(b, 3, printElement<int>);
    iter(s, 2, printElement<std::string>);
    iter(d, 3, printElement<double>);
    
}
