/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 17:53:12 by hmensah-          #+#    #+#             */
/*   Updated: 2026/10/17 17:53:13 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

#include <cctype>
#include <cerrno>
#include <cfloat>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

namespace
{
    enum LiteralKind
    {
        CHAR,
        INT,
        FLOAT,
        DOUBLE,
        INVALID
    };

    struct Literal
    {
        LiteralKind kind;
        char c;
        int i;
        double d;
        bool intOverflow;
        bool doubleOverflow;

        Literal()
            : kind(INVALID), c(0), i(0), d(0.0),
              intOverflow(false), doubleOverflow(false)
        {
        }
    };

    bool isNaN(double value)
    {
        return value != value;
    }

    bool isInfinite(double value)
    {
        return !isNaN(value) && (value > DBL_MAX || value < -DBL_MAX);
    }

    bool hasIntegerSyntax(const std::string& input)
    {
        size_t i = 0;

        if (input.empty())
            return false;
        if (input[i] == '+' || input[i] == '-')
            ++i;
        if (i == input.length())
            return false;
        while (i < input.length())
        {
            if (!std::isdigit(static_cast<unsigned char>(input[i])))
                return false;
            ++i;
        }
        return true;
    }

    bool parseDouble(const std::string& input, double& value, bool& overflow)
    {
        char* end = NULL;

        errno = 0;
        value = std::strtod(input.c_str(), &end);
        if (end == input.c_str() || *end != '\0')
            return false;
        overflow = (errno == ERANGE && (value > DBL_MAX || value < -DBL_MAX));
        return true;
    }

    Literal detect(const std::string& input)
    {
        Literal literal;

        // Quoted char literal: 'a'
        if (input.length() == 3 && input[0] == '\'' && input[2] == '\''
            && std::isprint(static_cast<unsigned char>(input[1])))
        {
            literal.kind = CHAR;
            literal.c = input[1];
            literal.d = static_cast<double>(literal.c);
            return literal;
        }

        // Bare printable character: a
        if (input.length() == 1
            && std::isprint(static_cast<unsigned char>(input[0]))
            && !std::isdigit(static_cast<unsigned char>(input[0])))
        {
            literal.kind = CHAR;
            literal.c = input[0];
            literal.d = static_cast<double>(literal.c);
            return literal;
        }

        // Double pseudo-literals
        if (input == "nan" || input == "+nan" || input == "-nan")
        {
            literal.kind = DOUBLE;
            literal.d = std::numeric_limits<double>::quiet_NaN();
            return literal;
        }
        if (input == "inf" || input == "+inf")
        {
            literal.kind = DOUBLE;
            literal.d = std::numeric_limits<double>::infinity();
            return literal;
        }
        if (input == "-inf")
        {
            literal.kind = DOUBLE;
            literal.d = -std::numeric_limits<double>::infinity();
            return literal;
        }

        // Float pseudo-literals
        if (input == "nanf" || input == "+nanf" || input == "-nanf")
        {
            literal.kind = FLOAT;
            literal.d = std::numeric_limits<double>::quiet_NaN();
            return literal;
        }
        if (input == "inff" || input == "+inff")
        {
            literal.kind = FLOAT;
            literal.d = std::numeric_limits<double>::infinity();
            return literal;
        }
        if (input == "-inff")
        {
            literal.kind = FLOAT;
            literal.d = -std::numeric_limits<double>::infinity();
            return literal;
        }

        // Float literal ending with 'f'
        if (input.length() > 1 && input[input.length() - 1] == 'f')
        {
            double value;
            bool overflow;
            std::string body = input.substr(0, input.length() - 1);

            if (parseDouble(body, value, overflow))
            {
                literal.kind = FLOAT;
                literal.d = value;
                literal.doubleOverflow = overflow;
                return literal;
            }
        }

        // Integer literal
        if (hasIntegerSyntax(input))
        {
            char* end = NULL;
            long parsed;
            bool strtolOverflow;
            double magnitude;
            bool overflow;

            errno = 0;
            parsed = std::strtol(input.c_str(), &end, 10);
            strtolOverflow = (errno == ERANGE);
            parseDouble(input, magnitude, overflow);

            literal.kind = INT;
            literal.d = magnitude;
            literal.doubleOverflow = overflow;
            if (strtolOverflow || parsed > INT_MAX || parsed < INT_MIN)
                literal.intOverflow = true;
            else
                literal.i = static_cast<int>(parsed);
            return literal;
        }

        // Double literal
        {
            double value;
            bool overflow;

            if (parseDouble(input, value, overflow))
            {
                literal.kind = DOUBLE;
                literal.d = value;
                literal.doubleOverflow = overflow;
            }
        }
        return literal;
    }

    void printChar(const Literal& literal)
    {
        std::cout << "char: ";
        if (literal.kind == INVALID || literal.doubleOverflow)
        {
            std::cout << "impossible" << std::endl;
            return;
        }
        if (literal.kind == CHAR)
        {
            std::cout << "'" << literal.c << "'" << std::endl;
            return;
        }

        double value = literal.d;
        if (isNaN(value) || isInfinite(value) || value < 0.0 || value > 127.0)
        {
            std::cout << "impossible" << std::endl;
            return;
        }

        char c = static_cast<char>(value);
        if (std::isprint(static_cast<unsigned char>(c)))
            std::cout << "'" << c << "'" << std::endl;
        else
            std::cout << "Non displayable" << std::endl;
    }

    void printInt(const Literal& literal)
    {
        std::cout << "int: ";
        if (literal.kind == INVALID || literal.doubleOverflow
            || (literal.kind == INT && literal.intOverflow))
        {
            std::cout << "impossible" << std::endl;
            return;
        }

        double value = literal.d;
        if (isNaN(value) || isInfinite(value)
            || value > INT_MAX || value < INT_MIN)
        {
            std::cout << "impossible" << std::endl;
            return;
        }
        std::cout << static_cast<int>(value) << std::endl;
    }

    void printFloat(const Literal& literal)
    {
        std::cout << "float: ";
        if (literal.kind == INVALID || literal.doubleOverflow)
        {
            std::cout << "impossible" << std::endl;
            return;
        }

        double value = literal.d;
        if (isNaN(value))
            std::cout << "nanf" << std::endl;
        else if (isInfinite(value))
            std::cout << (value < 0.0 ? "-inff" : "+inff") << std::endl;
        else if (value > FLT_MAX || value < -FLT_MAX)
            std::cout << "impossible" << std::endl;
        else
            std::cout << std::fixed << std::setprecision(1)
                      << static_cast<float>(value) << "f" << std::endl;
    }

    void printDouble(const Literal& literal)
    {
        std::cout << "double: ";
        if (literal.kind == INVALID || literal.doubleOverflow)
        {
            std::cout << "impossible" << std::endl;
            return;
        }

        double value = literal.d;
        if (isNaN(value))
            std::cout << "nan" << std::endl;
        else if (isInfinite(value))
            std::cout << (value < 0.0 ? "-inf" : "+inf") << std::endl;
        else
            std::cout << std::fixed << std::setprecision(1) << value << std::endl;
    }
}

ScalarConverter::ScalarConverter()
{
}

void ScalarConverter::convert(const std::string& literal)
{
    Literal parsed = detect(literal);

    printChar(parsed);
    printInt(parsed);
    printFloat(parsed);
    printDouble(parsed);
}
