#include "Trees.h"

//Search Tree
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
	int next_offset = 0;
	cout << "Welcome to binary search tree test program. Choose task:";
	while (task < 7 and task > 0) {
		cout << "\n1) Create from file\n2) Add element\n3) Find by key\n4) Delete from tree\n5) Print tree\n6) Close file\n> ";
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
			if (data1 < 0) {
				next_offset = 0;
			}
			else
			{
				next_offset = data1;
			}
			if (b.is_open()) {
				b.close();
			}
			createTextFile("test.txt", data1);
			b0.open("test.dat", ios::binary);
			b0.close();
			b.open("test.dat", ios::binary | ios::out | ios::in);
			textToBinary("test.txt", b);
			s.createFromFile(b);
			cout << "---completed---\n";
			break;
		case 2:
			if (b.is_open()) {
				cout << "card illness doctor: ";
				temp = new Patient;
				cin >> temp->card >> temp->illness >> temp->doctor;
				addRow(b, temp);
				s.add(temp->card, next_offset);
				next_offset++;
				delete temp;
				temp = nullptr;
			}
			else {
				cout << "key offset (-1 end of input): ";
				cin >> data1;
				while (data1 != -1) {
					cin >> data2;
					s.add(data1, data2);
					cout << "key offset (-1 end of input): ";
					cin >> data1;
				}
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
			s.deleteByKeyS(data1); 
			cout << "Now tree";
			if (b.is_open()) {
				deleteByKey(b, data1);
				cout << " and file";
			}
			cout << " does not have key=" << data1 << "\n";
			cout << "---completed---\n";
			break;
		case 5:
			cout << "\n";
			s.printTree();
			cout << "\n---completed---\n";
			break;
		case 6:
			if (b.is_open()) {
				b.close();
				cout << "---closed---\n";
			}
			else {
				cout << "---no file---\n";
			}
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

SearchTree::Node* SearchTree::deleteNode(int key, Node* root)
{
	Node* res = root;
	Node* to_delete = nullptr;
	Node* cur = nullptr;
	if (root) {
		if (root->key == key) {
			to_delete = root;
			if (root->leftTree) {
				if (root->rightTree) {
					res = root->leftTree;
					cur = res;
					while (cur->rightTree) {
						cur = cur->rightTree;
					}
					cur->rightTree = root->rightTree;
					to_delete->leftTree = nullptr;
					to_delete->rightTree = nullptr;
				}
				else {
					res = root->leftTree;
					to_delete->leftTree = nullptr;
				}
			}
			else if (root->rightTree) {
				res = root->rightTree;
				to_delete->rightTree = nullptr;
			}
			else {
				res = nullptr;
			}
			delete to_delete;
			return res;
		}
		res->rightTree = deleteNode(key, root->rightTree);
		res->leftTree = deleteNode(key, root->leftTree);
	}
	return res;
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
	int i = 0;
	Patient *temp = nullptr;
	do {
		temp = getRowBinary(b, i + 1);
		if (temp) {
			add(temp->card, i);
			//cout << temp->card << " " << i << "\n";
		}
		
		i++;
	} while (temp);
	//printAllBinary(b);
}

void SearchTree::clearTree()
{
	delete root;
	root = nullptr;
}

void SearchTree::add(int key, int offset)
{
	root = addNode(key, offset, root);
}

int SearchTree::findByKey(int key)
{
	return findNode(key, root);
}

void SearchTree::deleteByKeyS(int key)
{
	root = deleteNode(key, root);
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

