/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:15:40 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/21 13:27:59 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

Harl::Harl()
{
}

Harl::~Harl()
{
}

void Harl::debug()
{
    std::cout << "[ DEBUG ]\n";
    std::cout << "Let's debug all evaluator proposed errors\n\n";
}

void Harl::info()
{
    std::cout << "[ INFO ]\n";
    std::cout << "Check out, an evaluator entered the frame now\n\n";
}

void Harl::warning()
{
    std::cout << "[ WARNING ]\n";
    std::cout << "Tell the evaluator to treat this as a warning\n\n";
}

void Harl::error()
{
    std::cout << "[ ERROR ]\n";
    std::cout << "Evaluator error, that's certainly not my fault.\n\n";
}

int getLevel(std::string level)
{
    if (level == "DEBUG")
        return 1;
    else if (level == "INFO")
        return 2;
    else if (level == "WARNING")
        return 3;
    else if (level == "ERROR")
        return 4;
    else
        return 0;
}

void Harl::complain(std::string level)
{
    int tempLevel = getLevel(level);
    switch (tempLevel)
    {
    case 1:
        this->debug();
    case 2:
        this->info();
    case 3:
        this->warning();
    case 4:
        this->error();
        break ;
    default:
        std::cout << "[ Probably complaining about insignificant problems ]\n";
    }
}
