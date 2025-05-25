#pragma once
#include <vector>
#include <string>

using namespace std;

class BattleLog
{
private:
    vector<string> logs;

public:
    void addLog(const string &log);
    void printLog() const;
    void clear();
};