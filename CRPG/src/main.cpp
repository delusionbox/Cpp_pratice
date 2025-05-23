#include "character.h"
#include "monster.h"
#include "battle.h"
#include "item.h"
#include <iostream>

int main()
{
    Character player("ME", 100, 15);

    player.addItem(Item("small", 20));
    player.addItem(Item("middle", 50));

    cout << "current health: " << player.hp << endl;

    player.printInventory();
    player.useItem(0);

    return 0;

    /*
    Character player("ME", 100, 20);
    Monster slime("Slime", 50, 10);

    cout << "Battle start\n";
    battle(player, slime);
    */
}