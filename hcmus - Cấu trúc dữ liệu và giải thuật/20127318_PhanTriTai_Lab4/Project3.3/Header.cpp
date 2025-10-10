#include"Header.h"

bool isPalin(string s) {
	stack<char> a;
	queue<char> b;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == ' ') {
			s.erase(i, 1);
		}
	}
	for (int i = 0; i < s.length(); ++i) {
		a.push(s[i]);
		b.push(s[i]);
	}
	while (!a.empty()) {
		while (a.top() < 48 || (a.top() > 57 && a.top() < 65) || (a.top() > 90 && a.top() < 97) || a.top() > 122) {
			a.pop();
		}
		while (b.front() < 48 || (b.front() < 65 && b.front() > 57) || (b.front() > 90 && b.front() < 97) || b.front() > 122) {
			b.pop();
		}
		if (a.top() >= 65 && a.top() <= 90) {
			a.top() += 32;
		}
		if (b.front() >= 65 && b.front() <= 90) {
			b.front() += 32;
		}
		if (a.top() != b.front()) {
			return 0;
		}
		a.pop();
		b.pop();
	}
	return 1;
}