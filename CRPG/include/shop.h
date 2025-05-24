#pragma once
#include <vector>
#include "item.h"
#include "character.h"

class Shop
{
private:
    vector<Item> items;
    vector<int> prices;

public:
    Shop();

    void showItems() const;
    void buyItem(int index, Character &player);
};
