#include"Header.h"

//insertionsort
void insertionSort(int a[], int n, int count1) {
	int i, tmp, j;

	for (i = 1; i < n; i++) {
		tmp = a[i];
		j = i - 1;

		while (j >= 0 && a[j] > tmp) {
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = tmp;
		count1++;
	}
	cout << "A Count = " << count1 << endl;
}


//mergesort
void merge(int a[], int left, int mid, int right) {
	int* tmp;
	int i = left;
	int j = mid + 1;

	tmp = new int[right - left + 1];

	for (int k = 0; k <= right - left; k++) {
		if (a[i] < a[j]) {

			tmp[k] = a[i];
			i++;
		}
		else {
			tmp[k] = a[j];
			j++;
		}

		if (i == mid + 1) {

			while (j <= right) {
				k++;
				tmp[k] = a[j];
				j++;
			}
			break;
		}

		if (j == right + 1) {
			while (i <= mid) {
				k++;
				tmp[k] = a[i];
				i++;
			}
			break;
		}
	}
	for (int k = 0; k <= right - left; k++)
		a[left + k] = tmp[k];
}

void mergeSort(int a[], int left, int right, int& count2) {
	if (right > left) {
		int mid;

		mid = (left + right) / 2;

		mergeSort(a, left, mid, count2);
		mergeSort(a, mid + 1, right, count2);
		merge(a, left, mid, right);
		count2++;
	}
	cout << "B Count = " << count2 << endl;
}