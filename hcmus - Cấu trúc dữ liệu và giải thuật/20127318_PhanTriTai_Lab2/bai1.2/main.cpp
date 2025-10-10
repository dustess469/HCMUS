#include"Header.h"

int main() {
	int n, a[100], chan[100], le[100], x[100], y[100], i1 = 0, i2 = 0;
	cout << "Nhap so luong phan tu: ";
	cin >> n;
	cout << "Nhap phan tu:\n";
	input(n, a);
	mySort(n, a, chan, le, x, y);
	output(n, a);
	return 0;
}