#include"Header.h"

int main() {
	ofstream file1;
	file1.open("text1.txt");
	file1 << "Hello World\n";
	file1.close();
	return 0;
}