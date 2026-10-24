#ifndef RPN_HPP
#define RPN_HPP

#include <list>
#include <string>

class RPN
{
private:
    std::list<int> _stack;

    int stringToInt(const std::string &str) const;
    bool isOperator(const std::string &token) const;
    int performOperation(const std::string &operation, int operand1, int operand2) const;

public:
    RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();

    int evaluate(const std::string &expression);
};

#endif
