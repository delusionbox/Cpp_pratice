#include "character.h"
#include <iostream>

Character::Character(string name, int hp, int atk, int gold)
    : name(name), hp(hp), maxHp(hp), atk(atk), gold(gold) {}

void Character::addItem(const Item &item)
{
    inventory.push_back(item);
    cout << item.name << " Add inventory" << endl;
}

void Character::useItem(int index)
{
    if (index < 0 || index >= inventory.size())
    {
        cout << "wrong index" << endl;
        return;
    }

    Item item = inventory[index];
    item.use();

    hp += item.healAmount;
    if (hp > maxHp)
    {
        hp = maxHp;
    };

    inventory.erase(inventory.begin() + index);
}

void Character::printInventory() const
{
    cout << "======Inventory======" << endl;
    if (inventory.empty())
    {
        cout << "No item" << endl;
    }
    else
    {
        for (size_t i = 0; i < inventory.size(); ++i)
        {
            cout << i << ": " << inventory[i].name << "+: " << inventory[i].healAmount << endl;
        }
    }
}

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