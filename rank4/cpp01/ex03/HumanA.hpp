/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:29:07 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/18 16:50:29 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"
#include <string>

class HumanA {
private:
    Weapon&      _weapon;
    std::string _name;

public:
    HumanA(const std::string& name, Weapon& weapon);
    ~HumanA();
    void attack() const;
};

#endif