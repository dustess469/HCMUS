#ifndef bai2
#define bai2

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>


using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;
};


void insert(Node*& root, int value);

string check_AVL(Node* root);

#endif // !bai1
