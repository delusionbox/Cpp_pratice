#pragma once
#include <string>

using namespace std;

class Monster
{
public:
    Monster(string name, int hp, int atk);

    void takeDamage(int dmg);
    bool isAlive() const;
    int attack() const;
    void showStatus() const;

private:
    string name;
    int hp;
    int atk;
};