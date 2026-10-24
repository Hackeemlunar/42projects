/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 17:55:06 by hmensah-          #+#    #+#             */
/*   Updated: 2026/10/17 17:55:07 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

Base::~Base()
{
}

Base *generate(void)
{
    static bool seeded = false;

    if (!seeded)
    {
        std::srand(std::time(NULL));
        seeded = true;
    }

    int choice = std::rand() % 3;
    if (choice == 0)
        return new A();
    if (choice == 1)
        return new B();
    return new C();
}

void identify(Base *p)
{
    if (dynamic_cast<A *>(p) != NULL)
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B *>(p) != NULL)
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C *>(p) != NULL)
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown" << std::endl;
}

void identify(Base &p)
{
    try
    {
        (void)dynamic_cast<A &>(p);
        std::cout << "A" << std::endl;
        return;
    }
    catch (const std::exception &)
    {
    }

    try
    {
        (void)dynamic_cast<B &>(p);
        std::cout << "B" << std::endl;
        return;
    }
    catch (const std::exception &)
    {
    }

    try
    {
        (void)dynamic_cast<C &>(p);
        std::cout << "C" << std::endl;
        return;
    }
    catch (const std::exception &)
    {
    }

    std::cout << "Unknown" << std::endl;
}
