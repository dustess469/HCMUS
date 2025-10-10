#ifndef bai4
#define bai4

#include <iostream>

using namespace std;

struct Node
{
	int data;
	struct Node* left, * right;
};


Node* newNode(int d);

struct Node* findCommon(struct Node* root, int node1, int node2);
#endif // !bai4
