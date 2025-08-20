/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 20:39:33 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/18 17:07:50 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
private:
    std::string _type;

public:
    Weapon(const std::string& type);
    ~Weapon();

    const std::string& getType() const;
    void setType(const std::string& newType);
};

#endif