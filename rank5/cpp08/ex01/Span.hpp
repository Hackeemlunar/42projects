#ifndef SPAN_HPP
#define SPAN_HPP

#include <exception>
#include <vector>

class Span
{
private:
    unsigned int _maxSize;
    std::vector<int> _numbers;

public:
    class FullException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };

    class NoSpanException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };

    Span();
    Span(unsigned int n);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();

    void addNumber(int number);

    template <typename InputIterator>
    void addNumbers(InputIterator first, InputIterator last)
    {
        std::vector<int> values(first, last);

        if (_numbers.size() + values.size() > _maxSize)
            throw FullException();
        _numbers.insert(_numbers.end(), values.begin(), values.end());
    }

    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;
    unsigned int size() const;
    unsigned int maxSize() const;
};

#endif
