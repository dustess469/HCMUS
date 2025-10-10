#include"Header.h"

int main() {
	push(90);
	push(78);
	push(56);
	push(34);
	push(12);
	
	cout << "Before pop:\n";
	display();
	cout << "Top element is: " << fristElement() << endl;

	pop();

	cout << "\nAfter pop:\n";
	display();
	cout << "Top element is: " << fristElement() << endl;

	cout << "\nMemory status: " << displayBit() << endl;
	return 0;
}

