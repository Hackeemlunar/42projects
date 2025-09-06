/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:24:54 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/06 22:03:56 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
    std::cout << "Brain default constructor called\n";
}

Brain::Brain(const Brain& other) {
    for (size_t i = 0; i < 100; i++) {
        this->_ideas[i] = other._ideas[i];
    }
    std::cout << "Brain copy constructor called\n";
}

Brain& Brain::operator=(const Brain& other) {
    if (this != &other) {
        for (size_t i = 0; i < 100; i++) {
            this->_ideas[i] = other._ideas[i];
        }
    }
    std::cout << "Brain copy assignment operator called\n";
    return *this;
}

Brain::~Brain() {
    std::cout << "Brain destructor called\n";
}
