#include"Header.h"

struct Node {
	int data;
	Node* next;
	Node(int d) {
		data = d;
		next = NULL;
	}
};

struct Queue {
	Node* f, * l;
	Queue() {
		f = l = NULL;
	}

	void enqueue(int ans) {

		Node* tmp = new Node(ans);

		if (l == NULL) {
			f = l = tmp;
			return;
		}

		l->next = tmp;
		l = tmp;
	}

	void dequeue() {

		if (f == NULL)
			return;


		Node* tmps = f;
		f = f->next;


		if (f == NULL)
			l = NULL;

		delete (tmps);
	}


	int displayBit() {
		int t = 0;
		if (f == NULL)
			return 0;
		Node* temp = f;
		while (temp->next != nullptr) {
			t += sizeof(temp->data);
			temp = temp->next;
		}
		t += sizeof(temp->data);
		return t;
	}
};


int main() {

	Queue qe;

	qe.enqueue(1);
	qe.enqueue(2);
	qe.dequeue();
	qe.enqueue(3);
	qe.enqueue(4);
	qe.enqueue(5);
	qe.dequeue();
	qe.dequeue();

	cout << "Queue first is: " << (qe.f)->data << endl;
	cout << "Queue last is: " << (qe.l)->data << endl;
	cout << "Memory status: " << qe.displayBit() << endl;
}