#pragma once
#include <iostream> // ���������� ���������� ����������� ������� �����-������
#include <fstream> //���������� ��� ������ � �������, �������� ����/�����
#include <iomanip> // ���������� ��� ������ � ��������������� ������
#include <locale> // ���������� ��� �����, ��������� � ������������
#include <Windows.h> // ���������� Windows API
#include <cstdlib>//����������, ���������� � ���� ������� �������������� �����
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
		char temp[200];
		num_people = 0;
		ifstream file("people.txt");
		while (!file.eof())
		{
			file.getline(temp, 200);
			num_people++;
		} // ������� ����� � ����� people.txt
		file.close();
		ppl = new People[num_people]; // �������� ������������� �������
		ifstream fin("people.txt");
		for (int i = 0; i < num_people; i++) // ������ ������ � ����������
		{
			fin >> ppl[i].num;
			fin >> ppl[i].name;
			fin >> ppl[i].firstname;
			fin >> ppl[i].date_hiring;
			fin >> ppl[i].date_firing;
			fin >> ppl[i].reason_firing;
			fin >> ppl[i].gratitude;
			fin >> ppl[i].experience;
		}
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

	void add_people() { // ������� ����������� ������ � ����
		system("cls");
		string name;
		string firstname;
		string date_hiring;
		string date_firing;
		string reason_firing;
		string gratitude;
		string experience;
		cout << endl;
		cout << "������� ��� ���������" << endl;
		cin >> name;
		cout << "������� �������" << endl;
		cin >> firstname;
		cout << "���� �������� �� ������" << endl;
		cin >> date_hiring;
		cout << "���� ����������" << endl;
		cin >> date_firing;
		cout << "������� ����������" << endl;
		cin >> reason_firing;
		cout << "������� ������������� �� ������" << endl;
		cin >> gratitude;
		cout << "���� ������" << endl;
		cin >> experience;
		cout << "������ ��������� �������" << endl;
		ofstream out("people.txt", ios::app);
		out << endl << num_people + 1 << " " << name << " " << firstname << " " << date_hiring << " " << date_firing << " " << reason_firing << " " << gratitude << " " << experience;
		out.close();
	};
	void del_people() { // ������� ��������� ������ �� �����
		system("cls");
		int num;
		int check = 0;

		cout << endl << "������� ����� ��������� ������:  ";
		cin >> num;
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
		if (check == 0)
			cout << endl << "������!!!" << endl;
		else
			cout << endl << "������ ������� �������!" << endl;

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
