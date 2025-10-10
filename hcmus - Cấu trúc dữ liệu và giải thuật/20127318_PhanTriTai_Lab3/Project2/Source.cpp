#include <iostream>
#include <fstream>
#include <map>
#include<string>

using namespace std;

int main(int argc, char* argv[]) {
	fstream f1, f2;
	f1.open("input.txt", ios::in);
	f2.open(argv[argc - 1], ios::out);
	int in = 0;
	map<string, string> ans;
	while (!f1.eof()) {
		//fo << in << endl;
		++in;
		string s, tmp1, tmp2;
		int ok = 0;
		getline(f1, s);
		for (int i = 0; i <= (int)s.length() - 1; ++i) {
			if (s[i] == ':') ok = 1;
			if (!ok) tmp1 = tmp1 + s[i];
			if (ok) tmp2 = tmp2 + s[i];
		}
		ans[tmp1] = tmp2;
		/*	fo << tmp1 << " " << tmp2 << endl;
			if (in == 5) break;*/
	}
	//fo << argc << endl;
	for (int i = 1; i < argc - 1; ++i) {
		string tmp = argv[i];
		f2 << tmp << ans[tmp] << endl;
	}
	f1.close();
	return 0;
}