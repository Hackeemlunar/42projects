#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>

class RPN {
private:
    std::stack<int> _stack;
 
    int stringToInt(const std::string& str) const;
    bool isOperator(const std::string& token) const;
    int performOperation(const std::string& operation, int operand1, int operand2) const;

public:
    RPN();
    ~RPN();
    int evaluate(const std::string& expression);

};

#endif