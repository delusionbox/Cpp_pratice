#include "battleLog.h"
#include <iostream>

void BattleLog::addLog(const string &log)
{
    logs.push_back(log);
}

void BattleLog::printLog() const
{
    cout << "\n====== battle log ======" << endl;
    for (const auto &log : logs)
    {
        cout << log << endl;
    }
}

void BattleLog::clear()
{
    logs.clear();
}