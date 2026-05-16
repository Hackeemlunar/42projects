/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 15:57:00 by hmensah-          #+#    #+#             */
/*   Updated: 2026/05/16 15:57:05 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
    std::cout << "--- Test 1: Normal construction ---" << std::endl;
    try {
        Bureaucrat b("Alice", 75);
        std::cout << b;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "--- Test 2: Grade too high (0) ---" << std::endl;
    try {
        Bureaucrat b("Bob", 0);
        std::cout << b;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "--- Test 3: Grade too low (151) ---" << std::endl;
    try {
        Bureaucrat b("Charlie", 151);
        std::cout << b;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "--- Test 4: Increment past grade 1 ---" << std::endl;
    try {
        Bureaucrat b("Dave", 1);
        std::cout << b;
        b.incrementGrade();
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "--- Test 5: Decrement past grade 150 ---" << std::endl;
    try {
        Bureaucrat b("Eve", 150);
        std::cout << b;
        b.decrementGrade();
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "--- Test 6: Normal increment and decrement ---" << std::endl;
    try {
        Bureaucrat b("Frank", 50);
        std::cout << b;
        b.incrementGrade();
        std::cout << "After increment: " << b;
        b.decrementGrade();
        std::cout << "After decrement: " << b;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}