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
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Test 1: ShrubberyCreationForm ===" << std::endl;
    try
    {
        Bureaucrat alice("Alice", 130);
        ShrubberyCreationForm shrubbery("home");
        
        std::cout << alice << std::endl;
        std::cout << shrubbery << std::endl;
        
        alice.signForm(shrubbery);
        alice.executeForm(shrubbery);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 2: RobotomyRequestForm ===" << std::endl;
    try
    {
        Bureaucrat bob("Bob", 40);
        RobotomyRequestForm robotomy("Bender");
        
        std::cout << bob << std::endl;
        std::cout << robotomy << std::endl;
        
        bob.signForm(robotomy);
        bob.executeForm(robotomy);
        bob.executeForm(robotomy); // Try again for different result
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 3: PresidentialPardonForm ===" << std::endl;
    try
    {
        Bureaucrat president("President", 1);
        PresidentialPardonForm pardon("Arthur Dent");
        
        std::cout << president << std::endl;
        std::cout << pardon << std::endl;
        
        president.signForm(pardon);
        president.executeForm(pardon);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 4: Execute Unsigned Form ===" << std::endl;
    try
    {
        Bureaucrat charlie("Charlie", 1);
        PresidentialPardonForm unsignedPardon("Ford Prefect");
        
        std::cout << "Attempting to execute unsigned form..." << std::endl;
        charlie.executeForm(unsignedPardon); // Should fail - not signed
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 5: Insufficient Grade to Execute ===" << std::endl;
    try
    {
        Bureaucrat lowGrade("LowGrade", 50);
        PresidentialPardonForm pardon("Zaphod");
        Bureaucrat highGrade("HighGrade", 1);
        
        highGrade.signForm(pardon);
        lowGrade.executeForm(pardon); // Should fail - grade too low
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 6: Multiple Forms ===" << std::endl;
    try
    {
        Bureaucrat admin("Admin", 1);
        
        ShrubberyCreationForm shrub1("garden");
        ShrubberyCreationForm shrub2("park");
        RobotomyRequestForm robot("Marvin");
        PresidentialPardonForm pardon("Trillian");
        
        admin.signForm(shrub1);
        admin.signForm(shrub2);
        admin.signForm(robot);
        admin.signForm(pardon);
        
        std::cout << "\n--- Executing all forms ---" << std::endl;
        admin.executeForm(shrub1);
        admin.executeForm(shrub2);
        admin.executeForm(robot);
        admin.executeForm(pardon);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
