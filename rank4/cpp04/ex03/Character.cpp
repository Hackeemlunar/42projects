/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:30:00 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/16 15:48:40 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include <iostream>

Character::Character() : _name("default")
{
    for (int i = 0; i < 4; i++) {
        this->_inventory[i] = NULL;
    }
    // std::cout << "Character default constructor called\n";
}

Character::Character(std::string const & name) : _name(name)
{
    for (int i = 0; i < 4; i++) {
        this->_inventory[i] = NULL;
    }
    // std::cout << "Character parametrized constructor called for: " << name << "\n";
}

Character::Character(const Character& other) : _name(other._name)
{
    for (int i = 0; i < 4; i++) {
        if (other._inventory[i] != NULL) {
            this->_inventory[i] = other._inventory[i]->clone();
        } else {
            this->_inventory[i] = NULL;
        }
    }
    // std::cout << "Character copy constructor called\n";
}

Character& Character::operator=(const Character& other)
{
    if (this != &other) {
        this->_name = other._name;
        
        // Delete existing materias
        for (int i = 0; i < 4; i++) {
            if (this->_inventory[i] != NULL) {
                delete this->_inventory[i];
                this->_inventory[i] = NULL;
            }
        }
        
        // Deep copy the other's inventory
        for (int i = 0; i < 4; i++) {
            if (other._inventory[i] != NULL) {
                this->_inventory[i] = other._inventory[i]->clone();
            }
        }
    }
    // std::cout << "Character copy assignment operator called\n";
    return *this;
}

Character::~Character()
{
    for (int i = 0; i < 4; i++) {
        if (this->_inventory[i] != NULL) {
            delete this->_inventory[i];
        }
    }
    // std::cout << "Character destructor called for: " << this->_name << "\n";
}

std::string const & Character::getName() const
{
    return this->_name;
}

void Character::equip(AMateria* m)
{
    if (m == NULL) {
        return;
    }
    
    for (int i = 0; i < 4; i++) {
        if (this->_inventory[i] == NULL) {
            this->_inventory[i] = m;
            return;
        }
    }
}

void Character::unequip(int idx)
{
    if (idx < 0 || idx >= 4) {
        return;
    }
    
    if (this->_inventory[idx] == NULL) {
        return;
    }
    
    this->_inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target)
{
    if (idx < 0 || idx >= 4) {
        return;
    }
    
    if (this->_inventory[idx] == NULL) {
        return;
    }
    
    this->_inventory[idx]->use(target);
}
