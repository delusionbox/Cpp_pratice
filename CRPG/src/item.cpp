#include "item.h"
#include <iostream>

Item::Item(string name, int healAmount)
    : name(name), healAmount(healAmount) {

      };

void Item::use()
{
    cout << name << "is used. health +" << healAmount << endl;
}
