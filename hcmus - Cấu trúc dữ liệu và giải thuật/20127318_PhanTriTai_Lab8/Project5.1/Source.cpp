#include"Header.h"

int main() {
	int n, x;
	cout << "Number of array: ";
	cin >> n;

	vector<int>hash[1000];
	hash[1000] = { 0 };
	int a[1000];
	cout << "Elements: \n";
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}


	return 0;
}