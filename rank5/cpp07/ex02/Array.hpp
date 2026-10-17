#include <iostream>
#include <exception>

template<typename T>
class Array {
private:
    T* array;
    unsigned int ret_sz;

public:
    Array() {
        std::cout << "Default Constructor Called" << std::endl;
        ret_sz = 0;
        array = NULL;
    }

    Array(unsigned int n) {
        std::cout << "Paramitrized Constructor Called" << std::endl;
        ret_sz = n;
        if (n > 0)
            array = new T[n];
        else
            array = NULL;
    }

    Array(const Array &cpy) {
        std::cout << "Copy Constructor Called" << std::endl;

        ret_sz = cpy.ret_sz;

        if (ret_sz > 0)
            array = new T[ret_sz];
        else
            array = NULL;

        for (unsigned int i = 0; i < ret_sz; i++)
            array[i] = cpy.array[i];
    }

    Array &operator=(const Array &b) {
        std::cout << "Copy assignement operator Called" << std::endl;

        if (this == &b)
            return *this;

        delete[] array;

        ret_sz = b.ret_sz;

        if (ret_sz > 0)
            array = new T[ret_sz];
        else
            array = NULL;

        for (unsigned int i = 0; i < ret_sz; i++)
            array[i] = b.array[i];

        return *this;
    }

    unsigned int size(void) const {
        return ret_sz;
    }

    class Above : public std::exception {
    public:
        const char *what() const throw() {
            return "Error: index is greater than the size";
        }
    };

    T& operator[](unsigned int i) {
        if (i >= ret_sz)
            throw Above();
        return array[i];
    }

    const T &operator[](unsigned int i) const {
        if (i >= ret_sz)
            throw Above();
        return array[i];
    }

    ~Array() {
        std::cout << "Destructor Called" << std::endl;
        delete[] array;
    }
};
