/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:15:43 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/20 22:42:44 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl
{
private:
    void debug();
    void info();
    void warning();
    void error();

    void (Harl::*_functionPtr[4])();
    std::string _level[4];
public:
    Harl();
    ~Harl();
    void complain(std::string level);
};

#endif