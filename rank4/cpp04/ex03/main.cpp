/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:30:00 by hmensah-          #+#    #+#             */
/*   Updated: 2025/09/16 17:03:13 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include <iostream>

int mainTest()
{
    IMateriaSource* src = new MateriaSource();

    AMateria* ice = new Ice();
    AMateria* cure = new Cure();

    src->learnMateria(ice);
    src->learnMateria(cure);
    delete ice;
    delete cure;

    ICharacter* me = new Character("me");

    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);

    delete bob;
    delete me;
    delete src;

    return 0;
}

int main()
{
    std::cout << "\n===== Subject Test =====\n";
    {
        mainTest();
    }

    std::cout << "\n===== Additional Tests =====\n";
    
    std::cout << "\n--- Testing inventory full ---\n";
    {
        MateriaSource* src = new MateriaSource();
        AMateria* ice = new Ice();
        src->learnMateria(ice);
        delete ice;
        
        Character* hero = new Character("hero");
        
        for (int i = 0; i < 6; i++) {
            AMateria* materia = src->createMateria("ice");
            hero->equip(materia);
            if (i >= 4) {
                delete materia; // Clean up when inventory is full
            }
        }
        hero->use(0, *hero);
        hero->use(3, *hero);
        
        delete hero;
        delete src;
    }
    
    std::cout << "\n--- Testing unequip ---\n";
    {
        MateriaSource* src = new MateriaSource();
        
        AMateria* tempIce = new Ice();
        AMateria* tempCure = new Cure();
    
        src->learnMateria(tempIce);
        src->learnMateria(tempCure);
        delete tempIce;
        delete tempCure;
        
        Character* mage = new Character("mage");
        Character* target = new Character("target");
        
        AMateria* ice = src->createMateria("ice");
        AMateria* cure = src->createMateria("cure");
        
        mage->equip(ice);
        mage->equip(cure);
        
        mage->use(0, *target);
        mage->use(1, *target);
        
        // Unequip and save addresses to avoid leaks
        mage->unequip(0);
        mage->unequip(1);
        
        // Try to use after unequip
        mage->use(0, *target);
        mage->use(1, *target);
        
        delete target;
        delete mage;
        delete src;
        
        // Clean up unequipped materias
        delete ice;
        delete cure;
    }
    
    std::cout << "\n--- Testing edge cases ---\n";
    {
        MateriaSource* src = new MateriaSource();
        Character* user = new Character("user");
        Character* victim = new Character("victim");
        
        // Try to create unknown materia
        AMateria* unknown = src->createMateria("unknown");
        user->equip(unknown);
        
        // Try to use invalid slots
        user->use(-1, *victim);
        user->use(10, *victim);
        
        // Try to unequip invalid slots
        user->unequip(-1);
        user->unequip(10);
        user->unequip(0); // empty slot
        
        delete victim;
        delete user;
        delete src;
    }
    
    std::cout << "\n--- Testing deep copy ---\n";
    {
        Character original("original");
        
        MateriaSource* src = new MateriaSource();
        AMateria* tempIce = new Ice();
        AMateria* tempCure = new Cure();
    
        src->learnMateria(tempIce);
        src->learnMateria(tempCure);
        delete tempIce;
        delete tempCure;
        
        original.equip(src->createMateria("ice"));
        original.equip(src->createMateria("cure"));
        
        std::cout << "\n-- Copy constructor --\n";
        Character copy1(original);
        
        std::cout << "\n-- Assignment operator --\n";
        Character copy2("empty");
        copy2 = original;
        
        std::cout << "\n-- Test that copies are independent --\n";
        Character target("target");
        
        std::cout << "Original using materias:\n";
        original.use(0, target);
        original.use(1, target);
        
        std::cout << "Copy1 using materias:\n";
        copy1.use(0, target);
        copy1.use(1, target);
        
        std::cout << "Copy2 using materias:\n";
        copy2.use(0, target);
        copy2.use(1, target);
        
        delete src;
    }
    
    return 0;
}
