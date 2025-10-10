#include "Header.h"


//cau1A
int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (a[j] > pivot) {
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


//cau1B
void merge(int a[], int left, int mid, int right) {
    int n = mid - left + 1;
    int m = right - mid;
    int* Lt = new int[n];
    int* Rt = new int[m];

    for (int i1 = 0; i1 < n; i1++) {
        Lt[i1] = a[left + i1];
    }
    for (int j1 = 0; j1 < m; j1++) {
        Rt[j1] = a[mid + 1 + j1];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n && j < m) {
        if (Lt[i] >= Rt[j]) {
            a[k] = Lt[i];
            i++;
        }
        else {
            a[k] = Rt[j];
            j++;
        }
        k++;
    }
    while (i < n) {
        a[k] = Lt[i];
        i++;
        k++;
    }
    while (j < m) {
        a[k] = Rt[j];
        j++;
        k++;
    }
    delete[]Lt;
    delete[]Rt;
}

void mergeSort(int a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}


void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i];
    }
}