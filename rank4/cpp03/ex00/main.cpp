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
#include <iostream>


int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    ClapTrap jnr;
    jnr.attack("john");
    jnr.beRepaired(5);
    jnr.takeDamage(2);

    return 0;
}