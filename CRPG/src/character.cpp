#include "character.h"
#include <iostream>

Character::Character(string name, int hp, int atk)
    : name(name), hp(hp), atk(atk) {}

void Character::takeDamage(int dmg)
{
    hp -= dmg;
};

bool Character::isAlive() const
{
    return hp > 0;
};

int Character::attack() const
{
    return atk;
};

void Character::showStatus() const
{
    cout << name << " - HP: " << hp << "\n";
}