#include "Header.h"

void linearSearch(int a[], int n, int b[], int& index, int num) {
    for (int i = 0; i < n; ++i) {
        if (a[i] == num) {
            b[index] = i;
            ++index;
        }
    }
}

void sentinelSearch(int a[], int n, int num) {
    int last = a[n - 1];

    a[n - 1] = num;
    int i = 0;

    while (a[i] != num)
        i++;

    a[n - 1] = last;

    if ((i < n - 1) || (a[n - 1] == num))
        cout << num << " is present at index " << i;
    else
        cout << "Element Not found";
}


int firstOccurrence(int a[], int n, int num) {
    int beg = 0;
    int end = n - 1;
    while (beg <= end) {
        int mid = beg + (end - beg) / 2;
        if (a[mid] == num) {
            if (mid - 1 >= 0 and a[mid - 1] == num) {
                end = mid - 1;
                continue;
            }
            return mid;
        }
        else if (a[mid] < num)
            beg = mid + 1;
        else
            end = mid - 1;
    }
    return -1;
}


int lastOccurrence(int a[], int n, int num) {
    int beg = 0;
    int end = n - 1;
    while (beg <= end) {
        int mid = beg + (end - beg) / 2;
        if (a[mid] == num) {
            if (mid + 1 < n and a[mid + 1] == num) {
                beg = mid + 1;
                continue;
            }
            return mid;
        }
        else if (a[mid] < num)
            beg = mid + 1;
        else
            end = mid - 1;
    }
    return -1;
}