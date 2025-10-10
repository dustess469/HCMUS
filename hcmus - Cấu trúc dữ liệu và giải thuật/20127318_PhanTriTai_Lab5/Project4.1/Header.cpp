#include"Header.h"

struct Node {
	int data;
	struct Node* Linklist;
};

struct Node* top;


void push(int data) {

	struct Node* tmp;
	tmp = new Node();


	if (!tmp) {
		cout << "\nHeap is overflow";
		exit(1);
	}

	tmp->data = data;

	tmp->Linklist = top;

	top = tmp;
}


int checkEmpty() {
	return top == NULL;
}


int fristElement() {

	if (!checkEmpty()) {
		return top->data;
	}
	else {
		exit(1);
	}
}


void pop() {
	struct Node* tmps;


	if (top == NULL) {
		cout << "\nStack is underflow";
		exit(1);
	}
	else {
		tmps = top;
		top = top->Linklist;
		tmps->Linklist = NULL;
		free(tmps);
	}
}


void display() {
	struct Node* temp;

	if (top == NULL) {
		cout << "\nStack is underflow";
		exit(1);
	}
	else {
		temp = top;
		while (temp != NULL) {

			cout << temp->data << endl;

			temp = temp->Linklist;
		}
	}
}

int displayBit() {
	struct Node* t;
	int st = 0;
	if (top == NULL) {
		return 0;
	}
	else {
		t = top;
		while (t != NULL) {
			st += sizeof(t);
			t = t->Linklist;
		}
	}
}
