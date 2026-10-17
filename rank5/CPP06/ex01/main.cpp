/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 17:53:29 by hmensah-          #+#    #+#             */
/*   Updated: 2026/10/17 17:53:31 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Serializer.hpp"

int main()
{
    Serializer *a = NULL;
    Data *b = new Data();
    uintptr_t raw;
    Data *after;
    std::cout << "Original pointer: " << b << std::endl;
    raw = a->serialize(b);
    std::cout << "Serialized to uintptr_t: " << raw << std::endl;
    after = a->deserialize(raw);
    std::cout << "Deserialized back to pointer: " << after << std::endl;
    delete b;
    return 0;

}