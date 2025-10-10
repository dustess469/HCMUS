#include"Header.h"


struct Node 
{
	int data;
	struct Node* p, * n;
};


struct Node* g_node(int data)
{	
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

	newNode->data = data;

	newNode->p = newNode->n = NULL;
	return newNode;
}


void sortedInsert(struct Node** headaf, struct Node* newNode)
{
	struct Node* current;


	if (*headaf == NULL)
	{
		*headaf = newNode;
	}

	else if ((*headaf)->data >= newNode->data) 
	{
		newNode->n = *headaf;
		newNode->n->p = newNode;
		*headaf= newNode;
	}

	else 
	{
		current = *headaf;

		while (current->n != NULL && current->n->data < newNode->data)
			current = current->n;

		
		newNode->n = current->n;

		if (current->n != NULL)
		{
			newNode->n->p = newNode;
		}

		current->n = newNode;
		newNode->p = current;
	}
}

void insertionSort(struct Node** headaf)
{
	struct Node* sorted = NULL;

	struct Node* current = *headaf;
	while (current != NULL)
	{
		struct Node* next = current->n;

		current->p = current->n = NULL;

		sortedInsert(&sorted, current);

		current = next;
	}

	*headaf = sorted;
}


void printList(struct Node* head)
{
	while (head != NULL) 
	{
		cout << head->data << " ";
		head = head->n;
	}
}


void push(struct Node** headaf, int new_data)
{
	struct Node* new_Node = (struct Node*)
		malloc(sizeof(struct Node));

	new_Node->data = new_data;

	new_Node->n = (*headaf);
	new_Node->p = NULL;

	if ((*headaf) != NULL)
	{
		(*headaf)->p = new_Node;
	}
	(*headaf) = new_Node;
}

int main()
{
	struct Node* head = NULL;

	push(&head, 56);
	push(&head, 234);
	push(&head, 95);
	push(&head, 10);
	push(&head, 92);
	push(&head, 8);

	cout << "DOUBLE LINKED LIST\n";
	cout << "Before Sorting: ";
	printList(head);
	cout << endl;

	insertionSort(&head);

	cout << "\nAfter Sorting: ";
	printList(head);
	cout << endl;
	return 0;
}
