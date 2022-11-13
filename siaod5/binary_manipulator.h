#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "Patient.h"

using namespace std;

//������� ��������� ���� �� ��������
void createTextFile(string fname, int length);

//������� �������� ���� �� ����������
void textToBinary(string fname, fstream& b);

//������� ��������� ���� �� ���������
void binaryToText(fstream& b, string fname);

//�������� �� ��������� �����
void printAllBinary(fstream& b);

//�������� 1 ���
void printRowBinary(fstream& b, int row);

//������ � ������
Patient* getRowBinary(fstream& b, int row);

//������� ������
bool deleteByKey(fstream& b, int key);

//������� ���� ������ � 1 ������������
void onlyPatientsWith(fstream& b, string fname, int illness);

//��������� ��� � �����
void addRow(fstream& b, Patient* p);

//������ �������
void newDoctorFor(fstream& b, int* cards, int n, char doctor[16]);

//���������
void testBinF();
