/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:17:05 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/19 20:34:58 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include "AForm.hpp"

class Intern
{
private:
    // Private helper methods for creating each form type
    AForm* createShrubberyForm(const std::string& target) const;
    AForm* createRobotomyForm(const std::string& target) const;
    AForm* createPresidentialForm(const std::string& target) const;

public:
    // Orthodox Canonical Form
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();

    // Main method
    AForm* makeForm(const std::string& formName, const std::string& target) const;
};

#endif
