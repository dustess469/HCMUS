#include"Header.h"


Node* newNode(int data)
{
	struct Node* n_node = (struct Node*)malloc(sizeof(struct Node));
	n_node->data = data;
	n_node->left = n_node->right = NULL;
	return n_node;
}



bool checkLeaves(struct Node* root, int level, int* leaf)
{

	if (root == NULL)
	{
		return true;
	}

	if (root->left == NULL && root->right == NULL)
	{
		if (*leaf == 0)
		{
			*leaf = level;
			return true;
		}
		return (level == *leaf);
	}
	return checkLeaves(root->left, level + 1, leaf) && checkLeaves(root->right, level + 1, leaf);
}