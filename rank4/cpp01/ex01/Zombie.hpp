/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 22:58:01 by hmensah-          #+#    #+#             */
/*   Updated: 2025/08/30 19:50:06 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>

class Zombie {

private:
    std::string name;

public:
    Zombie();
    Zombie(const std::string &name);
    ~Zombie();
    
    void announce(void);
    void setName(const std::string &name);

    std::string getName() const;
};

Zombie* zombieHorde( int N, std::string name );

#endif
