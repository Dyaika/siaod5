#include "Trees.h"

void SearchTree::printTree()
{
	if (root) {
		printNodes(root);
	}
	else {
		cout << "empty\n";
	}
}

void SearchTree::test()
{
	SearchTree s;
	int task = 1;
	int data1, data2;
	Patient* temp;
	fstream b;
	ofstream b0;
	cout << "Welcome to binary search tree test program. Choose task:";
	while (task < 6 and task > 0) {
		cout << "\n1) Create from file\n2) Add element\n3) Find by key\n4) Delete from tree\n5) Print tree\n> ";
		cin >> task;
		switch (task)
		{
		case 1:
			if (!s.isEmpty()) {
				s.clearTree();
				cout << "Tree was cleared.\n";
			}
			cout << "How much notes should it have? ";
			cin >> data1;
			if (b.is_open()) {
				b.close();
			}
			createTextFile("test.txt", data1);
			b0.open("test.dat", ios::binary);
			b0.close();
			b.open("test.dat", ios::binary | ios::out | ios::in);
			textToBinary("test.txt", b);
			for (int i = 0; i < data1; i++) {
				temp = getRowBinary(b, i + 1);
				if (temp) {
					s.add(temp->card, i);
				}
				else {
					cout << "log1\n";
				}
			}
			cout << "---completed---\n";
			break;
		case 2:
			if (b.is_open()) {
				b.close();
				cout << "Binary file was closed. Now you can add new elements to existing tree:\n";
			}
			cout << "key offset (-1 end of input): ";
			cin >> data1;
			while (data1 != -1) {
				cin >> data2;
				s.add(data1, data2);
				cout << "key offset (-1 end of input): ";
				cin >> data1;
			}
			cout << "---added---\n";
			break;
		case 3:
			cout << "Key = ";
			cin >> data1;
			data2 = s.findByKey(data1);
			if (data2 == -1) {
				cout << "not found\n";
			}
			else {
				if (b.is_open()) {
					cout << "Row " << data2 + 1 << ": ";
					printRowBinary(b, data2 + 1);
					cout << "\n";
				}
				else {
					cout << "offset = " << data2 << "\n";
				}
			}
			cout << "---completed---\n";
			break;
		case 4:
			cout << "Key to delete: ";
			cin >> data1;
			if (s.deleteByKey(data1)) {
				cout << "Deleted from tree ";
				if (b.is_open()) {
					cout << "UNDER DEVELOPMENT";
				}
				cout << "\n";
			}
			else {
				cout << "not found\n";
			}
			cout << "---completed---\n";
			break;
		case 5:
			cout << "\n";
			s.printTree();
			cout << "\n---completed---\n";
			break;
		default:
			if (b.is_open()) {
				b.close();
			}
			break;
		}
	}
	cout << "---exit---\n";
}

SearchTree::Node* SearchTree::addNode(int key, int offset, Node* root)
{
	if (root) {
		if (key > root->key) {
			root->rightTree = addNode(key, offset, root->rightTree);
		}
		else if (key < root->key) {
			root->leftTree = addNode(key, offset, root->leftTree);
		}
		else {
			root->offset = offset;
		}
	}
	else {
		root = new Node;
		root->key = key;
		root->offset = offset;
	}
	return root;
}

int SearchTree::findNode(int key, Node* root)
{
	int res = -1;
	if (root) {
		if (root->key == key) {
			return root->offset;
		}
		res = findNode(key, root->rightTree);
		if (res == -1) {
			res = findNode(key, root->leftTree);
		}
	}
	return res;
}

bool SearchTree::deleteNode(int key, Node* root)
{
	cout << "UNDER DEVELOPMENT\n";
	return false;
}

void SearchTree::printNodes(Node* root, int tab_count, int tab_size)
{
	if (root) {
		printNodes(root->rightTree, tab_count + 1);
		for (int i = 0; i < tab_count * tab_size; i++) {
			cout << " ";
		}
		cout << root->key << ":" << root->offset << "\n";
		printNodes(root->leftTree, tab_count + 1);
	}
}

SearchTree::SearchTree(int n)
{
	for (int i = 0; i < n; i++) {
		add(i, i*i);
	}
}

SearchTree::~SearchTree()
{
	delete root;
}

void SearchTree::createFromFile(fstream& b)
{
	cout << "UNDER DEVELOPMENT\n";
}

void SearchTree::clearTree()
{
	size = 0;
	delete root;
	root = nullptr;
}

void SearchTree::add(int key, int offset)
{
	root = addNode(key, offset, root);
	size++;
}

int SearchTree::findByKey(int key)
{
	return findNode(key, root);
}

bool SearchTree::deleteByKey(int key)
{
	return deleteNode(key, root);
}

SearchTree::Node::~Node()
{
	if (leftTree) {
		delete leftTree;
		leftTree = nullptr;
	}
	if (rightTree) {
		delete rightTree;
		rightTree = nullptr;
	}
	//cout << "~" << this->key << "\n";
}
