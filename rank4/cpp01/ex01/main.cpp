/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:38:43 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/17 17:57:47 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

int main() {
    int numOfHorde = 15;

    Zombie* horde = zombieHorde(numOfHorde, "James Bond");

    if (horde == nullptr)
        return 0;
    for (int i = 0; i < numOfHorde; i++)
        horde[i].announce();

    std::cout << "\n";

    delete[] horde;
    
    return 0;
}
