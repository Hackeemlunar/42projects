/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:15:40 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/20 22:51:57 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

Harl::Harl()
{
    _functionPtr[0] = &Harl::debug;
    _functionPtr[1] = &Harl::info;
    _functionPtr[2] = &Harl::warning;
    _functionPtr[3] = &Harl::error;

    _level[0] = "DEBUG";
    _level[1] = "INFO";
    _level[2] = "WARNING";
    _level[3] = "ERROR";
}

Harl::~Harl()
{
}

void Harl::debug() {
    std::cout << "Let's debug all evaluator proposed errors\n";
}

void Harl::info() {
    std::cout << "Check out, an evaluator entered the frame now\n";
}

void Harl::warning() {
    std::cout << "Tell the evaluator to treat this as a warning\n";
}

void Harl::error() {
    std::cout << "Evaluator error, that's certainly not my fault.\n";
}

void Harl::complain(std::string level) {
    for (size_t i = 0; i < 4; i++)
    {
        if (_level[i] == level)
        {
            (this->*_functionPtr[i])();
            return ;
        }
    }
    std::cout << "Invalid level\n";
}
