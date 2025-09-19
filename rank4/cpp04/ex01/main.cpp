/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:30:40 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/15 17:16:15 by hmensah-         ###   ########.fr       */
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
    std::cout << "\n===== Testing basic polymorphism =====\n";
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    
    delete j;
    delete i;

    std::cout << "\n===== Testing array of Animals =====\n";
    const int arraySize = 10;
    const Animal* animals[arraySize];
    
    // Fill half with Dogs, half with Cats
    for (int idx = 0; idx < arraySize; idx++) {
        if (idx < arraySize / 2) {
            animals[idx] = new Dog();
        } else {
            animals[idx] = new Cat();
        }
    }
    
    std::cout << "\n===== Testing sounds =====\n";
    for (int idx = 0; idx < arraySize; idx++) {
        std::cout << "Animal " << idx << " (" << animals[idx]->getType() << "): ";
        animals[idx]->makeSound();
    }
    
    std::cout << "\n===== Cleaning up array =====\n";
    for (int idx = 0; idx < arraySize; idx++) {
        delete animals[idx];
    }

    std::cout << "\n===== Testing deep copy with Dogs =====\n";
    {
        Dog original;
        std::cout << "\n--- Creating copy using copy constructor ---\n";
        Dog copy1(original);
        
        std::cout << "\n--- Creating copy using assignment operator ---\n";
        Dog copy2;
        copy2 = original;
        
        std::cout << "\n--- Testing that copies are independent ---\n";
        std::cout << "Original address: " << &original << std::endl;
        std::cout << "Copy1 address: " << &copy1 << std::endl;
        std::cout << "Copy2 address: " << &copy2 << std::endl;
        
        std::cout << "\n--- End of scope, destructors will be called ---\n";
    }
    
    std::cout << "\n===== Testing deep copy with Cats =====\n";
    {
        Cat original;
        std::cout << "\n--- Creating copy using copy constructor ---\n";
        Cat copy1(original);
        
        std::cout << "\n--- Creating copy using assignment operator ---\n";
        Cat copy2;
        copy2 = original;
        
        std::cout << "\n--- Testing that copies are independent ---\n";
        std::cout << "Original address: " << &original << std::endl;
        std::cout << "Copy1 address: " << &copy1 << std::endl;
        std::cout << "Copy2 address: " << &copy2 << std::endl;
        
        std::cout << "\n--- End of scope, destructors will be called ---\n";
    }

    return 0;
}