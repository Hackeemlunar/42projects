/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:30:00 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/16 15:50:54 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include <iostream>

AMateria::AMateria() : _type("unknown")
{
    // std::cout << "AMateria default constructor called\n";
}

AMateria::AMateria(std::string const & type) : _type(type)
{
    // std::cout << "AMateria parametrized constructor called for type: " << type << "\n";
}

AMateria::AMateria(const AMateria& other) : _type(other._type)
{
    // std::cout << "AMateria copy constructor called\n";
}

AMateria& AMateria::operator=(const AMateria& other)
{
    if (this != &other) {}
    // std::cout << "AMateria copy assignment operator called\n";
    return *this;
}

AMateria::~AMateria()
{
    // std::cout << "AMateria destructor called\n";
}

std::string const & AMateria::getType() const
{
    return this->_type;
}

void AMateria::use(ICharacter& target)
{
    std::cout << "* uses some unknown materia on " << target.getName() << " *\n";
}
