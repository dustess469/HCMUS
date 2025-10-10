#include"Header.h"

int main() {
	int a[] = { 0,1,3,5,6,7,88,-65,77,8,91,101 };
	int x;
	int n = 12;



	quickSort(a, 0, n - 1);

	for (size_t i = 0; i < n; i++)
		cout << a[i] << " ";

	cout << endl;

	cout << "Enter element: ";
	cin >> x;
	cout << "\n===================================================\n";

	cout << "Linear search: " << endl;
	cout << "Index of element: "; linear_search(a, n, x);

	cout << "\n===================================================\n";

	cout << "Sentinel search: " << endl;
	cout << "Index of element: "; sentinel_search(a, n, x);

	cout << "\n===================================================\n";

	cout << "Binary search: " << endl;
	cout << "Index of element: " << binary_search(a, 0, n - 1, x);



	return 0;
}