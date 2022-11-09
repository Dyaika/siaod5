#include "binary_manipulator.h"

//������� ��������� ���� �� ��������
void createTextFile(string fname, int length = 0)
{
	ofstream tout;
	if (!tout.is_open()) {
		tout.open(fname);
	}
	string doctors[5] = { "Ivanov", "Fokin", "Razshildyaev", "Archipov", "Shabalov"};
	int* seq = new int[length];
	for (int i = 0; i < length; i++) {
		seq[i] = i + 1;
	}
	int myrand;
	//�������� ��� �������
	for (int i = 0; i < length; i++) {
		myrand = rand() % (length - i);
		tout << seq[myrand] << " " << (int)rand() % 15 + 1 << " " << doctors[rand() % 5] << "\n";
		seq[myrand] = seq[length - i - 1];
	}
	delete[] seq;
	tout.clear();
	if (tout.good()) {
		tout.close();
	}
	else {
		exit(1);
	}
}

//������� �������� ���� �� ����������
void textToBinary(string fname, fstream& b)
{

	ifstream tin;
	tin.open(fname);
	b.clear();
	if (!b.is_open() or !tin.is_open()) {
		exit(2);
	}
	b.seekg(0, ios::beg);//��������� � ������
	Patient temp;
	//tin >> temp.card >> temp.illness >> temp.doctor;
	while (tin >> temp.card >> temp.illness >> temp.doctor) {
		
		b.write((char*)&temp, sizeof(Patient));
	}
	b.seekg(0, ios::beg);//������� � ������
	b.clear();
	tin.clear();
	if (b.good() and tin.good()) {
		tin.close();
	}
	else {
		exit(3);
	}
}

//������� ��������� ���� �� ���������
void binaryToText(fstream& b, string fname)
{
	ofstream tout;
	tout.open(fname);
	b.clear();
	if (!tout.is_open() or !b.is_open()) {
		exit(4);
	}
	b.seekg(0, ios::beg);//��������� � ������
	Patient temp;
	b.read((char*)&temp, sizeof(Patient));
	while (!b.eof()) {
		tout << temp.card << " " << temp.illness << " " << temp.doctor << "\n";
		b.read((char*)&temp, sizeof(Patient));
	}
	tout.clear();
	b.seekg(0, ios::beg);//������� � ������
	b.clear();
	if (tout.good() and b.good()) {
		tout.close();
	}
	else {
		exit(5);
	}
}

//�������� �� ��������� �����
void printAllBinary(fstream& b)
{
	b.clear();
	if (!b.is_open()) {
		exit(6);
	}
	b.seekg(0, ios::beg);//��������� � ������
	Patient temp;
	b.read((char*)&temp, sizeof(Patient));
	while (!b.eof()) {
		cout << temp.card << "\t" << temp.illness << "\t" << temp.doctor << "\n";
		b.read((char*)&temp, sizeof(Patient));
	}
	b.seekg(0, ios::beg);//������� � ������
	b.clear();
	if (!b.good()) {
		exit(7);
	}
}

//�������� �� ��������� ����� ���� ������ (row ��� ����� ����, � �� ������)
void printRowBinary(fstream& b, int row)
{
	Patient* temp = getRowBinary(b, row);
	if (temp) {
		cout << temp->card << " " << temp->illness << " " << temp->doctor;
	}
	else {
		cout << "no data";
	}
}

//������ � ������
Patient* getRowBinary(fstream& b, int row){
	b.clear();
	if (!b.is_open()) {
		exit(20);
	}
	Patient temp;
	bool flag = false;
	b.seekg((row - 1) * sizeof(Patient), ios::beg);
	b.read((char*)&temp, sizeof(Patient));
	if (b.eof() or row < 1) {
		flag = true;
	}
	b.seekg(0, ios::beg);//������� � ������
	b.clear();
	if (!b.good()) {
		exit(21);
	}
	if (flag) {
		return nullptr;
	}
	//��������� ���� �� ��������
	Patient *res = new Patient;
	res->card = temp.card;
	for (int i = 0; i < 16; i++) {
		res->doctor[i] = temp.doctor[i];
	}
	res->illness = temp.illness;
	return res;
}

//�������� �� ��������� ������
bool deleteByKey(fstream& b, int key)
{
	b.clear();
	if (!b.is_open()) {
		exit(10);
	}
	b.seekg(0, ios::beg);//��������� � ������
	Patient last;
	int i = 0;
	int pos = -1;
	while (b.read((char*)&last, sizeof(Patient))) {
		if (last.card == key) {
			pos = i;
		}
		i++;
	}
	if (pos == -1) {
		return false;
	}
	else {
		b.clear();
		b.seekp(pos * sizeof(Patient), ios::beg);//��������� � ����������
		b.write((char*)&last, sizeof(Patient));//�������
	}
	b.seekg(0, ios::beg);//������� � ������
	b.clear();
	if (!b.good()) {
		exit(11);
	}
	return true;
}

//�������� ������������ �������
void onlyPatientsWith(fstream& b, string fname, int illness)
{
	b.clear();
	ofstream bout;
	bout.open(fname, ios::binary);
	if (!bout.is_open() or !b.is_open()) {
		exit(14);
	}
	b.seekg(0, ios::beg);//��������� � ������
	Patient temp;
	while (b.read((char*)&temp, sizeof(Patient))) {
		if (temp.illness == illness) {
			bout.write((char*)&temp, sizeof(Patient));
		}
	}
	bout.clear();
	b.clear();
	if (bout.good() and b.good()) {
		bout.close();
	}
	else {
		exit(15);
	}
	b.seekg(0, ios::beg);//������� � ������
}

//��������� �������
void newDoctorFor(fstream& b, int* cards, int n, char doctor[16])
{
	b.clear();
	if (!b.is_open()) {
		exit(16);
	}
	b.seekg(0, ios::beg);//��������� � ������
	Patient temp;
	int count = 0;
	while (b.read((char*)&temp, sizeof(Patient)))
	{
		for (int i = 0; i < n; i++) {
			if (temp.card == cards[i]) {
				for (int j = 0; j < 16; j++) {
					temp.doctor[j] = doctor[j];
				}
				break;
			}
		}
		//������� ����� � ����������
		b.seekg(sizeof(Patient) * (count), ios::beg);
		b.write((char*)&temp, sizeof(Patient));
		//cout << temp.card << " " << temp.illness << " " << temp.doctor << " " << count << "\n";
		count++;
		b.clear();
		//������ ������ � ������ ��� �������� ����
		b.seekg(sizeof(Patient) * (count), ios::beg);
		
	}

	b.seekg(0, ios::beg);//������� � ������
	b.clear();
	if (!b.good()) {
		exit(17);
	}
}

//������������ �� ���������� ������
void testBinF()
{
	Patient* temp = nullptr;
	string str;
	cout << "Enter file name: ";
	cin >> str;
	int* arr;
	int data;
	cout << "How much notes? ";
	cin >> data;
	createTextFile(str + ".txt", data);
	int task = 1;
	//������� �������� ����
	ofstream b0;
	b0.open(str + "_bin.dat", ios::binary);
	b0.close();
	//��������� ��� ��� ������/������
	fstream b, btemp;
	b.open(str + "_bin.dat", ios::binary | ios::out | ios::in);
	cout << "File " << str << ".txt was created and filled with random notes. Empty file " << str << "_bin.dat was created.";
	while (task > 0 and task < 8) {
		cout << "Choose task:\n1) To binary\n2) To text\n3) Print from binary file\n4) Print row\n5) Delete by key\n6) Create new file with only illness\n7) New doctor to\n> ";
		cin >> task;
		switch (task)
		{
		case 1:
			textToBinary(str + ".txt", b);
			cout << "Binary file is " << str << "_bin.dat\n";
			cout << "---completed---\n\n";
			break;
		case 2:
			binaryToText(b, str + "_text.txt");
			cout << "Text file is " << str << "_text.txt\n";
			cout << "---completet---\n\n";
			break;
		case 3:
			printAllBinary(b);
			cout << "---completed---\n\n";
			break;
		case 4:
			cout << "Row = ";
			cin >> data;
			cout << "Row " << data << ": ";
			temp = getRowBinary(b, data);
			if (temp) {
				cout << temp->card << " " << temp->illness << " " << temp->doctor;
			}
			else {
				cout << "no data";
			}
			cout << "\n---completed---\n\n";
			break;
		case 5:
			cout << "Key to delete = ";
			cin >> data;
			if (deleteByKey(b, data)) {
				cout << "removed";
			}
			else {
				cout << "not found";
			}
			cout << "\n---completed---\n\n";
			break;
		case 6:
			cout << "Illness = ";
			cin >> data;
			onlyPatientsWith(b, str + "_" + to_string(data) + ".dat", data);
			cout << str << "_" << data << ".dat:\n";
			btemp.open(str + "_" + to_string(data) + ".dat", ios::binary | ios::out | ios::in);
			printAllBinary(btemp);
			btemp.close();
			cout << "---completed---\n\n";
			break;
		case 7:
			cout << "How much patients? ";
			cin >> data;
			arr = new int[data];
			for (int i = 0; i < data; i++) {
				cout << i + 1 << ") ";
				cin >> arr[i];
			}
			cout << "Who is new doctor? ";
			char doc[16];
			cin >> doc;
			newDoctorFor(b, arr, data, doc);
			cout << "---completed---\n\n";
			delete[] arr;
			break;
		default:
			break;
		}
	}
	b.close();
	cout << "---exit---\n";
}

