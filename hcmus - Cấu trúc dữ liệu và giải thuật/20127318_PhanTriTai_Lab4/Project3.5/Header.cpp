#include "Header.h"

bool calculator(char x) {
	if (x == '+' || x == '-' || x == '*' || x == '/')
		return 1;
	return 0;
}

int solution(string s) {
	stack <int> sk;
	for (int i = 0; i < s.length(); ++i) {
		if (calculator(s[i]) != 1 && s[i] != ' ') {
			int pos = 0;
			for (int j = i; s[j] != ' ' && j < s.length(); ++j) {
				pos = j;
			}
			pos += 1;
			char* temp = new char[pos - i + 1];
			int index = 0;
			for (int j = i; j < pos; ++j) {
				temp[index] = s[j];
				++index;
			}
			sk.push(atoi(temp));
			i += index - 1;
			delete temp;
		}
		if (calculator(s[i]) == 1) {
			int temp = sk.top();
			sk.pop();
			if (s[i] == '+') {
				temp = sk.top() + temp;
			}
			if (s[i] == '-') {
				temp = sk.top() - temp;
			}
			if (s[i] == '*') {
				temp = sk.top() * temp;
			}
			if (s[i] == '/') {
				temp = sk.top() / temp;
			}
			sk.pop();
			sk.push(temp);
		}
	}
	return sk.top();
}