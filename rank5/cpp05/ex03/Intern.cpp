/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:19:39 by hmensah-          #+#    #+#             */
/*   Updated: 2026/05/16 17:36:15 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern() {}
Intern::Intern(const Intern&) {}
Intern& Intern::operator=(const Intern&) { return *this; }
Intern::~Intern() {}

static AForm* makeShrubbery(const std::string& target) {
    return new ShrubberyCreationForm(target);
}
static AForm* makeRobotomy(const std::string& target) {
    return new RobotomyRequestForm(target);
}
static AForm* makePardon(const std::string& target) {
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const {
    struct {
        const char* name;
        AForm* (*create)(const std::string&);
    } forms[] = {
        { "shrubbery creation", makeShrubbery },
        { "robotomy request",   makeRobotomy  },
        { "presidential pardon", makePardon   }
    };

    for (std::size_t i = 0; i < 3; i++) {
        if (formName == forms[i].name) {
            std::cout << "Intern creates " << formName << "\n";
            return forms[i].create(target);
        }
    }
    std::cout << "Intern: unknown form \"" << formName << "\"\n";
    return NULL;
}
