#include "Header.h"


int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return (i + 1);
}


void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

int binarySearch(int a[], int l, int r, int x) {
    if (r >= l) {
        int m = l + (r - l) / 2;
        if (a[m] == x) {
            return m;
        }
        if (a[m] > x) {
            return binarySearch(a, l, m - 1, x);
        }
        return binarySearch(a, m + 1, r, x);
    }
    return -1;
}