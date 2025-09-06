/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:30:40 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/06 21:04:28 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "WrongAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main()
{
const Animal* meta = new Animal();
const Animal* j = new Dog();
const Animal* i = new Cat();

std::cout << "\n===== Testing getTypes =====\n";
std::cout << j->getType() << " " << std::endl;
std::cout << i->getType() << " " << std::endl;

std::cout << "\n===== Testing makeSound =====\n";
i->makeSound(); //will output the cat sound!
j->makeSound();
meta->makeSound();

{
    std::cout << "\n===== Testing with WrongCat =====\n";
    const WrongAnimal* wrongCat = new WrongCat();
    std::cout << wrongCat->getType() << " " << std::endl;
    wrongCat->makeSound();
    delete wrongCat;
    std::cout << "===== Done Testing WrongCat =====\n";
}

std::cout << "\n===== Testing cleanup =====\n";
delete j;
delete i;
delete meta;

return 0;
}