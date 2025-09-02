#include <iostream>

void L_and(int a, int b)
{
    std::cout << "input number. 1(True) 0(False)\n";
    std::cin >> a >> b;
    if (a == 1 && b == 0)
    {
        std::cout << 0;
    }
    else if (a == 0 && b == 1)
    {
        std::cout << 0;
    }
    else if (a == 1 && b == 1)
    {
        std::cout << 1;
    }
    else if (a == 0 && b == 0)
    {
        std::cout << 0;
    }
    else
    {
        std::cout << "please input 1 or 0";
    }
};

int main()
{
    int a;
    int b;
    L_and(a, b);
    return 0;
};