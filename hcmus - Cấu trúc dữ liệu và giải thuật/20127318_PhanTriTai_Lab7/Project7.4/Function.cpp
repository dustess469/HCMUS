#include"Header.h"


Node* newNode(int d)
{
	Node* temp = new Node;
	temp->data = d;
	temp->left = temp->right = NULL;
	return temp;
}


struct Node* findCommon(struct Node* root, int node1, int node2)
{
	if (root == NULL) return NULL;


	if (root->data == node1 || root->data == node2) return root;

	Node* leftlca = findCommon(root->left, node1, node2);
	Node* rightlca = findCommon(root->right, node1, node2);

	if (leftlca && rightlca) return root;

	if (leftlca != NULL) return leftlca;
	else return rightlca;

}
