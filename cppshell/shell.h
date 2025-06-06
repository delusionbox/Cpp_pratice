#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Shell
{
public:
    void run();

private:
    vector<string> history; // history

    void handleInput(const string &line);
    void exeBuiltIn(const string &cmd, istream &args);

    // BuiltIn
    void cmdPwd();
    void cmdLs();
    void cmdCd(const string &path);
    void cmdMkdir(const string &dir);
    void cmdTouch(const string &file);
    void cmdRm(const string &file);
    void cmdCat(const string &file);
    void cmdEcho(const string &line);
    void cmdHistory();
    void cmdHelp();
    void cmdTime();
    void cmdClear();

    // util
    static string trim(const string &s);
};