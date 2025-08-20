/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:10:43 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/18 16:40:03 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>

class HumanB
{
private:
    std::string _name;
    Weapon *_weapon;

public:
    HumanB(const std::string &name);
    ~HumanB();

    void setWeapon(const Weapon &weapon);
    void attack() const;
};

#endif