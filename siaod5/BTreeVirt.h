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

		//дл€ получени€ всех данных из функций
		struct nodeData {
			int key = 0;
			int offset = 0;
		};

		Node(int n, bool isleaf);//конструктор
		~Node();//деструктор
		void traverse();//обход
		void insertNonFull(int key, int offset);//предполагаетс€ что текущий узел не заполнен
		void splitChild(int index, Node* node1);//предполагаетс€ что узел полон
		Node* search(int key);//возвращает указатель на узел
		int findIndex(int key);//возвращает индекс первого элемента больше или равного key
		void remove(int key);//удал€ет нужный ключ
		void removeFromLeaf(int index);//удаление если лист
		void removeFromNonLeaf(int index);//удаление если не лист
		nodeData getPred(int index);//получаем предшественника ключа где он присутствует на опр. позиции
		nodeData getSucc(int index);//получаем наследника ключа где он присутствует на опр. позиции
		void fill(int index);//заполн€ет дит€ на опр. позиции если у него меньше n-1 значений
		void borrowFromPrev(int index);//перетаскивает ключ из предыдущего ребенка в определенного
		void borrowFromNext(int index);//перетаскивает ключ из следующего ребенка в определенного
		void merge(int index);//совмещает определенного ребенка с следующим
	};

	//поле корн€
	Node* root;

	//дл€ определени€ количества элементов в узле (2*n-1 ключей, 2*n детей)
	int n;
	
	//вернет указатель на узел, содержащий этот ключ
	Node* search(int key) {
		if (root) {
			return root->search(key);
		}
		return nullptr;
	}

	//печатает узлы
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
	void deleteByKeyB(int key);

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



