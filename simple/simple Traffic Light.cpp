#include <iostream>
#include <unistd.h>

using namespace std;

int main ()
{
  cout << "press enter";
  cin.ignore ();

  int i=1;
  int j=0;

  while(true){
  for (i = 1; i <= 4; i++)
    {
        cout << "Line" << i << "\n";
        
        for(j= 0; j<= 10; j++){
            
            sleep(1);
            cout << j <<"\n";
            
        }
    }
  }


  return 0;
}
