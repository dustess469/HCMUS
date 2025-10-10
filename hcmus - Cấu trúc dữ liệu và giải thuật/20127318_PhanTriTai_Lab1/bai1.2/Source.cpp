#include"Header.h"

int main() {
	fstream file2;
	file2.open("input.txt", ios::in);
	string s;
	getline(file2, s);
	map<string, int> m;
	string tmp;
	for (int i = 0; i <= s.length() - 1; ++i) {
		if (s[i] == ' ') {
			++m[tmp];
			tmp = "";
		}
		else {
			tmp = tmp + s[i];
		}
	}
	int count = 0;
	for (auto i : m) {
		++count;
	}
	cout << "So chuoi khong trung nhau: " << count << endl;
	file2.close();
	return 0;
}