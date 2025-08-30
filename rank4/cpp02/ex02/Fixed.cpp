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

Fixed::Fixed() : fixedPart(0) {}

Fixed::Fixed(const int initial) : fixedPart(initial) {
    this->fixedPart = initial << fractionalPart;
}

Fixed::Fixed(const float initial) : fixedPart(initial) {
    this->fixedPart = static_cast<int>(roundf(initial * (1 << fractionalPart)));
}

Fixed::Fixed(const Fixed &other) {
    *this = other;
}

Fixed& Fixed::operator=(const Fixed &other) {
    if (this != &other) {
        this->fixedPart= other.getRawBits();
    }
    return *this;
}

Fixed::~Fixed() {}

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

Fixed Fixed::operator++(int) {
    Fixed temp = *this;
    ++(*this);
    return temp;
}

Fixed& Fixed::operator++() {
    this->fixedPart++;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed temp = *this;
    --(*this);
    return temp;
}

Fixed& Fixed::operator--() {
    this->fixedPart--;
    return *this;
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
