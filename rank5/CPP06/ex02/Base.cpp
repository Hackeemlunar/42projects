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

Base::~Base()
{
}
Base* Base::generate(void)
{
    int r = rand() % 3;
    
    if (r == 0)
        return new A();
    else if (r == 1)
        return new B();
    else
        return new C();
}

void Base::identify(Base* p)
{
    Base* ptr = dynamic_cast<A*>(p);
    if(ptr != NULL)
    {
        std::cout << "pointer is type A" << std::endl;
        return;
    }
    ptr = dynamic_cast<B*>(p);
    if(ptr != NULL)
    {
        std::cout << "pointer is type B" << std::endl;
        return;
    }
    ptr = dynamic_cast<C*>(p);
    if(ptr != NULL)
    {
        std::cout << "pointer is type C" << std::endl;
        return;
    }
    std::cout << "Unknown Type" << std::endl;
}

void Base::identify(Base& p)
{
    try
    {
        A& a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << "reference is type A" << std::endl;
        return;
    }
    catch(const std::exception& e)
    {
    }
    try
    {
        B& b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << "reference is type B" << std::endl;
        return;
    }
    catch(const std::exception& e)
    {
    }
    try
    {
        C& c = dynamic_cast<C&>(p);
        (void)c;
        std::cout << "reference is type C" << std::endl;
        return;
    }
    catch(const std::exception& e)
    {
    }
    std::cout << "Unknown Type" << std::endl;
}