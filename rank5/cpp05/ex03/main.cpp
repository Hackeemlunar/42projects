#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Test 1: Create Robotomy Request Form ===" << std::endl;
    {
        Intern someRandomIntern;
        AForm* rrf;
        
        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        
        if (rrf)
        {
            std::cout << *rrf << std::endl;
            
            Bureaucrat boss("Boss", 1);
            boss.signForm(*rrf);
            boss.executeForm(*rrf);
            
            delete rrf;
        }
    }

    std::cout << "\n=== Test 2: Create Shrubbery Creation Form ===" << std::endl;
    {
        Intern intern;
        AForm* form;
        
        form = intern.makeForm("shrubbery creation", "garden");
        
        if (form)
        {
            std::cout << *form << std::endl;
            
            Bureaucrat gardener("Gardener", 100);
            gardener.signForm(*form);
            gardener.executeForm(*form);
            
            delete form;
        }
    }

    std::cout << "\n=== Test 3: Create Presidential Pardon Form ===" << std::endl;
    {
        Intern intern;
        AForm* form;
        
        form = intern.makeForm("presidential pardon", "Arthur Dent");
        
        if (form)
        {
            std::cout << *form << std::endl;
            
            Bureaucrat president("President", 1);
            president.signForm(*form);
            president.executeForm(*form);
            
            delete form;
        }
    }

    std::cout << "\n=== Test 4: Invalid Form Name ===" << std::endl;
    {
        Intern intern;
        AForm* form;
        
        form = intern.makeForm("invalid form", "Target");
        
        if (!form)
        {
            std::cout << "Form creation failed as expected." << std::endl;
        }
        else
        {
            delete form;
        }
    }

    std::cout << "\n=== Test 5: Multiple Forms from Same Intern ===" << std::endl;
    {
        Intern intern;
        Bureaucrat vip("VIP", 1);
        
        AForm* form1 = intern.makeForm("robotomy request", "Marvin");
        AForm* form2 = intern.makeForm("shrubbery creation", "park");
        AForm* form3 = intern.makeForm("presidential pardon", "Trillian");
        
        if (form1)
        {
            vip.signForm(*form1);
            vip.executeForm(*form1);
            delete form1;
        }
        
        if (form2)
        {
            vip.signForm(*form2);
            vip.executeForm(*form2);
            delete form2;
        }
        
        if (form3)
        {
            vip.signForm(*form3);
            vip.executeForm(*form3);
            delete form3;
        }
    }

    std::cout << "\n=== Test 6: Case Sensitivity Test ===" << std::endl;
    {
        Intern intern;
        AForm* form;
        
        form = intern.makeForm("Robotomy Request", "Test");
        
        if (!form)
        {
            std::cout << "Form creation failed due to case sensitivity." << std::endl;
        }
        else
        {
            delete form;
        }
    }

    return 0;
}
