/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:19:39 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/19 20:36:42 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Test 1: Valid Form Creation ===" << std::endl;
    try
    {
        Form taxForm("Tax Form", 50, 25);
        std::cout << taxForm << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 2: Form Grade Too High ===" << std::endl;
    try
    {
        Form invalidForm("Invalid Form", 0, 25);
        std::cout << invalidForm << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 3: Form Grade Too Low ===" << std::endl;
    try
    {
        Form invalidForm("Invalid Form", 151, 25);
        std::cout << invalidForm << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 4: Successful Form Signing ===" << std::endl;
    try
    {
        Bureaucrat alice("Alice", 30);
        Form requestForm("Request Form", 50, 25);
        
        std::cout << "Before signing: " << requestForm << std::endl;
        alice.signForm(requestForm);
        std::cout << "After signing: " << requestForm << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 5: Failed Form Signing (Grade Too Low) ===" << std::endl;
    try
    {
        Bureaucrat bob("Bob", 100);
        Form importantForm("Important Form", 50, 25);
        
        std::cout << "Before signing attempt: " << importantForm << std::endl;
        bob.signForm(importantForm);
        std::cout << "After signing attempt: " << importantForm << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 6: Edge Case - Grade 1 Bureaucrat ===" << std::endl;
    try
    {
        Bureaucrat boss("Boss", 1);
        Form topSecretForm("Top Secret Form", 1, 1);
        
        std::cout << boss << std::endl;
        std::cout << topSecretForm << std::endl;
        boss.signForm(topSecretForm);
        std::cout << "After signing: " << topSecretForm << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 7: Multiple Signing Attempts ===" << std::endl;
    try
    {
        Bureaucrat charlie("Charlie", 40);
        Bureaucrat diana("Diana", 60);
        Form mediumForm("Medium Form", 50, 25);
        
        std::cout << mediumForm << std::endl;
        diana.signForm(mediumForm);  // Should fail
        charlie.signForm(mediumForm); // Should succeed
        std::cout << "Final state: " << mediumForm << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
