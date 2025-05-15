#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int main()
{
    srand(time(0));
    
    string itemcode[5] = {"money", "box", "water", "file", " "};
    
    int result = (rand() % 5 );
    
    cout<<"press enter"<< endl;
    
    cin.ignore();
    
    cout<< itemcode[result];
    
    return 0;
}
