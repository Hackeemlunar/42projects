/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:30:00 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/06 22:30:00 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include <iostream>

Ice::Ice() : AMateria("ice")
{
    // std::cout << "Ice constructor called\n";
}

Ice::Ice(const Ice& other) : AMateria(other)
{
    // std::cout << "Ice copy constructor called\n";
}

Ice& Ice::operator=(const Ice& other)
{
    if (this != &other) {
        AMateria::operator=(other);
    }
    // std::cout << "Ice copy assignment operator called\n";
    return *this;
}

Ice::~Ice()
{
    // std::cout << "Ice destructor called\n";
}

AMateria* Ice::clone() const
{
    return new Ice(*this);
}

void Ice::use(ICharacter& target)
{
    std::cout << "* shoots an ice bolt at " << target.getName() << " *\n";
}
