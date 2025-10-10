#include"Header.h"

void push(char a[], int& n, char x) {
	++n;
	a[n] = x;
}

void pop(char a[], int& n) {
	--n;
}

void output(char a[], int n) {
	for (int i = n; i != 0; --i) {
		cout << a[i] << " ";
	}
}