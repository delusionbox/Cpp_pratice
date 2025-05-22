#include "monster.h"
#include <iostream>

Monster::Monster(string name, int hp, int atk)
    : name(name), hp(hp), atk(atk) {}

void Monster::takeDamage(int dmg)
{
    hp -= dmg;
};

bool Monster::isAlive() const
{
    return hp > 0;
};

int Monster::attack() const
{
    return atk;
};

void Monster::showStatus() const
{
    cout << name << " - HP: " << hp << "\n";
}