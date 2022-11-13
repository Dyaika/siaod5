#include "BTreeVirt.h"

BTreeVirt::Node::Node(int n, bool isleaf)
{
	this->n = n;
	this->isleaf = isleaf;
	keys = new int[2 * n - 1];
	offsets = new int[2 * n - 1];
	children = new BTreeVirt::Node * [2 * n];
	count = 0;
}

void BTreeVirt::Node::traverse()
{
	for (int i = 0; i < count; i++) {
		if (!isleaf) {
			children[i]->traverse();
		}
		cout << " " << keys[i];
	}
	if (!isleaf) {
		children[count]->traverse();
	}
}

void BTreeVirt::printNodes(Node* root, int tab_count, int tab_size)
{
	if (root) {
		if (!root->isleaf) {
			printNodes(root->children[root->count], tab_count + 1);
		}
		for (int i = root->count - 1; i >= 0; i--) {
			for (int j = 0; j < tab_count * tab_size; j++) {
				cout << " ";
			}
			cout << root->keys[i] << ":" << root->offsets[i] << "\n";
			if (!root->isleaf) {
				printNodes(root->children[i], tab_count + 1);
			}
		}
	}
}

void BTreeVirt::Node::insertNonFull(int key, int offset)
{
	int i = count - 1;
	if (isleaf) {
		while (i >= 0 and keys[i] > key) {
			keys[i + 1] = keys[i];
			offsets[i + 1] = offsets[i];
			i--;
		}
		keys[i + 1] = key;
		offsets[i + 1] = offset;
		count++;
	}
	else {
		while (i >= 0 and keys[i] > key) {
			i--;
		}
		if (children[i + 1]->count == 2 * n - 1) {
			//заполнен ребенок -> режем
			splitChild(i + 1, children[i + 1]);
			//средний ребенок улетел вверх и разделилс€
			//смотрим куда теперь ставить ключ
			if (keys[i + 1] < key) {
				i++;
			}
		}
		children[i + 1]->insertNonFull(key, offset);
	}
}

void BTreeVirt::Node::splitChild(int index, Node* node1)
{
	Node* node2 = new Node(node1->n, node1->isleaf);
	node2->count = n - 1;
	//тащим последние n-1 ключей из node1 в node2
	for (int i = 0; i < n - 1; i++) {
		node2->keys[i] = node1->keys[i + n];
		node2->offsets[i] = node1->offsets[i + n];
	}
	//тащим последние n детей из node1 в node2
	if (!node1->isleaf) {
		for (int i = 0; i < n; i++) {
			node2->children[i] = node1->children[i + n];
		}
	}
	node1->count = n - 1;
	//делаем пустоту дл€ ребенка в “≈ ”ў≈ћ узле
	for (int i = count; i >= (index + 1); i--) {
		children[i + 1] = children[i];
	}
	children[index + 1] = node2;
	//один ключ из node1 переехал в текущий узел. сдвинем большие ключи вправо
	for (int i = count - 1; i >= index; i--) {
		keys[i + 1] = keys[i];
		offsets[i + 1] = offsets[i];
	}
	keys[index] = node1->keys[n - 1];
	offsets[index] = node1->offsets[n - 1];
	count++;
}

BTreeVirt::Node* BTreeVirt::Node::search(int key)
{
	int i = 0;
	while (i < count and key > keys[i]) {
		i++;
	}
	if (keys[i] == key) {
		return this;
	}
	if (isleaf) {
		return nullptr;
	}
	return children[i]->search(key);
}

int BTreeVirt::Node::findIndex(int key)
{
	int index = 0;
	while (index < count and keys[index] < key) {
		++index;
	}
	return index;
}

void BTreeVirt::Node::remove(int key)
{
	int index = findIndex(key);

	//есть в текущем узле
	if (index < count and keys[index] == key) {
		if (isleaf) {
			removeFromLeaf(index);
		}
		else {
			removeFromNonLeaf(index);
		}
	}
	//нет в текущем узле
	else {
		if (isleaf) {
			return;
		}
		bool flag = index == count;
		if (children[index]->count < n) {
			fill(index);
		}
		if (flag and index > count) {
			children[index - 1]->remove(key);
		}
		else {
			children[index]->remove(key);
		}
	}
	
}

void BTreeVirt::Node::removeFromLeaf(int index)
{
	for (int i = index + 1; i < count; ++i) {
		keys[i - 1] = keys[i];
		offsets[i - 1] = offsets[i];
	}
	count--;
}

void BTreeVirt::Node::removeFromNonLeaf(int index)
{
	nodeData dat;
	dat.key = keys[index];
	dat.offset = offsets[index];

	//если дочерний элемент, предшеств. ключу имеет не менее n элементов
	if (children[index]->count >= n) {
		nodeData pred = getPred(index);
		keys[index] = pred.key;
		offsets[index] = pred.offset;
		children[index]->remove(pred.key);
	}
	//если дочерний элемент имеет менее count ключей
	else if (children[index + 1]->count >= n) {
		nodeData succ = getSucc(index);
		keys[index] = succ.key;
		offsets[index] = succ.offset;
		children[index + 1]->remove(succ.key);
	}
	//если и children[index] и children[index+1] имеют меньше n элементов
	else {
		merge(index);
		children[index]->remove(dat.key);
	}
}

BTreeVirt::Node::nodeData BTreeVirt::Node::getPred(int index)
{
	Node* cur = children[index];
	while (!cur->isleaf) {
		cur = cur->children[cur->count - 1];
	}
	nodeData res;
	res.key = cur->keys[cur->count - 1];
	res.offset = cur->offsets[cur->count - 1];
	return res;
}

BTreeVirt::Node::nodeData BTreeVirt::Node::getSucc(int index)
{
	Node* cur = children[index + 1];
	while (!cur->isleaf) {
		cur = cur->children[0];
	}
	nodeData res;
	res.key = cur->keys[0];
	res.offset = cur->offsets[0];
	return res;
}

void BTreeVirt::Node::fill(int index)
{
	//если предыдущий ребенок имеет больше n-1 ключей, забираем оттуда
	if (index != 0 and children[index - 1]->count >= n) {
		borrowFromPrev(index);
	}
	//если следующий ребенок имеет больше n-1 ключей, забираем оттуда
	else if (index != count and children[index + 1]->count >= n) {
		borrowFromNext(index);
	}
	else {
		if (index != count) {
			merge(index);
		}
		else {
			merge(index - 1);
		}
	}
}

void BTreeVirt::Node::borrowFromPrev(int index)
{
	Node* child = children[index];
	Node* sibling = children[index - 1];
	for (int i = child->count - 1; i >= 0; --i) {
		child->keys[i + 1] = child->keys[i];
		child->offsets[i + 1] = child->offsets[i];
	}
	if (!child->isleaf) {
		for (int i = child->count; i >= 0; --i) {
			child->children[i + 1] = child->children[i];
		}
	}
	child->keys[0] = keys[index - 1];
	child->offsets[0] = offsets[index - 1];
	if (!child->isleaf) {
		child->children[0] = sibling->children[sibling->count];
	}
	keys[index - 1] = sibling->keys[sibling->count];
	offsets[index - 1] = sibling->offsets[sibling->count];
	child->count++;
	sibling->count--;
}

void BTreeVirt::Node::borrowFromNext(int index)
{
	Node* child = children[index];
	Node* sibling = children[index + 1];
	child->keys[child->count] = keys[index];
	child->offsets[child->count] = offsets[index];
	if (!child->isleaf) {
		child->children[child->count + 1] = sibling->children[0];
	}
	keys[index] = sibling->keys[0];
	offsets[index] = sibling->offsets[0];
	for (int i = 1; i, sibling->count; ++i) {
		sibling->keys[i - 1] = sibling->keys[i];
		sibling->offsets[i - 1] = sibling->offsets[i];
	}
	if (!sibling->isleaf) {
		for (int i = 1; i < sibling->count; ++i) {
			sibling->children[i - 1] = sibling->children[i];
		}
	}
	child->count++;
	sibling->count--;
}

void BTreeVirt::Node::merge(int index)
{
	Node* child = children[index];
	Node* sibling = children[index + 1];
	child->keys[n - 1] = keys[index];
	child->offsets[n - 1] = offsets[index];
	for (int i = 0; i < sibling->count; ++i) {
		child->keys[i + n] = sibling->keys[i];
		child->offsets[i + n] = sibling->offsets[i];
	}
	if (!child->isleaf) {
		for (int i = 0; i < sibling->count; ++i) {
			child->children[i + n] = sibling->children[i];
		}
	}
	for (int i = index + 1; i < count; ++i) {
		keys[i - 1] = keys[i];
		offsets[i - 1] = offsets[i];
	}
	for (int i = index + 2; i <= count; ++i) {
		children[i - 1] = children[i];
	}
	child->count += sibling->count + 1;
	count--;
	sibling->children = nullptr;
	delete sibling;
}

void BTreeVirt::createFromFile(fstream& b)
{
	int i = 0;
	Patient* temp = nullptr;
	do {
		temp = getRowBinary(b, i + 1);
		if (temp) {
			add(temp->card, i);
			//cout << temp->card << " " << i << "\n";
		}

		i++;
	} while (temp);
}

BTreeVirt::Node::~Node() {
	if (!isleaf) {
		if (children) {
			for (int i = 0; i < count + 1; i++) {
				if (children[i]) {
					delete children[i];
				}
			}
		}
	}
	if (children) {
		delete[] children;
	}
	
	delete[] keys;
	delete[] offsets;
	//cout << "~\n";
}

void BTreeVirt::add(int key, int offset)
{
	if (!root) {
		root = new Node(n, true);
		root->keys[0] = key;
		root->offsets[0] = offset;
		root->count = 1;
	}
	else {
		//корень полон
		if (root->count == 2 * n - 1) {
			Node* node = new Node(n, false);
			node->children[0] = root;
			node->splitChild(0, root);
			int i = 0;
			if (node->keys[0] < key) {
				i++;
			}
			node->children[i]->insertNonFull(key, offset);
			root = node;
		}
		else {
			root->insertNonFull(key, offset);
		}
	}
}

int BTreeVirt::findByKey(int key)
{
	Node* node = search(key);
	if (node) {
		for (int i = 0; i < node->count; i++) {
			if (node->keys[i] == key) {
				return node->offsets[i];
			}
		}
	}
	return -1;
}

void BTreeVirt::deleteByKeyB(int key)
{
	if (!root) {
		return;
	}
	root->remove(key);
	if (root->count == 0) {
		Node* temp = root;
		if (root->isleaf) {
			root = nullptr;
		}
		else
		{
			root = root->children[0];
			temp->children = nullptr;
			delete temp;
		}
	}
}

void BTreeVirt::test()
{
	BTreeVirt s;
	int task = 1;
	int data1, data2;
	Patient* temp;
	fstream b;
	ofstream b0;
	int next_offset = 0;
	cout << "Welcome to B-Tree test program. Choose task:";
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
			s.deleteByKeyB(data1);
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
