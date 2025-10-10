#include"Header.h"

void finfichero(int n) {
	fstream f1;
	f1.open("f1.txt", ios::in);
	queue<string> tmp;
	while (!f1.eof()) {
		string x;
		f1 >> x;
		if (tmp.size() == n + 1) {
			tmp.pop();
			tmp.push(x);
		}
		else
			tmp.push(x);
	}
	while (!tmp.empty()) {
		cout << tmp.front() << " ";
		tmp.pop();
	}

	cout << endl;
	f1.close();
}