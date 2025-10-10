#include "Header.h"

int main() {
	int n, x;
	cout << "Nhap n: ";
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; ++i) {
		cout << "a[" << i << "] = ";
		cin >> a[i];
	}


	quickSort(a, 0, n - 1);
	cout << "Nhap gia tri x: ";
	cin >> x;
	cout << "Vi tri x: " << binarySearch(a, 0, n - 1, x);
	delete[]a;
	return 0;
}