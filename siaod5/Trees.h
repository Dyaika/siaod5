//Trees.h
#ifndef __BTREE_H
#define __BTREE_H
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
	SearchTree(int n = 0);
	~SearchTree();
	bool isEmpty() {
		if (root) {
			return false;
		}
		return true;
	}
	void createFromFile(fstream& b);
	void clearTree();
	void add(int key, int offset);
	int findByKey(int key);
	void deleteByKeyS(int key);
	void printTree();
	static void test();
private:
	//поле корня
	Node* root = nullptr;
	//поле количества ячеек
	//int size = 0;

	//добавляет узел
	Node* addNode(int key, int offset, Node* root);
	//ищет узел по ключу
	int findNode(int key, Node* root);
	//удаляет узел по улючу
	Node* deleteNode(int key, Node* root);
	//печатает узлы
	void printNodes(Node* root, int tab_count = 0, int tab_size = 8);
};

class BTree
{
public:
	//BTree();
	//~BTree();

private:
	struct Node
	{
		int key = 0;
		int offset = 0;

	};
};
#endif // !__BTREE_H



