#include"Header.h"

struct Node {
	int value;
	struct Node* next;
	Node(int x)
	{
		value = x;
		next = NULL;
	}
};

class Linkedlist {

public:
	Node* head;
	Node* tail;

	void push(int n)
	{

		Node* newNode = new Node(n);

		newNode->next = head;

		head = newNode;
	}


	void insert(Node* newNode)
	{

		if (tail == NULL || tail->value >= newNode->value) {
			newNode->next = tail;
			tail = newNode;
		}
		else {
			Node* current = tail;

			while (current->next != NULL && current->next->value < newNode->value) {
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
	}


	void insertionSort(Node* headafter)
	{
		tail = NULL;
		Node* current = headafter;

		while (current != NULL) {
			Node* next = current->next;
			insert(current);
			current = next;
		}
		head = tail;
	}


	void print(Node* head)
	{
		while (head != NULL) {
			cout << head->value << " ";
			head = head->next;
		}
	}
};



int main()
{
	Linkedlist list;
	list.head = NULL;
	list.push(12);
	list.push(658);
	list.push(25);
	list.push(3);
	list.push(90);
	list.push(27);

	cout << "SINGLE LINKED LIST\n";
	cout << "Before sorting: ";
	list.print(list.head);
	cout << endl;

	list.insertionSort(list.head);

	cout << "\nAfter sorting: ";
	list.print(list.head);
	cout << endl;
	return 0;
}