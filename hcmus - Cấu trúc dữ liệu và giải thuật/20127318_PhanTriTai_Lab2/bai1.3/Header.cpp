#include "Header.h"

string year(string a) {
	a.erase(0, a.length() - 4);
	return a;
}

string name(string a) {
	a.erase(0, 10);
	a.erase(a.length() - 5, a.length() - 1);
	for (int i = 0; i < a.length(); ++i) {
		if (a[i] == ' ') {
			a.erase(i + 1, a.length());
		}
	}
	return  a;
}

int partition(string arr[], int low, int high) {
	string pivot = year(arr[high]);
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++) {
		if (year(arr[j]) < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}


void quickSort(string arr[], int low, int high) {
	if (low < high) {
		int op = partition(arr, low, high);
		quickSort(arr, low, op - 1);
		quickSort(arr, op + 1, high);
	}
}


void heap(string a[], int n, int i) {
	int max = i, l1 = 2 * i + 1, l2 = 2 * i + 2;
	if (l1 < n && year(a[max]) < year(a[l1])) {
		max = l1;
	}
	if (l2 < n && year(a[max]) < year(a[l2])) {
		max = l2;
	}
	if (max != i) {
		string tmp = a[max];
		a[max] = a[i];
		a[i] = tmp;
		heap(a, n, max);
	}
}

void heapSort(string a[], int n) {
	for (int i = (n - 2) / 2; i >= 0; --i)
		heap(a, n, i);
	for (int i = n - 1; i > 0; --i) {
		string temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		heap(a, i, 0);
	}
}

void merge(string arr[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	string* L1 = new string[n1];
	string* R1 = new string[n2];

	for (int i1 = 0; i1 < n1; i1++) {
		L1[i1] = arr[left + i1];
	}
	for (int j1 = 0; j1 < n2; j1++) {
		R1[j1] = arr[mid + 1 + j1];
	}

	int i = 0;
	int j = 0;
	int k = left;
	while (i < n1 && j < n2) {
		if (year(L1[i]) <= year(R1[j])) {
			arr[k] = L1[i];
			i++;
		}
		else {
			arr[k] = R1[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L1[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R1[j];
		j++;
		k++;
	}
}

void mergeSort(string a[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(a, left, mid);
		mergeSort(a, mid + 1, right);
		merge(a, left, mid, right);
	}
}
