#include <iostream>
#include <string>
using namespace std;

int main()
{
	string first;
	string next;
	
	cout << "who first?" << '\n';
	
	cout << "input: ";
	getline(cin, first, '\n');

	cout << "input: ";
	getline(cin, next, '\n');

	int result = first.compare(next);

	if (result == 0) {
		cout << "equal";
	}
	else if (result < 0) {
		cout << first;
	}
	else {
		cout << next;
	}

	return 0;
}
