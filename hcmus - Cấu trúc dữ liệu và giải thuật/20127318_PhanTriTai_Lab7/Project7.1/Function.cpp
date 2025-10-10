#include"Header.h"

int height(Node* n_node)
{
	if (n_node == nullptr)
	{
		return 0;
	}
	else
		return n_node->height;
}


int max(int a, int b)
{
	if (a < b) return a;
	else
		return b;
}


Node* newNode(int key)
{
	Node* node = new Node();
	node->data = key;
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1;

	return(node);
}


Node* leftRotate(Node* l)
{
	Node* lt = l->right;
	Node* T2 = lt->left;

	lt->left = l;
	l->right = T2;

	l->height = max(height(l->left), height(l->right)) + 1;
	lt->height = max(height(lt->left), height(lt->right)) + 1;

	return lt;
}


Node* rightRotate(Node* r)
{
	Node* rt = r->left;
	Node* T2 = rt->right;


	rt->right = r;
	r->left = T2;


	r->height = max(height(r->left), height(r->right)) + 1;
	rt->height = max(height(rt->left), height(rt->right)) + 1;

	return rt;
}


int	lastBalance(Node* n_node)
{
	if (n_node == nullptr) {
		return 0;
	}
	else
		return height(n_node->left) - height(n_node->right);
}


Node* insert(Node* node, int key)
{
	if (node == nullptr) {
		return(newNode(key));
	}

	if (key < node->data)
	{
		node->left = insert(node->left, key);
	}
	else if (key > node->data)
	{
		node->right = insert(node->right, key);
	}
	else
		return node;


	node->height = 1 + max(height(node->left), height(node->right));


	int balance = lastBalance(node);


	if (balance > 1 && key < node->left->data)
	{
		return rightRotate(node);
	}


	if (balance < -1 && key > node->right->data)
	{
		return leftRotate(node);
	}

	if (balance > 1 && key > node->left->data)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node->right->data)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}


Node* minNode(Node* node)
{
	Node* current = node;

	while (current->left != nullptr)
		current = current->left;

	return current;
}


Node* deleteNode(Node* root, int key)
{

	if (root == nullptr)
	{
		return root;
	}

	if (key < root->data)
	{
		root->left = deleteNode(root->left, key);
	}

	else if (key > root->data)
	{
		root->right = deleteNode(root->right, key);
	}

	else
	{
		if ((root->left == nullptr) || (root->right == nullptr))
		{
			Node* tmp = root->left ?
				root->left :
				root->right;

			if (tmp == nullptr)
			{
				tmp = root;
				root = nullptr;
			}
			else
				*root = *tmp;

			free(tmp);
		}
		else
		{

			Node* tmp = minNode(root->right);


			root->data = tmp->data;


			root->right = deleteNode(root->right, tmp->data);
		}
	}


	if (root == nullptr)
	{
		return root;
	}


	root->height = 1 + max(height(root->left), height(root->right));


	int balance = lastBalance(root);


	if (balance > 1 && lastBalance(root->left) >= 0)
	{
		return rightRotate(root);
	}


	if (balance > 1 && lastBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}


	if (balance < -1 && lastBalance(root->right) <= 0)
	{
		return leftRotate(root);
	}


	if (balance < -1 && lastBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

//Pre-order fun
void preOrder(Node* root)
{
	if (root != nullptr)
	{
		cout << root->data << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

//In-order fun
void inOrder(Node* root)
{
	if (root != nullptr)
	{
		inOrder(root->left);
		cout << root->data << " ";
		inOrder(root->right);
	}
}

//Post-order fun
void postOrder(Node* root)
{
	if (root != nullptr)
	{
		postOrder(root->left);
		postOrder(root->right);
		cout << root->data << " ";
	}
}

int maxDh(Node* n_node)
{
	if (n_node == nullptr)
	{
		return 0;
	}

	else
	{
		int lDh = maxDh(n_node->left);
		int rDh = maxDh(n_node->right);


		if (lDh > rDh)
		{
			return(lDh + 1);
		}
		else
			return(rDh + 1);
	}
}

bool identify(Node* n_node, int key)
{
	if (n_node == nullptr)
		return false;

	if (n_node->data == key)
		return true;


	bool tmp = identify(n_node->left, key);

	if (tmp) return true;

	bool res = identify(n_node->right, key);

	return res;
}
