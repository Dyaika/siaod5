#ifndef __BTREEVIRT_H
#define __BTREEVIRT_H
#include <fstream>
#include <iostream>
#include "binary_manipulator.h"
#include "Patient.h"
class BTreeVirt
{
private:
	//структура узла
	struct Node {
		int* keys;//ключи
		int* offsets;//смещени€
		int n;//мин количество ключей в записи
		Node** children;//ветки вниз
		int count;//текущ€€ заполненность
		bool isleaf;
		//конструктор
		Node(int n, bool isleaf);
		~Node();
		void traverse();//обход
		void insertNonFull(int key, int offset);//предполагаетс€ что текущий узел не заполнен
		void splitChild(int index, Node* node1);//предполагаетс€ что узел полон
		Node* search(int key);

	};

	Node* root;
	int n;

	Node* search(int key) {
		if (root) {
			return root->search(key);
		}
		return nullptr;
	}
	void printNodes(Node* root, int tab_count = 0, int tab_size = 8);
public:
	//проверка на пустоту дерева
	bool isEmpty() {
		return root == nullptr;
	}

	//конструктор
	BTreeVirt(int n = 2) {
		root = nullptr;
		this->n = n;
	}

	//деструктор
	~BTreeVirt() {
		delete root;
	}

	//обход дерева по возрастанию
	void traverse() {
		if (root) {
			root->traverse();
		}
	}
	
	//создание дерева по бинарному файлу
	void createFromFile(fstream& b);
	
	//удал€ет дерево
	void clearTree() {
		delete root;
		root = nullptr;
	}

	//добавл€ет корень в дерево
	void add(int key, int offset);

	//возвращает смещение по ключу
	int findByKey(int key);
	
	//удал€ет узел по ключу
	void deleteByKeyB(int key) {
		cout << "IN DEVELOPMENT\n";
	}

	//печатает дерево как дерево
	void printTree() {
		if (root) {
			printNodes(root);
		}
		else
		{
			cout << "empty\n";
		}
	}

	//программа теста
	static void test();
};
#endif // !__BTREEVIRT_H



