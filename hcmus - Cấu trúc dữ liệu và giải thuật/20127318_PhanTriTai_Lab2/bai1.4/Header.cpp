#include"Header.h"

void quickSort(int a[], int l, int r) {
	if (l <= r) {
		int key = a[(l + r) / 2];
		int i = l;
		int j = r;

		while (i <= j) {
			while (a[i] < key) ++i;
			while (a[j] > key) --j;
			if (i <= j) {
				swap(a[i], a[j]);
				++i;
				--j;
			}
		}
		if (l < j) quickSort(a, l, j);
		if (r > i) quickSort(a, i, r);
	}
}