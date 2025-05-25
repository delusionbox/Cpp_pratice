#include "character.h"
#include "monster.h"
#include "battle.h"
#include "item.h"
#include "shop.h"
#include "battleLog.h"
#include <iostream>

int main()
{
     Character player("ME", 100, 20, 100);
     Monster slime("slime", 40, 8);
     BattleLog log;

     int turn = 1;

     while (player.hp > 0 && slime.hp > 0)
     {
          cout << "\n[turn " << turn << "]" << endl;

          // player attack
          slime.hp -= player.atk;
          if (slime.hp < 0)
          {
               slime.hp = 0;
          };

          log.addLog("[turn " + to_string(turn) + "]" + player.name + "is" + slime.name + "attack" + to_string(player.atk) + "damage");

          if (slime.hp == 0)
          {
               log.addLog(slime.name + "is dead");
               break;
          };

          // monster counter attack
          player.hp -= slime.atk;
          if (player.hp < 0)
          {
               player.hp = 0;
          };

          log.addLog("[turn " + to_string(turn) + "]" + slime.name + "is attack" + to_string(slime.atk) + "damage");

          ++turn;
     }

     log.printLog();

     cout << "\nBattle End" << endl;
     cout << player.name << " HP: " << player.hp << endl;
     cout << slime.name << " HP: " << slime.hp << endl;

     return 0;

     /*
     Character player("ME", 100, 15, 100);
     Shop shop;

     cout << player.name << "have gold: " << player.gold << "\n"
          << endl;

     shop.showItems();

     cout << "\n item buying\n"
          << endl;
     shop.buyItem(0, player);

     player.printInventory();

     return 0;
     */

     /*
     Character player("ME", 100, 15);

     player.addItem(Item("small", 20));
     player.addItem(Item("middle", 50));

     cout << "current health: " << player.hp << endl;

     player.printInventory();
     player.useItem(0);

     return 0;
     */
     /*
     Character player("ME", 100, 20);
     Monster slime("Slime", 50, 10);

     cout << "Battle start\n";
     battle(player, slime);
     */
}