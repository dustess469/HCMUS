#include"Header.h"


int main()
{
	Node* root = nullptr;

	root = insert(root, 26);
	root = insert(root, 10);
	root = insert(root, 32);
	root = insert(root, 79);
	root = insert(root, 15);
	root = insert(root, 46);

	//Pre-order
	cout << "Pre-order AVL tree:\n";
	preOrder(root);
	cout << endl;

	//In-order
	cout << "\nIn-order AVL tree:\n";
	inOrder(root);
	cout << endl;

	//Post-order
	cout << "\nPost-order AVL tree:\n";
	postOrder(root);
	cout << endl;


	//DeletionAVLtree
	root = deleteNode(root, 10);
	cout << "\nPreorder after deletion:\n";
	preOrder(root);
	cout << endl;

	cout << "\nHeight AVL tree: " << maxDh(root) << endl;

	cout << "\nIdentify value in tree: " << identify(root, 26) << endl;
	return 0;
}
