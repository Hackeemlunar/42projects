/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:30:29 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/22 20:32:49 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "iostream"

const int Fixed::fractionalPart = 0;

Fixed::Fixed() : fixedPart(0) {
    std::cout << "Default constructor called\n";
}

Fixed::Fixed(const Fixed &other) {
    std::cout << "Copy constructor called\n";
    this->fixedPart = other.getRawBits();
}

Fixed& Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assignment operator called\n";
    if (this != &other) {
        this->fixedPart= other.getRawBits();
    }
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called\n";
}

int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called\n";
    return this->fixedPart;
}

void Fixed::setRawBits(int const raw) {
    this->fixedPart = raw;
}