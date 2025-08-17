/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:43:47 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/17 20:34:31 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

int main() {
    std::string  str        = "HI THIS IS BRAIN";
    std::string* stringPTR  = &str;
    std::string& stringREF  = str;

    std::cout << &str       << "\n";
    std::cout << stringPTR  << "\n";
    std::cout << &stringREF << "\n";

    std::cout << "\n";

    std::cout << str        << "\n";
    std::cout << *stringPTR  << "\n";
    std::cout << stringREF  << "\n";

    return 0;
}