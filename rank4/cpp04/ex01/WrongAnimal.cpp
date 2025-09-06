/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:48:10 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/06 20:30:30 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"
#include <iostream>

WrongAnimal::WrongAnimal() : _type("WrongAnimal")
{
    std::cout << "WrongAnimal default constructor called\n";
}

WrongAnimal::WrongAnimal(const WrongAnimal &other) {
    this->_type = other._type;
    std::cout << "WrongAnimal copy constructor called\n";
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal &other) {
    if (this != &other) {
        this->_type = other._type;
    }
    
    std::cout << "WrongAnimal copy assignment operator called\n";
    return *this;
}

WrongAnimal::~WrongAnimal() {
    std::cout << "WrongAnimal destructor called\n";
}

void WrongAnimal::makeSound() const {
    std::cout << _type << ": making some unknown WrongAnimal sound\n";
}

std::string const& WrongAnimal::getType() const {
    return this->_type;
}
