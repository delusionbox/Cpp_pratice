#include <iostream>
using namespace std;

int sum(int a, int b){
    int r = a + b;
    return r;
}

int sum(int a){
    int r = a;
    return r;
}

float sum(float a, float b, float c){
    float r = a + b + c;
    return r;
}

int main()
{
    cout << sum(10, 30) << endl;
    cout << sum(10) << endl;
    cout << sum(3.1f, 4.2f, 2.6f) << endl;
}
