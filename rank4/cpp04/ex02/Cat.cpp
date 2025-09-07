/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:04:13 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/06 17:26:05 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal()
{
    this->_type = "Cat";
    this->_brain = new Brain();
    std::cout << "Cat default constructor called\n";
}

Cat::Cat(const Cat& other) : Animal(other) {
    this->_brain = new Brain(*other._brain);
    std::cout << "Cat copy constructor called\n";
}

Cat& Cat::operator=(const Cat& other) {
    if (this != &other) {
        Animal::operator=(other);
        delete this->_brain;
        this->_brain = new Brain(*other._brain);
    }
    std::cout << "Cat copy assignment operator called\n";

    return *this;
}

Cat::~Cat()
{
    delete this->_brain;
    std::cout << "Cat destructor called\n";
}

void Cat::makeSound() const {
    std::cout << _type << ": crying fondly meow weoooooowww meeeeoooooooooowwww\n";
}

std::string const& Cat::getType() const {
    return this->_type;
}
