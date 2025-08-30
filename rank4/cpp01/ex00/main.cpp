/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:38:43 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/17 17:11:46 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

int main() {
    std::cout << "Creating a zombie on the heap...\n";
    Zombie* heapZombie = newZombie("HeapZombie");
    
    heapZombie->announce();

    delete heapZombie;
    heapZombie = NULL;

    std::cout << "\n";

    std::cout << "Creating a zombie on the stack...\n";
    randomChump("StackZombie");

    return 0;
}
