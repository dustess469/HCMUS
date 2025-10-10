#include"Header.h"

int main() {
	fstream file1, file2;
	file1.open("f1.txt", ios::in);
	file2.open("f2.txt", ios::in);

	string t1, t2;
	while (!file1.eof()) {
		while (!file2.eof()) {
			getline(file1, t1);
			getline(file2, t2);
			if (t1 != t2) {
				cout << "< " << t1 << endl;
				cout << "> " << t2 << endl;
			}
		}
	}

	file1.close();
	file2.close();

	return 0;
}