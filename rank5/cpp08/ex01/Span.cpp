#include "Span.hpp"

#include <algorithm>
#include <cstddef>

const char *Span::FullException::what() const throw()
{
    return "Span: maximum capacity reached";
}

const char *Span::NoSpanException::what() const throw()
{
    return "Span: not enough numbers to compute a span";
}

Span::Span() : _maxSize(0), _numbers()
{
}

Span::Span(unsigned int n) : _maxSize(n), _numbers()
{
    _numbers.reserve(n);
}

Span::Span(const Span &other) : _maxSize(other._maxSize), _numbers(other._numbers)
{
}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        _maxSize = other._maxSize;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span()
{
}

void Span::addNumber(int number)
{
    if (_numbers.size() >= _maxSize)
        throw FullException();
    _numbers.push_back(number);
}

unsigned int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw NoSpanException();

    std::vector<int> sorted(_numbers);
    std::sort(sorted.begin(), sorted.end());

    unsigned int shortest = static_cast<unsigned int>(-1);
    for (std::size_t i = 1; i < sorted.size(); ++i)
    {
        unsigned int distance = static_cast<unsigned int>(sorted[i])
                              - static_cast<unsigned int>(sorted[i - 1]);

        if (distance < shortest)
            shortest = distance;
    }
    return shortest;
}

unsigned int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw NoSpanException();

    std::vector<int>::const_iterator lowest =
        std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator highest =
        std::max_element(_numbers.begin(), _numbers.end());

    return static_cast<unsigned int>(*highest)
         - static_cast<unsigned int>(*lowest);
}

unsigned int Span::size() const
{
    return static_cast<unsigned int>(_numbers.size());
}

unsigned int Span::maxSize() const
{
    return _maxSize;
}
