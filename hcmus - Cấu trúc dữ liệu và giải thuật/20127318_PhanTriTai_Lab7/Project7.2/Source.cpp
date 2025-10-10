#include"Header.h"

int main()
{
	ifstream fileinput;
	ofstream fileoutput;
	fileinput.open("input.txt");
	fileoutput.open("output.txt");

	int n;
	fileinput >> n;
	fileinput.ignore();

	while (!fileinput.eof())
	{
		Node* root;
		root = nullptr;
		string s1, s2;
		getline(fileinput, s1);

		stringstream s;
		s << s1;

		int x;
		while (s >> s2)
		{
			x = stoi(s2);
			insert(root, x);
		}

		cout << check_AVL(root) << "\n";
		fileoutput << check_AVL(root) << "\n";
	}
	fileinput.close();
	fileoutput.close();
	return 0;
}