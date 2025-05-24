#include "shop.h"
#include <iostream>

Shop::Shop()
{
    // shop initialize
    items.emplace_back("small potion", 20);
    prices.push_back(30);

    items.emplace_back("middle potion", 50);
    prices.push_back(60);
}

void Shop::showItems() const
{
    cout << "====== shop list ======" << endl;
    for (size_t i = 0; i < items.size(); ++i)
    {
        cout << i << ": " << items[i].name << " +: " << items[i].healAmount << " - " << prices[i] << "Gold" << endl;
    }
}

void Shop::buyItem(int index, Character &player)
{
    if (index < 0 || index >= items.size())
    {
        cout << "wrong select" << endl;
        return;
    }

    int price = prices[index];
    if (player.gold < price)
    {
        cout << "not enough gold" << endl;
        return;
    }

    player.gold -= price;
    player.addItem(items[index]);
    cout << "Success! gold: " << player.gold << endl;
}