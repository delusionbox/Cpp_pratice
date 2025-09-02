#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> //clear function
#include <limits>  //numeric_limits
#include <conio.h> //_getch
#include <map>

std::string getHiddenInput(const std::string &prompt) // hiding input text
{
    std::string input;
    char ch;
    std::cout << prompt;
#ifdef _WIN32                       // if window
    while ((ch = _getch()) != '\r') // repeat '\r'(enter)
    {
        if (ch == '\b' && !input.empty()) //'\b'
        {
            input.pop_back();     // last char delete
            std::cout << "\b \b"; // backspace? char erase..
        }
        else if (isdigit(ch) && input.size() < 4) // isdigit=>only number, limit 4
        {
            input.push_back(ch);
            std::cout << "*";
        }
    }
#else
    system("stty -echo");
    getline(cin, input);
    system("stty echo");
    std::cout << std::string(input.size(), '*') << std::endl;
#endif
    return input;
};

void clearScreen() // clear console
{
#ifdef _WIN32
    system("cls"); // window
#else
    system("clear"); // linux and mac
#endif
};

void pause() // show message and empty input buffer and waiting enter => press enter function end
{
    std::cout << "\nPlease enter to continue..";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // input buffer empty
    std::cin.get();
}

void printHeader(const std::string &title) // print header
{
    std::cout << "====" << title << "====" << std::endl;
};

void printFooter() // print footer
{
    std::cout << "==== Thank you ====" << std::endl;
};

struct Transaction
{
    std::string type;
    double amount{};
    time_t timestamp{};
};

struct Account
{
    std::string username;
    double balance = 0.0;
    std::string pin;
    std::vector<Transaction> history;
};

class ATM
{
    std::map<std::string, Account> accounts;
    Account *currentUser = nullptr;

public:
    //  createAccount
    void createAccount();
    // login
    void login();
    // logout
    void logout()
    {
        currentUser = nullptr;
    };
    // check balance
    void checkBalance()
    {
        printHeader("check Balance");
        std::cout << "Balance: $" << currentUser->balance << std::endl;
        pause();
    };
    // deposit
    void deposit()
    {
        printHeader("deposit");
        double amount;
        std::cin >> amount;
        std::cin.ignore();
        if (amount > 0)
        {
            currentUser->balance += amount;
            currentUser->history.push_back({"Deposit", amount});
            std::cout << "success deposit" << std::endl;
        }
        else
        {
            std::cout << "Error" << std::endl;
        }
        pause();
    };
    // withdraw
    void withdraw()
    {
        printHeader("withdraw");
        double amount;
        std::cout << "Withdraw money: $";
        std::cin >> amount;
        std::cin.ignore();
        if (amount > 0 && amount <= currentUser->balance)
        {
            currentUser->balance -= amount;
            currentUser->history.push_back({"Withdraw", amount});
            std::cout << "withdraw success" << std::endl;
        }
        else
        {
            std::cout << "No money";
        }
        pause();
    };
    // History
    void showHistory()
    {
        printHeader("Transaction History");
        if (currentUser->history.empty())
        {
            std::cout << "No history.\n";
        }
        else
        {
            for (const auto &text : currentUser->history)
            {
                std::cout << text.type << "$" << text.amount;
            }
        }
        pause();
    };
    // Menu
    void userMenu()
    {
        int select = 0;
        while (true)
        {
            clearScreen();
            printHeader("ATM");
            std::cout << "";
            std::cin >> select;
            std::cin.ignore();
            switch (select)
            {
            case 1:
                checkBalance();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                showHistory();
                break;
            case 5:
                logout();
                break;
            default:
                std::cout << "choice";
                pause();
                break;
            };
        }
    };
};

int main()
{
    /*
    Account a = {"john doe", 1.2, "asdf"};
    printHeader("hello");
    std::cout << a.username << a.balance << a.pin << std::endl;
    printFooter();
    pause();
    std::string pin = getHiddenInput("Enter 4-pin: ");
    std::cout << "\nEntered: " << pin << std::endl;
    */
    ATM atm;
    atm.userMenu();
    return 0;
}