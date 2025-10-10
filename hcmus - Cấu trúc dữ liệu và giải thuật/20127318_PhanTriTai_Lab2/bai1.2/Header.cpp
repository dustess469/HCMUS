#include"Header.h"

void input(int n, int a[]) {
	for (int i = 0; i < n; i++){
		cout << "a[" << i << "] = ";
		cin >> a[i];
	}
}

void output(int n, int a[]) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}

int mySort(int n, int a[100],int chan[100],int le[100],int x[100],int y[100]) {
	int i1 = 0, i2 = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] % 2 == 0) {
			chan[i1] = a[i];
			x[i1] = i;
			++i1;
		}
		else {
			le[i2] = a[i];
			y[i2] = i;
			++i2;
		}
	}
	for (int i = 0; i < i1; ++i) {
		for (int j = i + 1; j < i1; ++j) {
			if (chan[i] > le[j]) {
				int tmp = chan[i];
				chan[i] = chan[j];
				chan[j] = tmp;
			}
		}
	}
	for (int i = 0; i < i2; ++i) {
		for (int j = i + 1; j < i2; ++j) {
			if (le[i] < le[j]) {
				int tmp = le[i];
				le[i] = le[j];
				le[j] = tmp;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		int tmp = 0;
		for (int j = 0; j < i1; ++j) {
			if (x[j] == i) {
				tmp = chan[j];
				break;
			}
		}
		for (int j = 0; j < i2; ++j) {
			if (y[j] == i) {
				tmp = le[j];
				break;
			}
		}
		a[i] = tmp;
	}
}