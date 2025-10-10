#include <iostream>
#include<vector>
#include<queue>

using namespace std;


struct Node
{
    int key;
    vector <Node*> c;
};


Node* newNode(int key)
{
    Node* tmp = new Node;
    tmp->key = key;
    return tmp;
}


void level(Node* root)
{
    if (root == NULL)
        return;

    queue<Node*> q; 
    q.push(root); 
    while (!q.empty())
    {
        int n = q.size();

        while (n > 0)
        {
            Node* p = q.front();
            q.pop();
            cout << p->key << " ";

            
            for (int i = 0; i < p->c.size(); i++)
                q.push(p->c[i]);
            n--;
        }

        cout << endl; 
    }
}


int main()
{
    Node* root = newNode(10);

    (root->c).push_back(newNode(2));
    (root->c).push_back(newNode(34));
    (root->c).push_back(newNode(56));
    (root->c).push_back(newNode(100));

    (root->c[0]->c).push_back(newNode(77));
    (root->c[0]->c).push_back(newNode(88));
    (root->c[2]->c).push_back(newNode(1));
    (root->c[3]->c).push_back(newNode(7));
    (root->c[3]->c).push_back(newNode(8));
    (root->c[3]->c).push_back(newNode(9));

    cout << "Before Mirroring\n";
    level(root);

    return 0;
}