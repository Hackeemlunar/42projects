/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:30:29 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/25 18:41:00 by hmensah-         ###   ########.fr       */
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

bool Fixed::operator<(const Fixed& other) const {
    return this->getRawBits() < other.getRawBits();
}

bool Fixed::operator>(const Fixed& other) const {
    return other < *this;
}

bool Fixed::operator==(const Fixed& other) const {
    return this->getRawBits() == other.getRawBits();
}

bool Fixed::operator!=(const Fixed& other) const {
    return !(*this == other);
}

bool Fixed::operator<=(const Fixed& other) const {
    return !(*this > other);
}

bool Fixed::operator>=(const Fixed& other)  const {
    return !(*this < other);
}

Fixed Fixed::operator+(const Fixed& other) const {
    Fixed result;
    result.setRawBits(this->getRawBits() + other.getRawBits());
    return result;
}

Fixed Fixed::operator-(const Fixed& other) const {
    Fixed result;
    result.setRawBits(this->getRawBits() - other.getRawBits());
    return result;
}

Fixed Fixed::operator*(const Fixed& other) const {
    long long raw = static_cast<long long>(this->getRawBits()) * other.getRawBits();

    Fixed result;
    result.setRawBits(raw >> fractionalPart);
    return result;
}

Fixed Fixed::operator/(const Fixed& other) const {
    long long raw = static_cast<long long>(this->getRawBits()) << fractionalPart;

    Fixed result;
    result.setRawBits(raw / other.getRawBits());
    return result;
}

Fixed& Fixed::min(Fixed &first, Fixed &second) {
    return (first.getRawBits() < second.getRawBits() ? first : second);
}

const Fixed& Fixed::min(const Fixed &first, const Fixed &second) {
    return (first.getRawBits() < second.getRawBits() ? first : second);
}

Fixed& Fixed::max(Fixed &first, Fixed &second) {
    return (first.getRawBits() > second.getRawBits() ? first : second);
}

const Fixed& Fixed::max(const Fixed &first, const Fixed &second) {
    return (first.getRawBits() > second.getRawBits() ? first : second);
}
