/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:14:16 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/18 16:31:34 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string& name) : _name(name), _weapon(NULL) {}

HumanB::~HumanB() {}

void HumanB::setWeapon(const Weapon& weapon) {
    _weapon = const_cast<Weapon*>(&weapon);
}

void HumanB::attack() const {
    if (_weapon)
        std::cout << _name << " attacks with their " << _weapon->getType() << "\n";
}