/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:58:01 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/16 23:06:01 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Zombie.hpp
# define Zombie.hpp

#include <string>

class Zombie
{
private:
    std::string _name;

public:
    Zombie();
    ~Zombie();
    
    void announce(void);
};

#endif