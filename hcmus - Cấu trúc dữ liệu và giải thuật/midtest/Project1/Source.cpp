#include "Header.h"

int main() {
	int n = 200, a[205], temp[205];
	for (int i = 0; i < n; ++i) {
		a[i] = rand() % 10;
		temp[i] = a[i];
	}
	
	//cau1A
	cout << "Quick sort: \n";
	quickSort(temp, 0, n - 1);
	for (int i = 0; i < n; ++i)
		cout << temp[i] << " ";
	cout << endl;

	//cau1B
	mergeSort(a, 0, n - 1);
	cout << "\nMegre sort: \n";
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}