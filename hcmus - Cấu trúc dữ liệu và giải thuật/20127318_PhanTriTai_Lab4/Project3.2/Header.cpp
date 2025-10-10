#include"Header.h"

void push(int a[], int& n, int x) {
	++n;
	a[n - 1] = x;
}

void pop(int a[], int& n) {
	for (int i = 0; i < n; ++i) {
		a[i] = a[i + 1];
	}
	--n;
}

void output(int a[], int n) {
	for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}
}