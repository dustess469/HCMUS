#include"Header.h"


int main()
{
	int n = 0;
	string name[1000], numberP[1000], hash[100][2];
	string a, b, c;

	readFile("Phonebook.txt", name, numberP, n);

	//adds a monster m with phone number p to the phone book
	add(hash, name, numberP, n);

	printHash(hash, n);

	//returns the phone number of monster m
	cout << "\nEnter name to find: ";
	getline(cin, a);
	find(hash, a, n);
	return 0;
}