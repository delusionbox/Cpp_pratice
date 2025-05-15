#include <iostream>

using namespace std;

int main ()
{
  int a;
  int b;
  int c;

  cout << "This is to return the larger number when you enter two numbers." << endl;
  cout << "When you want to start, please enter the <1>" << endl;
  cout << "When you want to quit, please enter the <0>" << endl;


  cin >> c;

  while (c == 1)
    {
      cout << "input the number 1>>";
      cin >> a;
      cout << "input the number 2>>";
      cin >> b;


  if (a == b)
	{
	  cout << "same size" << endl;
	}
  else if (a > b)
	{
	  cout << "large number is = " << a << endl;
	}
  else if (a < b)
	{
	  cout << "large number is = " << b << endl;
	}
    }

  if (c == 0)
    {
      cout << "app is quit please restart" << endl;
    }
  else if (c <= -1 || c >= 2)
    {
      cout << "error please restart" << endl;
    }
}
