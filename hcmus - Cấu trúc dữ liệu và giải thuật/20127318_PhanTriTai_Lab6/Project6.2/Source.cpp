#include"Header.h"

struct Student
{
	string ID, name, birth;
	bool status;
};


struct Node
{
	Node* left, * right;
	Student data;
};


Node* CreateNode(Student data)
{
	Node* newnode = new Node;
	newnode->data = data;
	newnode->left = nullptr;
	newnode->right = nullptr;
	return newnode;
}


void InsertStudent(Node*& root, Student& value) 
{
	if (root == nullptr)
	{
		root = CreateNode(value);
	}

	else
	{
		if (root->data.ID.compare(value.ID) == 0)
		{
			return;
		}
		if (root->data.ID.compare(value.ID) > 0)
		{
			InsertStudent(root->left, value);
		}
		if (root->data.ID.compare(value.ID) < 0)
		{
			InsertStudent(root->right, value);
		}
	}
}


void PrintTree(Node* root) 
{
	Student St;


	if (!root)
	{
		return;
	}

	PrintTree(root->left);
	PrintTree(root->right);

	St = root->data;
	cout << St.ID << " ";
	cout << St.name << " ";
	cout << St.birth << " ";
	cout << St.status << " ";
	cout << endl;
}


void ReadFile(const char* filename, Node*& root, Student& St, int& n) 
{
	ifstream Infile(filename);

	if (!Infile.is_open())
	{
		cout << "Have file\n";
		return;
	}

	else
	{
		Infile >> n;
		for (int i = 0; i < n; i++)
		{
			Infile.ignore();
			getline(Infile, St.ID);
			getline(Infile, St.name);
			getline(Infile, St.birth);
			Infile >> St.status;
			InsertStudent(root, St);
		}
	}
	Infile.close();
}


void WriteNewFile(const char* filename, Node*& root, int m)
{
	ofstream Outfile(filename);

	if (!Outfile.is_open())
	{
		cout << "Can't open file. ";
		return;
	}

	else
	{
		Outfile << m;
		for (int i = 0; i < m; i++)
		{
			Outfile << root->data.ID << endl;
			Outfile << root->data.name << endl;
			Outfile << root->data.birth << endl;
			Outfile << root->data.status << endl;
		}
	}
	Outfile.close();
}


void ShowGraduate(Node* root) 
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		if (root->data.status == 1)
		{
			cout << root->data.ID << " ";
			cout << root->data.name << " ";
			cout << root->data.birth << " ";
			cout << root->data.status << " ";
			cout << endl;
		}
		ShowGraduate(root->left);
		ShowGraduate(root->right);
	}
}

Node* FindMinRight(Node* root) 
{
	Node* temp = root;
	while (temp != nullptr && temp->left != nullptr)
	{
		temp = temp->left;
	}
	return temp;
}


Node* DeleteByCode(Node* root, string code) 
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (root->data.ID.compare(code) == 0)
		{
			if (root->left == nullptr)
			{
				Node* temp = root->right;
				free(root);
				return temp;
			}
			if (root->right == nullptr)
			{
				Node* temp = root->left;
				free(root);
				return temp;
			}

			Node* temp = FindMinRight(root->right);
			root->data = temp->data;
			root->right = DeleteByCode(root->right, temp->data.ID);
		}
		if (root->data.ID.compare(code) > 0)
		{
			root->left = DeleteByCode(root->left, code);
		}
		if (root->data.ID.compare(code) < 0)
		{
			root->right = DeleteByCode(root->right, code);
		}
	}
	return root;
}


void InsertNewStudent(Node*& root, Student& value) 
{
	cout << "Enter ID: ";
	cin >> value.ID;
	cout << "Enter Name: ";
	cin >> value.name;
	cout << "Enter Date: ";
	cin >> value.birth;
	cout << "Enter Status (1 or 0): ";
	cin >> value.status;
	InsertStudent(root, value);
}


Node* FindByCode(Node* root, string code) 
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (root->data.ID.compare(code) == 0)
		{
			cout << "Student: " << endl;
			cout << root->data.ID << " ";
			cout << root->data.name << " ";
			cout << root->data.birth << " ";
			cout << root->data.status << " ";
		}
		if (root->data.ID.compare(code) > 0)
		{
			root->left = FindByCode(root->left, code);
		}
		if (root->data.ID.compare(code) < 0)
		{
			root->right = FindByCode(root->right, code);
		}
	}
	return root;

}


Node* DeleteAllGraduate(Node* root, int& count) 
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (root->data.status == 1)
		{
			count++;
			if (root->left == nullptr)
			{
				Node* temp = root->right;
				free(root);
				return temp;
			}
			if (root->right == nullptr)
			{
				Node* temp = root->left;
				free(root);
				return temp;
			}

			Node* temp = FindMinRight(root->right);
			root->data = temp->data;
			root->right = DeleteByCode(root->right, temp->data.ID);
		}
		root->left = DeleteAllGraduate(root->left, count);
		root->right = DeleteAllGraduate(root->right, count);
	}
	return root;
}


Node* UpdateAfterFind(Node* root, string code) 
{
	if (root == nullptr)
	{
		return nullptr;
	}
	else
	{
		if (root->data.ID.compare(code) == 0)
		{
			cout << "Enter infomation you want to update:\n";
			cout << "Enter ID: ";
			cin >> root->data.ID;
			cout << "Enter Name: ";
			cin >> root->data.name;
			cout << "Enter Date: ";
			cin >> root->data.birth;
			cout << "Enter Status (1 or 0): ";
			cin >> root->data.status;
		}

		if (root->data.ID.compare(code) > 0)
		{
			root->left = UpdateAfterFind(root->left, code);
		}
		if (root->data.ID.compare(code) < 0)
		{
			root->right = UpdateAfterFind(root->right, code);
		}
	}
	return root;
}


void BinTreeToLList(Node* root, Node*& head) 
{
	if (root == NULL) return;

	static Node* prev = NULL;

	BinTreeToLList(root->left, head);

	if (prev == NULL)
		head = root;
	else
	{
		root->left = prev;
		prev->right = root;
	}
	prev = root;

	BinTreeToLList(root->right, head);
}


void PrintList(Node* head) 
{
	while (head != NULL)
	{
		cout << head->data.ID << endl;
		cout << head->data.name << endl;
		cout << head->data.birth << endl;
		cout << head->data.status << endl;
		head = head->right;
	}
}


void SortedInsert(Node*& temp, Node* NewNode)
{
	struct Node* current;

	if (temp == NULL)
		temp = NewNode;

	else if ((temp)->data.name >= NewNode->data.name)
	{
		NewNode->right = temp;
		NewNode->right->left = NewNode;
		temp = NewNode;
	}

	else
	{
		current = temp;

		while (current->right != NULL && current->right->data.name < NewNode->data.name)
			current = current->right;

		NewNode->right = current->right;

		if (current->right != NULL)
			NewNode->right->left = NewNode;

		current->right = NewNode;
		NewNode->left = current;
	}
}


void InsertionSort(Node*& temp) 
{
	Node* sorted = NULL;
	Node* current = temp;

	while (current != NULL)
	{
		struct Node* next = current->right;
		current->left = current->right = NULL;
		SortedInsert(sorted, current);
		current = next;
	}
	temp = sorted;
}



int main()
{
	int size;
	Student Stu;
	Node* root = nullptr;
	int option;

	ReadFile("input.txt", root, Stu, size);

	cout << "\nList:\n";
	PrintTree(root);
	cout << endl;

	cout << "=============MENU============\n";
	cout << "1. Create new student info and insert it to BST.\n";
	cout << "2. Find a student.\n";
	cout << "3. List all students in lexicographic order of their names.\n";
	cout << "4. List all graduated students.\n";
	cout << "5. Delete a student given.\n";
	cout << "6. Delete all graduates or save all students in file.\n";
	cout << "7. Exit.\n";
	
	cout << "\nEnter your option: ";
	cin >> option;
	cout << endl;
	system("cls");

	switch (option)
	{
	case 1:
	{
		cout << "1. Create new student info and insert it to BST.\n";
		InsertNewStudent(root, Stu);
		
		cout << "\nAfter inserting:\n";
		PrintTree(root);
		break;
	}
	case 2:
	{
		cout << "2. Find a student.\n";
		
		string code;
		int choice;
		cout << "\nEnter student's ID you want to find: ";
		cin >> code;
		cout << endl;

		root = FindByCode(root, code);
		
		cout << "\nDo you want to update information (Yes-1 No-0): ";
		cin >> choice;
		cout << endl;

		if (choice == 1)
		{
			cin.ignore();
			root = UpdateAfterFind(root, code);
			
			cout << "\nAfter updating:\n";
			PrintTree(root);

		}
		if (choice == 0)
		{
			cin.ignore();
			cout << "List:\n";
			PrintTree(root);
		}
		break;
	}
	case 3:
	{
		Node* head = nullptr;
		cout << "3. List all students in lexicographic order of their names.\n";
		BinTreeToLList(root, head);
		
		cout << "\nList after sorting:\n";
		InsertionSort(head);
		PrintList(head);
		break;
	}
	case 4:
	{
		cout << "4. List all graduated students.\n";
		ShowGraduate(root);
		break;
	}
	case 5:
	{
		cout << "5. Delete a student given.\n";
		string code;

		cout << "Enter student's ID you want to delete: ";
		cin >> code;

		root = DeleteByCode(root, code);
		
		cout << "\nList after deleting:\n";
		PrintTree(root);
		break;
	}
	case 6:
	{
		Student St;
		int count = 0;
		cout << "6. Delete all graduates or save all students in file.\n";
		root = DeleteAllGraduate(root, count);
		
		cout << "\nList after deleting all graduates:\n";
		PrintTree(root);
		WriteNewFile("student.data.txt", root, size - count);
		
		cout << "\nComplete Saving!\n";
		break;
	}
	case 7:
	{
		exit(1);
		break;
	}
	}
	return 0;
}