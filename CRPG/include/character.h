#pragma once
#include <string>
#include <vector>
#include "item.h"

using namespace std;

class Character
{
public:
    string name;
    int hp;
    int maxHp;
    int atk;
    vector<Item> inventory;

    Character(string name, int hp, int atk);

    void addItem(const Item &item);
    void useItem(int index);
    void printInventory() const;

    void takeDamage(int dmg);
    bool isAlive() const;
    int attack() const;
    void showStatus() const;
};