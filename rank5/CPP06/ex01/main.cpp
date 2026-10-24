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
#include <iostream>

int main()
{
    Data* data = new Data();
    data->id = 42;
    data->name = "Bureaucrat";

    std::cout << "Original pointer: " << data << std::endl;

    uintptr_t raw = Serializer::serialize(data);
    std::cout << "Serialized value: " << raw << std::endl;

    Data* after = Serializer::deserialize(raw);
    std::cout << "Deserialized pointer: " << after << std::endl;

    if (after == data)
        std::cout << "OK: deserialized pointer matches original" << std::endl;
    else
        std::cout << "KO: deserialized pointer does not match original" << std::endl;

    if (after->id == 42 && after->name == "Bureaucrat")
        std::cout << "OK: data content preserved" << std::endl;
    else
        std::cout << "KO: data content corrupted" << std::endl;

    delete data;
    return 0;
}
