#ifndef bai3
#define bai3

#include <iostream>

using namespace std;

struct Node
{
	int data;
	struct Node* left, * right;
};


Node* newNode(int data);

bool checkLeaves(struct Node* root, int level, int* leaf);
#endif // !bai3
