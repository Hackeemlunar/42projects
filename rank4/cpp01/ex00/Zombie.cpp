/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:22:54 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/30 19:15:03 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie()
{
}
Zombie::Zombie(const std::string &name) : name(name)
{
}
Zombie::~Zombie()
{
    std::cout << "Deleting " << this->name << " \n";
}

void Zombie::setName(const std::string &name) {
    this->name = name;
}

std::string Zombie::getName() const {
    return this->name;
}

void Zombie::announce() {
    std::cout << this->name << ": " << "BraiiiiiiinnnzzzZ...\n";
}
