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

#include "Base.hpp"
#include <iostream>

int main()
{
    for (int i = 0; i < 6; ++i)
    {
        Base* object = generate();

        std::cout << "identify(pointer): ";
        identify(object);
        std::cout << "identify(reference): ";
        identify(*object);

        delete object;
    }
    return 0;
}
