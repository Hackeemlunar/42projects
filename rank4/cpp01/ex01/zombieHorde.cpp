/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:30:09 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/17 17:47:31 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

Zombie* zombieHorde( int N, std::string name ) {
    if (N <= 0) {
        std::cout << "Can't create 0 or less horde\n";
        return nullptr;
    }

    Zombie* horde = new Zombie[N];

    for (int i = 0; i < N; i++) {
        horde[i].setName(name);
    }

    return horde;
}