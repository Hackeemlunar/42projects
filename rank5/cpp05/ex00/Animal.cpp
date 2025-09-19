/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:48:10 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/07 13:41:26 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include <iostream>

Animal::Animal() : _type("Kingdom Animalia")
{
    std::cout << "Animal default constructor called\n";
}

Animal::Animal(const Animal &other) : _type(other._type) {
    std::cout << "Animal copy constructor called\n";
}

Animal& Animal::operator=(const Animal &other) {
    if (this != &other) {
        this->_type = other._type;
    }
    
    std::cout << "Animal copy assignment operator called\n";
    return *this;
}

Animal::~Animal() {
    std::cout << "Animal destructor called\n";
}

void Animal::makeSound() const {
    std::cout << _type << ": making some unknown animal sound\n";
}

std::string const& Animal::getType() const {
    return this->_type;
}
