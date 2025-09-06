/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:15:31 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/06 17:23:00 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal()
{
    this->_type = "Dog";
    std::cout << "Dog default constructor called\n";
}

Dog::Dog(const Dog& other) {
    this->_type = other._type;
    std::cout << "Dog copy constructor called\n";
}

Dog& Dog::operator=(const Dog& other) {
    if (this != &other) {
        this->_type = other._type;
    }
    std::cout << "Dog copy assignment operator called\n";

    return *this;
}

Dog::~Dog()
{
    std::cout << "Dog destructor called\n";
}

void Dog::makeSound() const {
    std::cout << _type << ": barking angrily Wooooof Woooooof Woof\n";
}

std::string const& Dog::getType() const {
    return this->_type;
}
