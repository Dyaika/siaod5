#ifndef __BTREEVIRT_H
#define __BTREEVIRT_H
#include <fstream>
#include <iostream>
#include "binary_manipulator.h"
#include "Patient.h"
class BTreeVirt
{
private:
	//��������� ����
	struct Node {
		int* keys;//�����
		int* offsets;//��������
		int n;//��� ���������� ������ � ������
		Node** children;//����� ����
		int count;//������� �������������
		bool isleaf;
		//�����������
		Node(int n, bool isleaf);
		~Node();
		void traverse();//�����
		void insertNonFull(int key, int offset);//�������������� ��� ������� ���� �� ��������
		void splitChild(int index, Node* node1);//�������������� ��� ���� �����
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
	//�������� �� ������� ������
	bool isEmpty() {
		return root == nullptr;
	}

	//�����������
	BTreeVirt(int n = 2) {
		root = nullptr;
		this->n = n;
	}

	//����������
	~BTreeVirt() {
		delete root;
	}

	//����� ������ �� �����������
	void traverse() {
		if (root) {
			root->traverse();
		}
	}
	
	//�������� ������ �� ��������� �����
	void createFromFile(fstream& b);
	
	//������� ������
	void clearTree() {
		delete root;
		root = nullptr;
	}

	//��������� ������ � ������
	void add(int key, int offset);

	//���������� �������� �� �����
	int findByKey(int key);
	
	//������� ���� �� �����
	void deleteByKeyB(int key) {
		cout << "IN DEVELOPMENT\n";
	}

	//�������� ������ ��� ������
	void printTree() {
		if (root) {
			printNodes(root);
		}
		else
		{
			cout << "empty\n";
		}
	}

	//��������� �����
	static void test();
};
#endif // !__BTREEVIRT_H



