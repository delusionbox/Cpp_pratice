#include "character.h"
#include "monster.h"
#include "battle.h"
#include <iostream>

int main()
{
    Character player("ME", 100, 20);
    Monster slime("Slime", 50, 10);

    cout << "Battle start\n";
    battle(player, slime);
}