#include"Header.h"


int main()
{

	struct Node* root = newNode(69);

	root->left = newNode(24);
	root->right = newNode(15);

	root->left->left = newNode(9);
	root->left->left->left = newNode(10);
	root->right->left = newNode(8);
	root->right->left = newNode(2);

	int level = 0, leafLevel = 0;

	if (checkLeaves(root, level, &leafLevel))
	{
		cout << "All leaves of a AVL tree are same depth\n";
	}
	else
		cout << "All leaves of a AVL tree are not same depth\n";
	return 0;
}