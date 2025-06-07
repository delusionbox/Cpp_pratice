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
    void executePipe(const string &cmd1, const string &cmd2);

    void exeBuiltIn(const string &cmd, istream &args);
    void executeBuiltIn(const string &cmd, istream &args, ostream &out);

    // BuiltIn
    void cmdPwd(ostream &out);
    void cmdLs(ostream &out);
    void cmdCd(const string &path);
    void cmdMkdir(const string &dir);
    void cmdTouch(const string &file);
    void cmdRm(const string &file);
    void cmdCat(const string &file);
    void cmdEcho(const string &line);
    void cmdHistory(ostream &out);
    void cmdHelp(ostream &out);
    void cmdTime(ostream &out);
    void cmdClear();

    // util
    static string trim(const string &s);
};