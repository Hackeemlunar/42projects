/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 17:53:55 by hmensah-          #+#    #+#             */
/*   Updated: 2026/10/17 17:53:57 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string>
#include <stdint.h>

struct Data
{
    int id;
    std::string name;

    Data() : id(0), name("")
    {
    }
};

class Serializer
{
private:
    Serializer();
    ~Serializer();
    Serializer(const Serializer& other);
    Serializer& operator=(const Serializer& other);

public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};

#endif
