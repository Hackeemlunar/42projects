/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:28:57 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/18 17:07:47 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(const std::string& name, Weapon& weapon) : _weapon(weapon), _name(name) {}

HumanA::~HumanA() {}

void HumanA::attack() const {
    std::cout << _name << " attacks with their " << _weapon.getType() << "\n";
}
