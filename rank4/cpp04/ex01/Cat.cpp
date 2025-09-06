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
    std::cout << "Cat default constructor called\n";
}

Cat::Cat(const Cat& other) {
    this->_type = other._type;
    std::cout << "Cat copy constructor called\n";
}

Cat& Cat::operator=(const Cat& other) {
    if (this != &other) {
        this->_type = other._type;
    }
    std::cout << "Cat copy assignment operator called\n";

    return *this;
}

Cat::~Cat()
{
    std::cout << "Cat destructor called\n";
}

void Cat::makeSound() const {
    std::cout << _type << ": crying fondly meow weoooooowww meeeeoooooooooowwww\n";
}

std::string const& Cat::getType() const {
    return this->_type;
}
