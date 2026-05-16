#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(NULL));

    std::cout << "--- Test 1: ShrubberyCreationForm ---" << std::endl;
    try {
        Bureaucrat b("Alice", 136);
        ShrubberyCreationForm f("home");
        std::cout << f;
        b.signForm(f);
        b.executeForm(f);
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    std::cout << "--- Test 2: Execute unsigned form ---" << std::endl;
    try {
        Bureaucrat b("Bob", 1);
        ShrubberyCreationForm f("garden");
        b.executeForm(f);
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    std::cout << "--- Test 3: RobotomyRequestForm ---" << std::endl;
    try {
        Bureaucrat b("Charlie", 45);
        RobotomyRequestForm f("Bender");
        b.signForm(f);
        b.executeForm(f);
        b.executeForm(f);
        b.executeForm(f);
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    std::cout << "--- Test 4: Grade too low to execute ---" << std::endl;
    try {
        Bureaucrat signer("Dave", 72);
        Bureaucrat exec("Eve", 46);
        RobotomyRequestForm f("Wall-E");
        signer.signForm(f);
        exec.executeForm(f);
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    std::cout << "--- Test 5: PresidentialPardonForm ---" << std::endl;
    try {
        Bureaucrat b("Zaphod", 5);
        PresidentialPardonForm f("Arthur Dent");
        b.signForm(f);
        b.executeForm(f);
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    std::cout << "--- Test 6: Grade too low to sign ---" << std::endl;
    try {
        Bureaucrat b("Intern", 100);
        PresidentialPardonForm f("Ford Prefect");
        b.signForm(f);
        b.executeForm(f);
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << '\n';

    return 0;
}
