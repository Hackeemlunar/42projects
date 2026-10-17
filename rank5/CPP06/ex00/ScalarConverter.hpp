/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 17:53:18 by hmensah-          #+#    #+#             */
/*   Updated: 2026/10/17 17:53:19 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <cfloat>
#include <cmath>
#include <climits>
#include <iomanip>


class ScalarConverter
{
private:
    ScalarConverter();

public:
    static void convert(const std::string& literal);
    static void toChar(const std::string& input);
    static void toInt(const std::string& input);
    static void toFloat(const std::string& input);
    static void toDouble(const std::string& input);
};

#endif