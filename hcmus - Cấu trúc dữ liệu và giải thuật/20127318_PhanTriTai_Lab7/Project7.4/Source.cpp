#include"Header.h"


int main()
{
	Node* root = newNode(27);

	root->left = newNode(10);
	root->right = newNode(17);

	root->left->left = newNode(9);
	root->left->right = newNode(1);
	root->right->left = newNode(4);
	root->right->right = newNode(2);

	cout << " The least common ancestor(1, 2) = " << findCommon(root, 1, 2)->data << endl;
	cout << " The least common ancestor(4, 9) = " << findCommon(root, 4, 9)->data << endl;
	cout << " The least common ancestor(1, 10) = " << findCommon(root, 1, 10)->data << endl;
	return 0;
}
