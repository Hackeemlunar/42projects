/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:17:05 by hmensah-          #+#    #+#             */
/*   Updated: 2026/05/16 16:05:33 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
# include <iostream>
#include <exception>

class Form;

class Bureaucrat
{
private:
    const std::string _name;
    int _grade;

public:
    class GradeTooHighException : public std::exception {
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
        const char* what() const throw();
    };

    Bureaucrat();
    Bureaucrat& operator=(const Bureaucrat& other);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat(const std::string& name, int grade);
    ~Bureaucrat();

    const std::string& getName() const;
    int getGrade() const;
    void incrementGrade();
    void decrementGrade();
    void signForm(Form& f);
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat& in);

#endif