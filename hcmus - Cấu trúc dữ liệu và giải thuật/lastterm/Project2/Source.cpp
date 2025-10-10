#include "Header.h"


struct Node 
{
    int data;
    Node* left;
    Node* right;
};
#define COUNT 20

Node* createNode(int data);
Node* insert(Node* root, int data);
void LRN(Node* t);
void NLR(Node* t);
void NodeThe(Node*& X, Node*& Y);
void XoaNode(Node*& t, int data);
void printTree(Node* root, int space);
bool Check(Node* root, int sum, unordered_set<int>& key);


Node* createNode(int data) 
{
    Node* p = new Node;
    p->data = data;
    p->left = p->right = nullptr;
    return p;
}


Node* insert(Node* root, int data) 
{
    if (root == nullptr) {
        root = createNode(data);
        return root;
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    else if (data < root->data) {
        root->left = insert(root->left, data);
    }
    return root;
}


void  LRN(Node* t)
{
    if (t != NULL)
    {
        LRN(t->left);
        LRN(t->right);
        cout << t->data << "  ";
    }
}


void NLR(Node* t)
{
    if (t != NULL)
    {
        cout << t->data << " ";
        NLR(t->left);
        NLR(t->right);
    }
}


void NodeThe(Node*& X, Node*& Y)
{
    if (Y->left != NULL)
    {
        NodeThe(X, Y->left);
    }
    else {
        X->data = Y->data;
        X = Y;
        Y = Y->right;
    }
}


void XoaNode(Node*& t, int data)
{
    if (t == NULL)
    {
        cout << endl << "False";
        return;

    }
    else
    {
        if (data < t->data)
        {
            XoaNode(t->left, data);
        }
        else if (data > t->data)
        {
            XoaNode(t->right, data);
        }
        else {
            Node* X = t;
            if (t->left == NULL)
            {
                t = t->right;
            }
            else if (t->right == NULL)
            {
                t = t->left;
            }
            else
            {
                NodeThe(X, t->right);
            }
            delete X;
        }
    }

}


void printTree(Node* root, int space)
{
    if (root == NULL)
        return;
    space += COUNT;
    printTree(root->right, space);
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << "\n";
    printTree(root->left, space);
}


bool Check(Node* root, int sum, unordered_set<int>& key) {
    if (root == NULL)
        return false;
    if (Check(root->left, sum, key))
        return true;
    if (key.find(sum - root->data) != key.end()) {
        return true;
    }
    else
        key.insert(root->data);
    return Check(root->right, sum, key);
}


int main() 
{
    Node* root = nullptr;
    root = insert(root, 25);
    root = insert(root, 32);
    root = insert(root, 14);
    root = insert(root, 21);
    root = insert(root, 19);
    root = insert(root, 17);
    root = insert(root, 23);
    
    cout << "BST:";
    printTree(root, 0);
    LRN(root);

    cout << endl << "BST LRN: \n";
    printTree(root, 0);
    NLR(root);

    cout << endl << "BST NLR: \n";
    printTree(root, 0);

    cout << "Nhap nut k can xoa: ";
    int k;
    cin >> k;
    XoaNode(root, k);
    printTree(root, 0);

}