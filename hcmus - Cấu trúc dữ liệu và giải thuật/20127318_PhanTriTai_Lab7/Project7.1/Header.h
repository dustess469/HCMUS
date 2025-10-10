#ifndef bai1
#define bai1

#include<iostream>

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
	int height;
};

Node* insert(Node* node, int key);

void preOrder(Node* root);

void inOrder(Node* root);

void postOrder(Node* root);

Node* deleteNode(Node* root, int key);

int maxDh(Node* n_node);

bool identify(Node* n_node, int key);

#endif // !bai1
