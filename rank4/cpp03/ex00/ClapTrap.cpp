/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:39:58 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/30 23:23:18 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap(): _name("hackeem"), _hitPoint(10), _energyPoint(10), _attackDamage(0) {
    std::cout << "Default constructor called\n";
}

ClapTrap::ClapTrap(std::string name): _name(name), _hitPoint(10), _energyPoint(10), _attackDamage(0) {
    std::cout << "Secondary constructor called\n";
}

ClapTrap::ClapTrap(const ClapTrap &other) {
    std::cout << "Copy constructor called\n";
    this->_name = other._name;
    this->_hitPoint = other._hitPoint;
    this->_energyPoint = other._energyPoint;
    this->_attackDamage = other._attackDamage;
}

ClapTrap& ClapTrap::operator=(const ClapTrap &other) {
    std::cout << "Copy assignment operator called\n";
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoint = other._hitPoint;
        this->_energyPoint = other._energyPoint;
        this->_attackDamage = other._attackDamage;
    }

    return *this;
}

ClapTrap::~ClapTrap() {
    std::cout << "\nDestructor called\n";
}

void ClapTrap::attack(const std::string& target) {
    if (!this->_energyPoint || !this->_hitPoint) {
        std::cout << "Hit point or energy point is 0\n";
        return ;
    }
    --(this->_energyPoint);
    std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " 
        << _attackDamage << " points of damage!\n";
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (!this->_energyPoint || !this->_hitPoint) {
        std::cout << "Hit point or energy point is 0\n";
        return ;
    }
    if (this->_hitPoint - amount < 0)
        this->_hitPoint = 0;
    else
        this->_hitPoint -= amount;
    std::cout << "ClapTrap " << _name << " takes damage, causing it to lose " 
        << amount << " hit points!\n";
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (!this->_energyPoint || !this->_hitPoint) {
        std::cout << "Hit point or energy point is 0\n";
        return ;
    }
    --(this->_energyPoint);
    this->_hitPoint += amount;
    std::cout << "ClapTrap " << _name << " repairs itself, causing it to gain " 
        << amount << " hit points!\n";
}
