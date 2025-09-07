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
    this->_brain = new Brain();
    std::cout << "Dog default constructor called\n";
}

Dog::Dog(const Dog& other) : Animal(other) {
    this->_brain = new Brain(*other._brain);
    std::cout << "Dog copy constructor called\n";
}

Dog& Dog::operator=(const Dog& other) {
    if (this != &other) {
        Animal::operator=(other);
        delete this->_brain;
        this->_brain = new Brain(*other._brain);
    }
    std::cout << "Dog copy assignment operator called\n";

    return *this;
}

Dog::~Dog()
{
    delete this->_brain;
    std::cout << "Dog destructor called\n";
}

void Dog::makeSound() const {
    std::cout << _type << ": barking angrily Wooooof Woooooof Woof\n";
}

std::string const& Dog::getType() const {
    return this->_type;
}
