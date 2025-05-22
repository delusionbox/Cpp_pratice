#include "battle.h"
#include <iostream>

void battle(Character &player, Monster &monster)
{
    while (player.isAlive() && monster.isAlive())
    {
        monster.takeDamage(player.attack());
        if (!monster.isAlive())
            break;

        player.takeDamage(monster.attack());
    }

    if (player.isAlive())
        cout << "Player Win\n";
    else
        cout << "Monster Win\n";
}