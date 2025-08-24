/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:30:29 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/24 22:20:22 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

const int Fixed::fractionalPart = 8;

Fixed::Fixed() : fixedPart(0) {
    std::cout << "Default constructor called\n";
}

Fixed::Fixed(const int initial) : fixedPart(initial) {
    std::cout << "Int constructor called\n";
    this->fixedPart = initial << fractionalPart;
}

Fixed::Fixed(const float initial) : fixedPart(initial) {
    std::cout << "Float constructor called\n";
    this->fixedPart = static_cast<int>(std::roundf(initial * (1 << fractionalPart)));
}

Fixed::Fixed(const Fixed &other) {
    std::cout << "Copy constructor called\n";
    *this = other;
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
    return this->fixedPart;
}

void Fixed::setRawBits(int const raw) {
    this->fixedPart = raw;
}

float Fixed::toFloat(void) const {
    return static_cast<float>(this->fixedPart) / (1 << Fixed::fractionalPart);
}

float Fixed::toInt(void) const {
    return this->fixedPart >> Fixed::fractionalPart;
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed) {
    out << fixed.toFloat();
    return out;
}
