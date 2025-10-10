#include"Header.h"


//HashFunction1
int hashFunction1(int value, int size) {
	return value % size;
}


void insert1(vector<int> hash[], int value, int size) {
	int id = hashFunction1(value, size);
	hash[id].push_back(value);
}


bool search1(vector<int> hash[], int value, int size) {
	int id = hashFunction1(value, size);
	for (auto i : hash[id]) {
		if (i == value)return true;
	}
	return false;
}


//HashFunction2
int hashFunction2(int value, int size, int i) {
	return (value + i) % size;
}

void insert2(int hash[], int value, int size, int check) {
	int id = hashFunction2(value, size, 0);
	int i = 1;
	while (hash[id] != check) {
		id = hashFunction2(value, size, i);
		i++;
	}
	hash[id] = value;
}

bool search2(int hash[], int value, int size) {
	int id = hashFunction2(value, size, 0);
	int i = 1;
	if (hash[id] == value) return true;
	while (i < size) {
		id = hashFunction2(value, size, i);
		if (hash[id] == value) return true;
		i++;
	}
	return false;
}


//HashFunction3
int hashFunction3(int value, int size, int i) {
	return (value + i * i) % size;
}

void insert3(int hash[], int value, int size, int check) {
	int id = hashFunction3(value, size, 0);
	int i = 1;
	while (hash[id] != check) {
		id = hashFunction3(value, size, i);
		i++;
	}
	hash[id] = value;
}

bool search3(int hash[], int value, int size) {
	int id = hashFunction3(value, size, 0);
	int i = 1;
	if (hash[id] == value) return true;
	while (i < size) {
		id = hashFunction3(value, size, i);
		if (hash[id] == value) return true;
		i++;
	}
	return false;
}