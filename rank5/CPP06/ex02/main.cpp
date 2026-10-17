/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 17:55:17 by hmensah-          #+#    #+#             */
/*   Updated: 2026/10/17 17:55:18 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Base.hpp"

int main()
{
    srand(time(NULL));
    Base* basePtr = Base::generate();
    Base& baseRef = *basePtr;
    Base* p5 = Base::generate();
    basePtr->identify(basePtr);
    basePtr->identify(baseRef);
    p5->identify(*p5);
    delete basePtr;
    delete p5;
    return 0;
}