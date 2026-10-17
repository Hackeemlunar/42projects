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

ScalarConverter::ScalarConverter()
{
}

void ScalarConverter::toChar(const std::string& input)
{
    std::cout << "char: ";

    if(input.length() == 1 && std::isprint(input[0]) && !std::isdigit(input[0]))
    {
        std::cout << "'" << input[0] << "'" << std::endl;
        return ;
    }

    try
    {
        std::string temp = input;
        if(!temp.empty() && temp[temp.size() - 1] == 'f')
            temp = temp.substr(0, temp.size() - 1);
        char* end;
        double d = strtod(temp.c_str(), &end);
        char c = static_cast<char>(d);

        if (*end != '\0' || d < 0 || d > 127 || std::isnan(d) || std::isinf(d))
            throw std::exception();
        if (std::isprint(c))
            std::cout << "'" << c << "'" << std::endl;
        else
            std::cout << "Non displayable" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "impossible" << std::endl;
    }
    
}

void ScalarConverter::toInt(const std::string& input)
{
    std::cout << "int: ";
    try
    {
        std::string temp = input;
        if (temp.length() > 0 && temp[temp.size() - 1] == 'f')
            temp = temp.substr(0, temp.size() - 1);
        char* end;
        double d = strtod(temp.c_str(), &end);

        if (*end != '\0' || d > INT_MAX || d < INT_MIN || std::isnan(d) || std::isinf(d))
            throw std::exception();

        std::cout << static_cast<int>(d) << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout <<  "impossible" << std::endl;
    }
}


void ScalarConverter::toFloat(const std::string& input)
{
    std::cout << "float: ";
    try
    {
        std::string temp = input;
        if(!temp.empty() && temp[temp.size() - 1] == 'f')
            temp = temp.substr(0, temp.size() - 1);
        char* end;
        float f = static_cast<float>(strtod(temp.c_str(), &end));

        if (*end != '\0')
            throw std::exception();
        if (std::isnan(f))
            std::cout << "nanf" << std::endl;
        else if (std::isinf(f))
            std::cout << (f < 0 ? "-inff" : "+inff") << std::endl;
        else
            std::cout << f << ".0f" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "impossible" << std::endl;
    }
}


void ScalarConverter::toDouble(const std::string& input)
{
    std::cout << "double: ";
    try
    {
       std::string temp = input;
         if(!temp.empty() && temp[temp.size() - 1] == 'f')
                temp = temp.substr(0, temp.size() - 1);
       char* end;
       double d = strtod(temp.c_str(), &end);

       if(*end != '\0')
            throw std::exception();
        if(std::isnan(d))
            std::cout << "nan" << std::endl;
        else if (std::isinf(d))
            std::cout << (d < 0 ? "-inf" : "+inf") << std::endl;
        else
            std::cout << std::fixed << std::setprecision(1) << d << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "impossible" << std::endl;
    }
}


void ScalarConverter::convert(const std::string& literal)
{
    toChar(literal);
    toInt(literal);
    toFloat(literal);
    toDouble(literal);
}
