#include"Header.h"

int main() {
	string s;
	cout << "Enter string: ";
	getline(cin, s);
	if (isPalin(s) == 1) {
		cout << "True\n";
	}
	else {
		cout << "False\n";
	}
	return 0;
}