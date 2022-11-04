// siaod5.cpp

#include "Trees.h"
#include <iostream>
#include "Windows.h"
#include "binary_manipulator.h"
using namespace std;
class MyApp
{
public:
	MyApp();
};
int main()
{
	MyApp a;
}




MyApp::MyApp()
{
	cout << "Welcome to test program.\n";
	int task = 1;
	while (task < 4 and task > 0)
	{
		cout << "1) Test binary sort tree\n2) Test B-tree\n3) Test binary manipulations\n> ";
		cin >> task;
		switch (task)
		{
		case 1:
			system("cls");
			SearchTree::test();
			system("cls");
			break;
		case 2:
			system("cls");
			cout << "IN DEVELOPMENT\n";
			break;
		case 3:
			system("cls");
			testBinF();
			system("cls");
			break;
		default:
			break;
		}
	}
	cout << "---exit---\n";
}
