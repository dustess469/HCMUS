#include "Header.h"

int main() {
	int a[1000], c;
	int n = 0, option = 1;
	while (option != 0) {
		cout << "Choose: \n";
		cout << "0 : Break\n";
		cout << "1 : Push\n";
		cout << "2 : Pop\n";
		cout << "3 : Size\n";
		cout << "\nYour option is: ";
		cin >> option;
		if (option == 1) {
			if (n == 1000) {
				cout << "Queue is full\n";
			}
			else {
				cout << "Which number do you want to push: ";
				cin >> c;
				push(a, n, c);
				cout << "Queue now is: ";
				output(a, n);
				cout << endl;
			}
		}
		if (option == 2) {
			if (n == 0) {
				cout << "Queue is empty\n";
			}
			else {
				pop(a, n);
				cout << "Queue now is: ";
				output(a, n);
				cout << endl;
			}
		}

		if (option == 3) {
			cout << "Size: " << n << endl;
			cout << endl;
		}

		if (option == 4) {
			if (n == 0) cout << "Empty\n";
			else
				cout << "Not empty\n";
			cout << endl;
		}

		cout << endl;
		if (option == 0) {
			break;
		}
	}
	return 0;
}