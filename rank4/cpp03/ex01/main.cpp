/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 23:19:53 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/30 23:25:34 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    
    std::cout << "=== Testing ClapTrap ===" << std::endl;
    ClapTrap clap("ClapBot");
    clap.attack("target1");
    clap.beRepaired(5);
    clap.takeDamage(3);
    
    std::cout << "\n=== Testing ScavTrap ===" << std::endl;
    ScavTrap scav("ScavBot");
    scav.attack("target2");
    scav.beRepaired(10);
    scav.takeDamage(25);
    scav.guardGate();
    
    std::cout << "\n=== Testing construction/destruction chaining ===" << std::endl;
    {
        ScavTrap temp("TempScav");
    }
    
    std::cout << "\n=== End of main ===" << std::endl;
    return 0;
}
