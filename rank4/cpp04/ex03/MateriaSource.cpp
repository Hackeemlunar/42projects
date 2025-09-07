/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:30:00 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/06 22:30:00 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include <iostream>

MateriaSource::MateriaSource()
{
    for (int i = 0; i < 4; i++) {
        this->_templates[i] = NULL;
    }
    // std::cout << "MateriaSource constructor called\n";
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
    for (int i = 0; i < 4; i++) {
        if (other._templates[i] != NULL) {
            this->_templates[i] = other._templates[i]->clone();
        } else {
            this->_templates[i] = NULL;
        }
    }
    // std::cout << "MateriaSource copy constructor called\n";
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
    if (this != &other) {
        // Delete existing templates
        for (int i = 0; i < 4; i++) {
            if (this->_templates[i] != NULL) {
                delete this->_templates[i];
                this->_templates[i] = NULL;
            }
        }
        
        // Deep copy the other's templates
        for (int i = 0; i < 4; i++) {
            if (other._templates[i] != NULL) {
                this->_templates[i] = other._templates[i]->clone();
            }
        }
    }
    // std::cout << "MateriaSource copy assignment operator called\n";
    return *this;
}

MateriaSource::~MateriaSource()
{
    for (int i = 0; i < 4; i++) {
        if (this->_templates[i] != NULL) {
            delete this->_templates[i];
        }
    }
    // std::cout << "MateriaSource destructor called\n";
}

void MateriaSource::learnMateria(AMateria* m)
{
    if (m == NULL) {
        return;
    }
    
    for (int i = 0; i < 4; i++) {
        if (this->_templates[i] == NULL) {
            this->_templates[i] = m->clone();
            return;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
    for (int i = 0; i < 4; i++) {
        if (this->_templates[i] != NULL && this->_templates[i]->getType() == type) {
            return this->_templates[i]->clone();
        }
    }
    return NULL;
}
