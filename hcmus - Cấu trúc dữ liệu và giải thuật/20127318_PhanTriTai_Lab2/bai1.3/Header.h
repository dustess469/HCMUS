#ifndef bai3
#define bai3

#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <string>


using namespace std;
string year(string a);
string name(string a);

int partition(string a[], int low, int high);
void quickSort(string arr[], int low, int high);
void heap(string a[], int n, int i);
void heapSort(string a[], int n);
void merge(string arr[], int left, int mid, int right);
void mergeSort(string a[], int left, int righ);


#endif 