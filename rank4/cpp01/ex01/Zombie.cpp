/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:22:54 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/17 17:12:31 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie()
{
}
Zombie::Zombie(const std::string &name) : _name(name)
{
}
Zombie::~Zombie()
{
    std::cout << "Deleting " << this->_name << " \n";
}

void Zombie::setName(const std::string &name) {
    this->_name = name;
}

std::string Zombie::getName() const {
    return this->_name;
}

void Zombie::announce() {
    std::cout << this->_name << ": " << "BraiiiiiiinnnzzzZ...\n";
}
