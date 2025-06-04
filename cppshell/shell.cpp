#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <filesystem>
#include <direct.h>
#include <io.h>
#include <cerrno>
#include <cstring>
#include <fstream> // ofstream, ifstream

using namespace std;

void showHelp()
{
    cout << "Available Commands: echo, help, time, exit, clear, pwd, ls, cd, mkdir, touch " << endl;
};

void showTime()
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

void clearScreen()
{
#ifdef _WIN32
    system("cls"); // window
#else
    system("clear"); // Mac or Linux
#endif
};

void printWorkDirectory()
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

void listDirectory()
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

void changeDirectory(const string &path)
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

void makeDirectory(const string &DName)
{
    if (_mkdir(DName.c_str()) != 0)
    {
        cerr << "mkdir failed: " << DName << "'\n";
        cerr << "Reason: " << strerror(errno) << "\n";
    }
    else
    {
        cout << "mkdir success: " << DName << endl;
    }
};

void createFile(const string &filename)
{
    ofstream file(filename);
    if (!file)
    {
        cerr << "create file failed: " << filename << endl;
        return;
    }

    cout << "file is created" << filename << endl;
    file.close();
};

void removeFile(const string &filename)
{
    if (remove(filename.c_str()) != 0)
    {
        cerr << "File Remove Fail: " << filename << endl;
    }
    else
    {
        cout << "File Removed: " << filename << endl;
    }
};

void printFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Open File failed" << filename << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
};

void echoFile(const string &inputLine)
{
    size_t redirectPos = inputLine.find('>');

    if (redirectPos == string::npos)
    {
        cerr << "echo: echo [content] > [file]" << endl;
        return;
    }

    string content = inputLine.substr(5, redirectPos - 5);
    string filename = inputLine.substr(redirectPos + 1);

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

int main()
{
    string input;

    while (true)
    {
        cout << ">>";
        getline(cin, input);

        if (input.empty())
            continue;

        if (input.substr(0, 4) == "echo")
        {
            echoFile(input);
        }
        else
        {

            stringstream ss(input);
            string command;
            ss >> command;

            if (command == "exit")
            {
                break;
            }
            else if (command == "help")
            {
                showHelp();
            }
            else if (command == "time")
            {
                showTime();
            }
            else if (command == "echo")
            {
                string text;
                getline(ss, text);
                cout << text << endl;
            }
            else if (command == "clear")
            {
                clearScreen();
            }
            else if (command == "pwd")
            {
                printWorkDirectory();
            }
            else if (command == "ls")
            {
                listDirectory();
            }
            else if (command == "cd")
            {
                string target;
                ss >> target;
                if (target.empty())
                {
                    cerr << "cd: Input Path.\n";
                }
                else
                {
                    changeDirectory(target);
                }
            }
            else if (command == "mkdir")
            {
                string folder;
                ss >> folder;
                if (folder.empty())
                {
                    cerr << "mkdir: Input Directory Name.\n";
                }
                else
                {
                    makeDirectory(folder);
                }
            }
            else if (command == "touch")
            {
                string filename;
                ss >> filename;
                if (filename.empty())
                {
                    cerr << "touch: Input filename.\n";
                }
                else
                {
                    createFile(filename);
                };
            }
            else if (command == "rm")
            {
                string filename;
                ss >> filename;
                if (filename.empty())
                {
                    cerr << "rm: Input filename.\n";
                }
                else
                {
                    removeFile(filename);
                };
            }
            else if (command == "cat")
            {
                string filename;
                ss >> filename;
                if (filename.empty())
                {
                    cerr << "Input filename.\n";
                }
                else
                {
                    printFile(filename);
                }
            }
            else
            {
                cout << "Wrong Command. Input help" << endl;
            }
        }
    }
    cout << "Shell exit" << endl;
    return 0;
}