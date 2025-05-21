#pragma once
#include <iostream> // ���������� ���������� ����������� ������� �����-������
#include <fstream> //���������� ��� ������ � �������, �������� ����/�����
#include <iomanip> // ���������� ��� ������ � ��������������� ������
#include <locale> // ���������� ��� �����, ��������� � ������������
#include <Windows.h> // ���������� Windows API
#include <cstdlib>//����������, ���������� � ���� ������� �������������� �����
#include <string>
using namespace std; //����������� ������������ ������������ ����


class People //�������� ����������-�����, � ������� ����� �������� ������ � ���������� �����������
{
public:
	int num;
	string name;
	string firstname;
	string date_hiring;
	string date_firing;
	string reason_firing;
	string gratitude;
	string experience;
};
class Organisation
{
public:
	int num_people;
	class People* ppl;//�������� ������� �� ���������� ������ People
	void line() // ������� ��� ���������� ������
	{
		const char* line = "______________________________________";
		cout << line << line << line << endl << line << line << line;
	};
	void load() { // ������� ������ ������ �� ����� 
		// ������ ������: ������� �����
		num_people = 0;
		ifstream file("people.txt");
		if (!file.is_open()) {
			cerr << "������ �������� ����� people.txt" << endl;
			return;
		}

		string line;
		while (getline(file, line)) {
			if (!line.empty()) {  // ���������� ������ ������
				num_people++;
			}
		}
		file.close();

		// ������ ������: ������ ������
		ppl = new People[num_people];
		ifstream fin("people.txt");
		if (!fin.is_open()) {
			cerr << "������ �������� ����� people.txt" << endl;
			delete[] ppl;  // ����������� ������ � ������ ������
			ppl = nullptr;
			num_people = 0;
			return;
		}

		for (int i = 0; i < num_people; i++) {
			// ���������, �������� �� ����� �����
			if (fin.eof()) {
				cerr << "������: ���� �������� ������ �������, ��� ���������" << endl;
				break;
			}

			fin >> ppl[i].num
				>> ppl[i].name
				>> ppl[i].firstname
				>> ppl[i].date_hiring
				>> ppl[i].date_firing
				>> ppl[i].reason_firing
				>> ppl[i].gratitude
				>> ppl[i].experience;

			// ���������� ���������� ����� ������ (���� ����)
			fin.ignore();
		}
		fin.close();
	};
	void show() { // ������� ��������� ������ �� ����� �������

		system("cls");
		line();
		cout << endl;
		cout << setw(7) << "�����" << setw(10) << "���" << setw(15) << "�������" << setw(15) << "��������" << setw(15) << "����������" << setw(19) << "�������" << setw(19) << "�������������" << setw(9) << "����" << endl << endl;
		for (int i = 0; i < num_people; i++)
		{
			cout << setw(7) << ppl[i].num << setw(10) << ppl[i].name << setw(15) << ppl[i].firstname << setw(15) << ppl[i].date_hiring << setw(15) << ppl[i].date_firing << setw(19) << ppl[i].reason_firing << setw(18) << ppl[i].gratitude << setw(10) << ppl[i].experience << endl << endl;
		}
	};
	void sort_by(int a) { // ������� ����������

		for (int j = 0; j < num_people; j++)
		{
			for (int i = 0; i < num_people - 1; i++)
			{
				switch (a)
				{
				case 2:
					if (ppl[i].firstname > ppl[i + 1].firstname)
						sort(i);
					break;
				case 1:
					if (ppl[i].name > ppl[i + 1].name)
						sort(i);
					break;
				case 3:
					if (ppl[i].date_hiring > ppl[i + 1].date_hiring)
						sort(i);
					break;
				case 4:
					if (ppl[i].date_firing > ppl[i + 1].date_firing)
						sort(i);
					break;
				case 5:
					if (ppl[i].experience > ppl[i + 1].experience)
						sort(i);
					break;
				}
			}
		}
		show();
	};
	void sort(int i) { // ���� ����������
		/*��-�� ����, ��� ��� ������� ���������� ��������� �� ���������� � ����������� �� ����, �� �������� ���������, �� ���� ������� ������� ������� �������� ����������, ��� ����� ����������� ���*/
		string temp;
		int itemp;
		itemp = ppl[i].num;
		ppl[i].num = ppl[i + 1].num;
		ppl[i + 1].num = itemp;

		temp = ppl[i].firstname;
		ppl[i].firstname = ppl[i + 1].firstname;
		ppl[i + 1].firstname = temp;

		temp = ppl[i].name;
		ppl[i].name = ppl[i + 1].name;
		ppl[i + 1].name = temp;

		temp = ppl[i].date_firing;
		ppl[i].date_firing = ppl[i + 1].date_firing;
		ppl[i + 1].date_firing = temp;

		temp = ppl[i].date_hiring;
		ppl[i].date_hiring = ppl[i + 1].date_hiring;
		ppl[i + 1].date_hiring = temp;

		temp = ppl[i].reason_firing;
		ppl[i].reason_firing = ppl[i + 1].reason_firing;
		ppl[i + 1].reason_firing = temp;

		temp = ppl[i].gratitude;
		ppl[i].gratitude = ppl[i + 1].gratitude;
		ppl[i + 1].gratitude = temp;

		temp = ppl[i].experience;
		ppl[i].experience = ppl[i + 1].experience;
		ppl[i + 1].experience = temp;
	};

	void add_people(string name,
	string firstname,
	string date_hiring,
	string date_firing,
	string reason_firing,
	string gratitude,
	string experience)
	{ // ������� ����������� ������ � ����
		system("cls");
		ofstream out("people.txt", ios::app);
		out << endl << num_people + 1 << " " << name << " " << firstname << " " << date_hiring << " " << date_firing << " " << reason_firing << " " << gratitude << " " << experience;
		out.close();
	};
	

	void del_people(int num) { // ������� ��������� ������ �� �����
		system("cls");
		
		int check = 0;
		ofstream out("people.txt");
		for (int i = 0; i < num_people; i++)
			if (ppl[i].num != num)
			{
				out << ppl[i].num << " " << ppl[i].name << " " << ppl[i].firstname << " " << ppl[i].date_hiring << " " << ppl[i].date_firing << " " << ppl[i].reason_firing << " " << ppl[i].gratitude << " " << ppl[i].experience;

				if ((i == num_people - 1) || ((ppl[i + 1].num == num) && (i == num_people - 2)))
					continue;
				out << endl;
			}
			else
				check = 1;

		out.close();

	};
	void calcul() { // ������� ����������� ������� ������� �������� ���������� � �����������
		system("cls");
		char date1[11], date2[11];
		int mass[11], mass2[11];
		line();
		cout << endl << setw(7) << "�����" << setw(10) << "���" << setw(15) << "�������" << setw(30) << "���� ������ � �����������" << endl << endl;
		for (int i = 0; i < num_people; i++)
		{
			strcpy_s(date1, ppl[i].date_hiring.c_str()); // �������� ������ ������� ������ � ������ ������ ��������
			strcpy_s(date2, ppl[i].date_firing.c_str());
			for (int j = 0; j < 11; j++) // �������������� ������ ���� char � ���� ������ int
			{
				mass[j] = date1[j];
				mass[j] = mass[j] - 48;
				mass2[j] = date2[j];
				mass2[j] = mass2[j] - 48;
			}
			int time = 0;
			time = (((mass2[0] * 1000 + mass2[2] * 10 + mass2[3]) - (mass[0] * 1000 + mass[2] * 10 + mass[3])) * 12) + ((mass2[5] * 10 + mass2[6]) - (mass[5] * 10 + mass[6])); // ������ ���������� �������
			cout << setw(7) << ppl[i].num << setw(10) << ppl[i].name << setw(15) << ppl[i].firstname << setw(10) << time << " �������" << endl << endl;
		}

	};
};
