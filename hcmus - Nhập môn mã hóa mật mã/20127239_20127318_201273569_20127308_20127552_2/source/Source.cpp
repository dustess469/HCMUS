#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <map>
#include <set>
#include <iomanip>
#include <stdlib.h>
#include <stack>
#include <fstream>

using namespace std;

#define f(a,b) for(int i=a;i<b;++i)
#define ft(a,b) for(int z=a;z<b;++z)
#define f1(a,b) for(int j=a;j<b;++j)
#define f2(a,b) for(int k=a;k<b;++k)
typedef long long ll;
typedef double db;

int sbox[16] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 };
int RevSbox[16] = { 14,2,11,0,4,6,7,15,8,5,3,9,13,12,1,10 };
int pbox[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0 };
int dif_table[16][16];
int knownP0[20], knownP1[20], knownC0[20], knownC1[20], PKey[20];

int Substitution(int& n) {
	return n = sbox[n];
}

int Permutation(int& n) {
	return n = pbox[n];
}

int encrypt(int plain, int k0, int k1) {
	plain ^= k0;
	plain = Substitution(plain);
	plain = Permutation(plain);

	plain ^= k1;
	plain = Substitution(plain);
	plain = Permutation(plain);
	return plain;
}

void Difference_Table() {
	f(0, 16)
		f1(0, 16)
		++dif_table[i ^ j][sbox[i] ^ sbox[j]];
}

int print_dif_talbe(int pair[][2], int& size) {
	int biggest_probability = 0;
	cout << "Difference Distribution Table: " << endl;
	f(0, 16) {
		f1(0, 16) {
			cout << dif_table[i][j] << " ";
			if (dif_table[i][j] > biggest_probability && i != 0 && j != 0)
				biggest_probability = dif_table[i][j];
		}
		cout << endl;
	}

	int index = 0;
	f(0, 16) {
		f1(0, 16) {
			if (dif_table[i][j] == biggest_probability) {
				pair[index][0] = i;
				pair[index][1] = j;
				++index;
			}
		}
	}
	size = index;
	return biggest_probability;
}

void PlainCipher(int num, int input_Dif) {
	int realK0 = rand() % 16;
	int realK1 = rand() % 16;
	cout << "Key 0: " << realK0 << endl;
	cout << "Key 1: " << realK1 << endl;

	f(0, num) {
		knownP0[i] = i;
		knownP1[i] = knownP0[i] ^ input_Dif;
		knownC0[i] = encrypt(knownP0[i], realK0, realK1);
		knownC1[i] = encrypt(knownP1[i], realK0, realK1);
	}
}

int findKey(int num, int out_Dif) {
	int biggest_prob = 0;
	int K1;
	f(0, num) {
		f1(0, num) {
			int y1 = RevSbox[(knownP0[i] - 1) % 16];
			int y2 = RevSbox[(knownP1[j] - 1) % 16];
			if ((y1 ^ y2) == out_Dif)
				++PKey[y1 ^ y2];

		}
	}
	f(0, 16)
		if (biggest_prob < PKey[i])
			biggest_prob = PKey[i];
	f(0, 16)
		if (PKey[i] == biggest_prob)
			K1 = i;
	return K1 + 1;
}

int main() {
	int probility, pair[100][2], size;
	int K1found;
	Difference_Table();
	probility = print_dif_talbe(pair, size);
	cout << "Biggest probility: " << probility << endl;
	cout << "Input Dif: " << pair[0][0] << endl;
	cout << "Output Dif: " << pair[0][1] << endl;
	PlainCipher(10, pair[0][0]);
	K1found = findKey(10, pair[0][1]);
	cout << "K1 found: ";
	cout << K1found << endl;
	return 0;
}