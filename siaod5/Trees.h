//Trees.h
#ifndef __TREES_H
#define __TREES_H
#include <fstream>
#include <iostream>
#include "binary_manipulator.h"
#include "Patient.h"
using namespace std;

class SearchTree
{
private:
	//структура узла для дерева поиска
	struct Node
	{
		int key = 0;
		int offset = 0;
		Node* leftTree = nullptr, * rightTree = nullptr;
		~Node();
	};
public:

	//конструктор
	SearchTree(int n = 0);

	//деструтор
	~SearchTree();

	//проверяет на отсутствие дерева
	bool isEmpty() {
		if (root) {
			return false;
		}
		return true;
	}

	//создает дерево по бинарному файлу
	void createFromFile(fstream& b);

	//удаляет дерево
	void clearTree();

	//добавляет элемент в дерево
	void add(int key, int offset);

	//находит смещение по ключу
	int findByKey(int key);

	//удаляет узел по ключу
	void deleteByKeyS(int key);

	//печатает дерево
	void printTree();

	//программа теста
	static void test();
private:
	//поле корня
	Node* root = nullptr;

	//добавляет узел
	Node* addNode(int key, int offset, Node* root);
	//ищет узел по ключу
	int findNode(int key, Node* root);
	//удаляет узел по улючу
	Node* deleteNode(int key, Node* root);
	//печатает узлы
	void printNodes(Node* root, int tab_count = 0, int tab_size = 8);
};

#endif // !__TREES_H



