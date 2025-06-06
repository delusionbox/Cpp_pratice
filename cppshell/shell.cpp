#include "Shell.h"
#include <ctime>
#include <filesystem>
#include <direct.h>
#include <io.h>
#include <cerrno>
#include <cstring>
#include <fstream> // ofstream, ifstream

using namespace std;

void Shell::run()
{
    string input;

    while (true)
    {
        cout << ">> ";
        if (!getline(cin, input))
            break;
        if (input.empty())
            continue;

        history.push_back(input);
        handleInput(input);
    }
};

void Shell::handleInput(const string &line)
{
    if (line.substr(0, 4) == "echo")
    {
        cmdEcho(line);
        return;
    }
    stringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd == "exit")
    {
        exit(0);
    }
    exeBuiltIn(cmd, ss);
};

void Shell::exeBuiltIn(const string &cmd, istream &args)
{
    if (cmd == "help")
        cmdHelp();
    else if (cmd == "time")
        cmdTime();
    else if (cmd == "clear")
        cmdClear();
    else if (cmd == "pwd")
        cmdPwd();
    else if (cmd == "ls")
        cmdLs();
    else if (cmd == "cd")
    {
        string path;
        args >> path;
        cmdCd(path);
    }
    else if (cmd == "mkdir")
    {
        string dir;
        args >> dir;
        cmdMkdir(dir);
    }
    else if (cmd == "touch")
    {
        string file;
        args >> file;
        cmdTouch(file);
    }
    else if (cmd == "rm")
    {
        string file;
        args >> file;
        cmdRm(file);
    }
    else if (cmd == "cat")
    {
        string file;
        args >> file;
        cmdCat(file);
    }
    else if (cmd == "history")
    {
        cmdHistory();
    }
    else
    {
        cout << "Wrong Command: help " << cmd << endl;
    }
}

void Shell::cmdHelp()
{
    cout << "Available Commands: echo, help, time, exit, clear, pwd, ls, cd, mkdir, touch, rm, cat, history" << endl;
};

void Shell::cmdTime()
{
    time_t now = time(0);
    tm *localTime = localtime(&now);
    cout << "Current Time: "
         << 1900 + localTime->tm_year << "-"
         << 1 + localTime->tm_mon << "-"
         << localTime->tm_mday << " "
         << localTime->tm_hour << ":"
         << localTime->tm_min << ":"
         << localTime->tm_sec << endl;
};

void Shell::cmdClear()
{
#ifdef _WIN32
    system("cls"); // window
#else
    system("clear"); // Mac or Linux
#endif
};

void Shell::cmdPwd()
{
    // cout << filesystem::current_path() << endl;
    char buffer[FILENAME_MAX];
    if (_getcwd(buffer, FILENAME_MAX))
    {
        cout << buffer << endl;
    }
    else
    {
        cerr << "ERROR\n"
             << endl;
    }
};

void Shell::cmdLs()
{
    /*
    for (const auto &entry : filesystem::directory_iterator(filesystem::current_path()))
    {
        cout << entry.path().filename().string() << endl;
    };
    */

    char buffer[FILENAME_MAX];
    if (!_getcwd(buffer, FILENAME_MAX))
    {
        cerr << "ERROR\n"
             << endl;
        return;
    }

    string path = string(buffer) + "\\*";
    struct _finddata_t fileinfo;
    intptr_t handle = _findfirst(path.c_str(), &fileinfo);

    if (handle == -1)
    {
        cerr << "ERROR\n"
             << endl;
    }

    do
    {
        cout << fileinfo.name;
        if (fileinfo.attrib & _A_SUBDIR)
        {
            cout << " [DIR]";
        }
        cout << endl;
    } while (_findnext(handle, &fileinfo) == 0);
    _findclose(handle);
};

void Shell::cmdCd(const string &path)
{
    if (_chdir(path.c_str()) != 0)
    {
        cerr << "Directory change failed: '" << path << "'\n";
    }
    else
    {
        char buffer[FILENAME_MAX];
        _getcwd(buffer, FILENAME_MAX);
        cout << "Directory change: " << buffer << endl;
    };
};

void Shell::cmdMkdir(const string &dir)
{
    if (_mkdir(dir.c_str()) != 0)
    {
        cerr << "mkdir failed: " << dir << "'\n";
        cerr << "Reason: " << strerror(errno) << "\n";
    }
    else
    {
        cout << "mkdir success: " << dir << endl;
    }
};

void Shell::cmdTouch(const string &file)
{
    ofstream f(file);
    if (!f)
    {
        cerr << "create file failed: " << file << endl;
        return;
    }

    cout << "file is created" << file << endl;
    f.close();
};

void Shell::cmdRm(const string &file)
{
    if (remove(file.c_str()) != 0)
    {
        cerr << "File Remove Fail: " << file << endl;
    }
    else
    {
        cout << "File Removed: " << file << endl;
    }
};

void Shell::cmdCat(const string &file)
{
    ifstream f(file);
    if (!f.is_open())
    {
        cerr << "Open File failed" << file << endl;
        return;
    }
    string line;
    while (getline(f, line))
    {
        cout << line << endl;
    }

    f.close();
};

void Shell::cmdEcho(const string &line)
{
    size_t redirectPos = line.find('>');

    if (redirectPos == string::npos)
    {
        cerr << "echo: echo [content] > [file]" << endl;
        return;
    }

    string content = line.substr(5, redirectPos - 5);
    string filename = line.substr(redirectPos + 1);

    content.erase(0, content.find_first_not_of(" \t"));
    content.erase(content.find_last_not_of(" \t") + 1);
    filename.erase(0, filename.find_first_not_of(" \t"));
    filename.erase(filename.find_last_not_of(" \t") + 1);

    ofstream file(filename);
    if (!file)
    {
        cerr << "Failed: " << filename << endl;
        return;
    }

    file << content;
    file.close();
    cout << "Complete: " << filename << endl;
};

void Shell::cmdHistory()
{
    for (size_t i = 0; i < history.size(); ++i)
    {
        std::cout << i + 1 << "  " << history[i] << std::endl;
    }
}
string Shell::trim(const string &s)
{
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}