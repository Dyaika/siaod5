#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "Patient.h"

using namespace std;

//создает текстовый файл со строками
void createTextFile(string fname, int length);

//создает бинарный файл по текстовому
void textToBinary(string fname, fstream& b);

//создает текстовый файл по бинарному
void binaryToText(fstream& b, string fname);

//печатает из бинарного файла
void printAllBinary(fstream& b);

//печатает 1 ряд
void printRowBinary(fstream& b, int row);

//доступ к записи
Patient* getRowBinary(fstream& b, int row);

//удаляет запись
bool deleteByKey(fstream& b, int key);

//создает файл только с 1 заболеванием
void onlyPatientsWith(fstream& b, string fname, int illness);

//добавляет ряд в конец
void addRow(fstream& b, Patient* p);

//меняет доктора
void newDoctorFor(fstream& b, int* cards, int n, char doctor[16]);

//тестирует
void testBinF();
