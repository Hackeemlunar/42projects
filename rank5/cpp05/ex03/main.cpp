#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(NULL));

    Intern someRandomIntern;

    std::cout << "--- Test 1: Intern creates robotomy request ---" << std::endl;
    {
        AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        if (rrf) {
            Bureaucrat b("Alice", 45);
            b.signForm(*rrf);
            b.executeForm(*rrf);
            delete rrf;
        }
    }
    std::cout << '\n';

    std::cout << "--- Test 2: Intern creates shrubbery creation ---" << std::endl;
    {
        AForm* scf = someRandomIntern.makeForm("shrubbery creation", "office");
        if (scf) {
            Bureaucrat b("Bob", 136);
            b.signForm(*scf);
            b.executeForm(*scf);
            delete scf;
        }
    }
    std::cout << '\n';

    std::cout << "--- Test 3: Intern creates presidential pardon ---" << std::endl;
    {
        AForm* ppf = someRandomIntern.makeForm("presidential pardon", "Marvin");
        if (ppf) {
            Bureaucrat b("Zaphod", 5);
            b.signForm(*ppf);
            b.executeForm(*ppf);
            delete ppf;
        }
    }
    std::cout << '\n';

    std::cout << "--- Test 4: Unknown form ---" << std::endl;
    {
        AForm* unknown = someRandomIntern.makeForm("form 28B", "someone");
        if (unknown)
            delete unknown;
    }
    std::cout << '\n';

    return 0;
}
