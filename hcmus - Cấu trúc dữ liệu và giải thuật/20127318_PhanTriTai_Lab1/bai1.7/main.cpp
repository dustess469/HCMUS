#include"Header.h"

int main() {
	fstream f1;
	f1.open("f1.bin", ios::out, ios::binary);

	string name;
	cout << "Full name: ";
	getline(cin, name);

	int age;
	cout << "Age: ";
	cin >> age;

	string address, a;
	cin >> a;
	cout << "Address: ";
	getline(cin, address);

	address += a;

	f1.write((char*)&name, sizeof(name));
	f1.write((char*)&age, sizeof(age));
	f1.write((char*)&address, sizeof(address));

	f1.close();
	return 0;
}