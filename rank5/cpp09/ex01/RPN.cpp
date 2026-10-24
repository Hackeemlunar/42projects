#include "RPN.hpp"

#include <cstdlib>
#include <sstream>
#include <stdexcept>

RPN::RPN() : _stack()
{
}

RPN::RPN(const RPN &other) : _stack(other._stack)
{
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::~RPN()
{
}

bool RPN::isOperator(const std::string &token) const
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::stringToInt(const std::string &str) const
{
    char *endptr = NULL;
    long value = std::strtol(str.c_str(), &endptr, 10);

    if (str.empty() || endptr == str.c_str() || *endptr != '\0')
        throw std::runtime_error("Invalid token: " + str);

    if (value >= 10 || value <= -10)
        throw std::runtime_error("Number must be less than 10");

    return static_cast<int>(value);
}

int RPN::performOperation(const std::string &operation, int operand1, int operand2) const
{
    if (operation == "+")
        return operand1 + operand2;
    if (operation == "-")
        return operand1 - operand2;
    if (operation == "*")
        return operand1 * operand2;
    if (operation == "/")
    {
        if (operand2 == 0)
            throw std::runtime_error("Division by zero");
        return operand1 / operand2;
    }
    throw std::runtime_error("Unknown operator: " + operation);
}

int RPN::evaluate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;

    _stack.clear();
    while (iss >> token)
    {
        if (isOperator(token))
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Insufficient operands for operation: " + token);
            int operand2 = _stack.back();
            _stack.pop_back();
            int operand1 = _stack.back();
            _stack.pop_back();
            int result = performOperation(token, operand1, operand2);
            _stack.push_back(result);
        }
        else
        {
            int value = stringToInt(token);
            _stack.push_back(value);
        }
    }

    if (_stack.size() != 1)
        throw std::runtime_error("Invalid RPN expression");

    return _stack.back();
}
