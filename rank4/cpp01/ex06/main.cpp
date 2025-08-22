/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:15:47 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/21 12:38:38 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

int main(int argc, char **argv) {
    Harl instance;

    if (argc != 2 ) {
        std::cerr << "Error: Usage <filename> LEVEL\n";
        return 1;
    }
    
    std::string level = std::string(argv[1]);
    instance.complain(level);
    return 0;
}
