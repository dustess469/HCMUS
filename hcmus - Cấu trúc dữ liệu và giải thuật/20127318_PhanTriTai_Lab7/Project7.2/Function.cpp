#include"Header.h"

void insert(Node*& root, int value)
{

	if (root == nullptr)
	{
		Node* node = new Node;
		node->data = value;
		node->left = nullptr;
		node->right = nullptr;
		root = node;
	}

	else
	{

		if (value < root->data)
		{
			insert(root->left, value);
		}

		else
			insert(root->right, value);
	}
}


int max(int a, int b)
{
	if (a > b) return a;
	else
		return b;
}


int height(Node* root)
{
	if (root == nullptr) return 0;
	else
		return max(height(root->left), height(root->right)) + 1;
}


string check_AVL(Node* root)
{
	int leftH, rightH;
	if (root == nullptr) return  "YES";

	leftH = height(root->left);
	rightH = height(root->right);

	int abs_lr = abs(leftH - rightH);
	if (abs_lr <= 1 && check_AVL(root->left) == "YES" && check_AVL(root->right) == "YES")
	{
		return "YES";
	}
	else
		return "NO";
}
