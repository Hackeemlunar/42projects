/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:19:39 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/19 20:36:42 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

// Default constructor
Intern::Intern()
{
    std::cout << "Intern default constructor called" << std::endl;
}

// Copy constructor
Intern::Intern(const Intern& other)
{
    (void)other;
    std::cout << "Intern copy constructor called" << std::endl;
}

// Assignment operator
Intern& Intern::operator=(const Intern& other)
{
    (void)other;
    std::cout << "Intern assignment operator called" << std::endl;
    return *this;
}

// Destructor
Intern::~Intern()
{
    std::cout << "Intern destructor called" << std::endl;
}

// Private helper methods
AForm* Intern::createShrubberyForm(const std::string& target) const
{
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyForm(const std::string& target) const
{
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialForm(const std::string& target) const
{
    return new PresidentialPardonForm(target);
}

// makeForm method - uses function pointer array to avoid messy if/else
AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
    // Array of form names
    const std::string formNames[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    
    // Array of function pointers (member function pointers)
    typedef AForm* (Intern::*FormCreator)(const std::string&) const;
    FormCreator formCreators[3] = {
        &Intern::createShrubberyForm,
        &Intern::createRobotomyForm,
        &Intern::createPresidentialForm
    };
    
    // Find matching form name and create it
    for (int i = 0; i < 3; i++)
    {
        if (formName == formNames[i])
        {
            std::cout << "Intern creates " << formName << std::endl;
            return (this->*formCreators[i])(target);
        }
    }
    
    // No matching form found
    std::cerr << "Error: Form name '" << formName << "' does not exist!" << std::endl;
    return NULL;
}
