/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 23:19:53 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/02 14:55:05 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    
    std::cout << "===== Testing ClapTrap =====\n";
    ClapTrap clap("ClapBot");
    clap.attack("target1");
    clap.beRepaired(5);
    clap.takeDamage(3);
    
    std::cout << "\n===== Testing ScavTrap =====\n";
    ScavTrap scav("ScavBot");
    scav.attack("target2");
    scav.beRepaired(10);
    scav.takeDamage(25);
    scav.guardGate();
    
    std::cout << "\n===== Testing construction/destruction chaining =====\n";
    {
        ScavTrap temp("TempScav");
    }
    
    std::cout << "\n===== End of main =====\n";
    return 0;
}
