#pragma once
#include <string>

using namespace std;

class Item
{
public:
    string name;
    int healAmount;

    Item(string name, int healAmount);

    void use();
};