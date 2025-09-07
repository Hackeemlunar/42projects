/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:46:20 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/06 17:25:18 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal
{
protected:
    std::string _type;

public:
    Animal();
    Animal& operator=(const Animal& other);
    Animal(const Animal& other);
    virtual ~Animal();

    virtual void makeSound() const = 0;
    virtual const std::string& getType() const;
};

#endif
