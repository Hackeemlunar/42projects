/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:17:05 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/19 20:34:58 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class AForm
{
private:
    const std::string   _name;
    bool                _signed;
    const int           _gradeToSign;
    const int           _gradeToExecute;

public:
    class GradeTooHighException : public std::exception {
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
        const char* what() const throw();
    };

    class FormNotSignedException : public std::exception {
        const char* what() const throw();
    };

    AForm();
    AForm(const std::string& name, int gradeToSign, int gradeToExecute);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);
    virtual ~AForm();

    const std::string&  getName() const;
    bool                getSigned() const;
    int                 getGradeToSign() const;
    int                 getGradeToExecute() const;

    void                beSigned(const Bureaucrat& b);
    void                checkExecute(const Bureaucrat& executor) const;
    virtual void        execute(Bureaucrat const& executor) const = 0;
};

std::ostream& operator<<(std::ostream& out, const AForm& f);

#endif
