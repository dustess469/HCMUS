#include"Header.h"

int main() {
	int n;
	int a[105];
	cout << "Input n: ";
	cin >> n;

	int tmp = 1, row = n, column = n;
	int x = 0;
	int ans[105][105];
	while (tmp <= n / 2) {
		for (int i = tmp; i <= column; ++i) {
			ans[tmp][i] = ++x;
		}
		for (int i = tmp + 1; i <= row; ++i) {
			ans[i][column] = ++x;
		}
		for (int i = column - 1; i >= tmp; --i) {
			ans[row][i] = ++x;
		}
		for (int i = row - 1; i > tmp; --i) {
			ans[i][tmp] = ++x;
		}
		++tmp;
		--row;
		--column;
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
