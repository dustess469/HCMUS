#include "Header.h"

int main() {
	string str1[100], str2[100], str3[100], tmp[100];
	fstream f1, f2;
	string temp;

	f1.open("employee.txt");
	f2.open("sortedemponage.txt");
	getline(f1, temp);
	int i = 0;
	while (!f1.eof()) {
		getline(f1, temp);
		str1[i] = temp;
		i++;
	}

	mergeSort(str1, 0, i - 1);
	for (int j = 0; j < i; j++) {
		int id = 0;
		for (int k = j + 1; year(str1[k]) == year(str1[j]); k++) {
			id++;
		}
		for (int k = j; k < j + id + 1; k++) {
			for (int p = k + 1; p < j + id + 1; p++) {
				if (name(str1[k]) > name(str1[p])) {
					swap(str1[k], str1[p]);
				}
			}
		}
		j += id;
	}
	for (int j = 0; j < i; ++j)
		f2 << str1[j] << endl;

	f1.close();
	f2.close();
	return 0;
}