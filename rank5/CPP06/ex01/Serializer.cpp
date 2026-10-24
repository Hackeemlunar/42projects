/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 17:53:48 by hmensah-          #+#    #+#             */
/*   Updated: 2026/10/17 17:53:50 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer()
{
}

Serializer::~Serializer()
{
}

Serializer::Serializer(const Serializer& other)
{
    (void)other;
}

Serializer& Serializer::operator=(const Serializer& other)
{
    (void)other;
    return *this;
}

uintptr_t Serializer::serialize(Data* ptr)
{
    if (!ptr)
        return 0;
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}
