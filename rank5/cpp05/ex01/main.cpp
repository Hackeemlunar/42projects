/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 15:57:00 by hmensah-          #+#    #+#             */
/*   Updated: 2026/05/16 16:24:17 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    std::cout << "--- Test 1: Form construction and output ---" << std::endl;
    try {
        Form f("TaxReturn", 50, 25);
        std::cout << f;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    std::cout << "--- Test 2: Form grade too high (0) ---" << std::endl;
    try {
        Form f("BadForm", 0, 25);
        std::cout << f;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    std::cout << "--- Test 3: Form grade too low (151) ---" << std::endl;
    try {
        Form f("BadForm", 151, 25);
        std::cout << f;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    std::cout << "--- Test 4: Successful signing ---" << std::endl;
    try {
        Bureaucrat b("Alice", 30);
        Form f("Permit", 50, 25);
        std::cout << b;
        std::cout << f;
        b.signForm(f);
        std::cout << f;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    std::cout << "--- Test 5: Grade too low to sign ---" << std::endl;
    try {
        Bureaucrat b("Bob", 100);
        Form f("Not-Permitted", 50, 25);
        std::cout << b;
        std::cout << f;
        b.signForm(f);
        std::cout << f;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    std::cout << "--- Test 6: Exact grade to sign ---" << std::endl;
    try {
        Bureaucrat b("Charlie", 50);
        Form f("License", 50, 10);
        b.signForm(f);
        std::cout << f;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    return 0;
}