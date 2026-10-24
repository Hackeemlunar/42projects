#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <exception>

template <typename T>
class Array
{
private:
    T *array;
    unsigned int ret_sz;

public:
    Array() : array(NULL), ret_sz(0)
    {
    }

    Array(unsigned int n) : array(n > 0 ? new T[n]() : NULL), ret_sz(n)
    {
    }

    Array(const Array &cpy)
        : array(cpy.ret_sz > 0 ? new T[cpy.ret_sz]() : NULL), ret_sz(cpy.ret_sz)
    {
        try
        {
            for (unsigned int i = 0; i < ret_sz; ++i)
                array[i] = cpy.array[i];
        }
        catch (...)
        {
            delete[] array;
            throw;
        }
    }

    Array &operator=(const Array &b)
    {
        if (this == &b)
            return *this;

        T *newArray = (b.ret_sz > 0) ? new T[b.ret_sz]() : NULL;
        try
        {
            for (unsigned int i = 0; i < b.ret_sz; ++i)
                newArray[i] = b.array[i];
        }
        catch (...)
        {
            delete[] newArray;
            throw;
        }

        delete[] array;
        array = newArray;
        ret_sz = b.ret_sz;
        return *this;
    }

    ~Array()
    {
        delete[] array;
    }

    unsigned int size(void) const
    {
        return ret_sz;
    }

    class Above : public std::exception
    {
    public:
        const char *what() const throw()
        {
            return "Error: index is greater than the size";
        }
    };

    T &operator[](unsigned int i)
    {
        if (i >= ret_sz)
            throw Above();
        return array[i];
    }

    const T &operator[](unsigned int i) const
    {
        if (i >= ret_sz)
            throw Above();
        return array[i];
    }
};

#endif
