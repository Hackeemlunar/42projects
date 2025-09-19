/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:30:40 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/15 16:37:18 by hmensah-         ###   ########.fr       */
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
const Animal* dog = new Dog();
const Animal* cat = new Cat();

std::cout << "\n===== Testing getTypes =====\n";
std::cout << dog->getType() << " " << std::endl;
std::cout << cat->getType() << " " << std::endl;

std::cout << "\n===== Testing makeSound =====\n";
cat->makeSound();
dog->makeSound();
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
delete dog;
delete cat;
delete meta;

return 0;
}