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
	//��������� ���� ��� ������ ������
	struct Node
	{
		int key = 0;
		int offset = 0;
		Node* leftTree = nullptr, * rightTree = nullptr;
		~Node();
	};
public:

	//�����������
	SearchTree(int n = 0);

	//���������
	~SearchTree();

	//��������� �� ���������� ������
	bool isEmpty() {
		if (root) {
			return false;
		}
		return true;
	}

	//������� ������ �� ��������� �����
	void createFromFile(fstream& b);

	//������� ������
	void clearTree();

	//��������� ������� � ������
	void add(int key, int offset);

	//������� �������� �� �����
	int findByKey(int key);

	//������� ���� �� �����
	void deleteByKeyS(int key);

	//�������� ������
	void printTree();

	//��������� �����
	static void test();
private:
	//���� �����
	Node* root = nullptr;

	//��������� ����
	Node* addNode(int key, int offset, Node* root);
	//���� ���� �� �����
	int findNode(int key, Node* root);
	//������� ���� �� �����
	Node* deleteNode(int key, Node* root);
	//�������� ����
	void printNodes(Node* root, int tab_count = 0, int tab_size = 8);
};

#endif // !__TREES_H



