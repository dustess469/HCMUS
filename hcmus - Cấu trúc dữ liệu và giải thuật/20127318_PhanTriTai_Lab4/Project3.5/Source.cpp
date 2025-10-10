#include"Header.h"

int main() {
	string s;
	cout << "Enter string: ";
	getline(cin, s);
	cout << endl;
	cout << "My answer: " << solution(s) << endl;
	return 0;
}