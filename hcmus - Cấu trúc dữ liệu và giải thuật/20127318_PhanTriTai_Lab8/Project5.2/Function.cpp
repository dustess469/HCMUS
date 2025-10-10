#include"Header.h"

void readFile(const char* filename, string name[], string num[], int& n)
{
	ifstream filein;
	filein.open(filename);

	string s[1000];
	while (!filein.eof())
	{
		getline(filein, s[n]);
		n++;
	}
	for (int i = 0; i < n; i++)
	{
		int j = 0;

		while (s[i][j + 1] < '0' || s[i][j + 1]>'9')
		{
			name[i] += s[i][j];
			j++;
		}
		j++;

		while (j < s[i].size())
		{
			num[i] += s[i][j];
			j++;
		}
	}
}



int changeStr(string s)
{
	int ans = 0;
	for (int i = 0; i < s.size(); i++)
	{
		ans += (int)s[i];
	}
	return ans;
}


int hashFunc(string s, int size, int i)
{
	int tmp = changeStr(s);
	return (tmp + i) % size;
}


void add(string hash[][2], string name[], string num[], int& size)
{
	for (int i = 0; i < size; i++)
	{
		int id = hashFunc(name[i], size, 0);
		int j = 1;
		while (hash[id][0].size() > 0)
		{
			id = hashFunc(name[i], size, j);
			j++;
		}

		hash[id][0] = name[i];
		hash[id][1] = num[i];
	}
}

void find(string hash[][2], string name, int size)
{
	int j = 0;
	int c = 0;

	while (j < size)
	{
		int id = hashFunc(name, size, j);

		if (name == hash[id][0])
		{
			cout << "Numberphone: " << hash[id][1] << endl;
			c = 1;
			break;
		}

		j++;
	}

	if (c == 0)
	{
		cout << "Don't have in Phonebook.txt\n";
	}
}

void printHash(string hash[][2], int n)
{
	cout << "THE MONSTER FAMILY\n";
	cout << "NAME AND PHONE:\n";

	for (int i = 0; i < n; i++)
	{
		cout << hash[i][0] << " " << hash[i][1] << endl;
	}
}