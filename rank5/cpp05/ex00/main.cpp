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
#include <iostream>

int main()
{
    std::cout << "=== Test 1: Valid Bureaucrat Creation ===" << std::endl;
    try
    {
        Bureaucrat bob("Bob", 75);
        std::cout << bob << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 2: Grade Too High Exception ===" << std::endl;
    try
    {
        Bureaucrat alice("Alice", 0);
        std::cout << alice << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 3: Grade Too Low Exception ===" << std::endl;
    try
    {
        Bureaucrat charlie("Charlie", 151);
        std::cout << charlie << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 4: Increment Grade ===" << std::endl;
    try
    {
        Bureaucrat diana("Diana", 2);
        std::cout << diana << std::endl;
        diana.incrementGrade();
        std::cout << "After increment: " << diana << std::endl;
        diana.incrementGrade(); // This should throw
        std::cout << "After increment: " << diana << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 5: Decrement Grade ===" << std::endl;
    try
    {
        Bureaucrat eve("Eve", 149);
        std::cout << eve << std::endl;
        eve.decrementGrade();
        std::cout << "After decrement: " << eve << std::endl;
        eve.decrementGrade(); // This should throw
        std::cout << "After decrement: " << eve << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 6: Copy Constructor ===" << std::endl;
    try
    {
        Bureaucrat frank("Frank", 100);
        Bureaucrat frankCopy(frank);
        std::cout << "Original: " << frank << std::endl;
        std::cout << "Copy: " << frankCopy << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 7: Assignment Operator ===" << std::endl;
    try
    {
        Bureaucrat grace("Grace", 50);
        Bureaucrat henry("Henry", 100);
        std::cout << "Before assignment:" << std::endl;
        std::cout << grace << std::endl;
        std::cout << henry << std::endl;
        
        grace = henry;
        std::cout << "After assignment (grace = henry):" << std::endl;
        std::cout << grace << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
