#include"Header.h"

int main() {
	fstream filein, fileout;
	filein.open("textin3.txt", ios::in);
	fileout.open("textoutt3.txt", ios::out);
	if (!filein) {
		fileout << "Khong co gi trong file\n";
	}
	else {
		int n;
		filein >> n;
		for (int i = 0; i < n; ++i) {
			double tmp, sum = 0.0, min = 100, max = 0;
			for (int j = 1; j <= 24; ++j) {
				filein >> tmp;
				sum += tmp;
				if (tmp < min) {
					min = tmp;
				}
				if (tmp > max) {
					max = tmp;
				}
			}
			fileout << "Day " << i + 1;
			fileout << "\n- average: " << fixed << setprecision(1) << sum / 24.0;
			fileout << "\n- max: " << fixed << setprecision(1) << max;
			fileout << "\n- min: " << fixed << setprecision(1) << min;
			cout << endl;
		}
	}
	filein.close();
	fileout.close();
	return 0;
}