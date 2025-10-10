#include"Header.h"

int main() {
	int a[10000];

	srand((int)time(0));
	int n = 10000;
	for (int i = 0; i < n; i++) {
		a[i] = rand();
	}

	int count1 = 0, count2 = 0;	
	
	insertionSort(a, n, count1);
	mergeSort(a, 0, n - 1, count2);
	return 0;
}