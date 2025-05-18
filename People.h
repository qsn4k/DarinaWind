#pragma once
#include <iostream> // библиотека содержащая стандартные функции ввода-вывода
#include <fstream> //библиотека для работы с файлами, поточный ввод/вывод
#include <iomanip> // библиотека для работы с форматированием вывода
#include <locale> // библиотека для задач, связанных с локализацией
#include <Windows.h> // библиотека Windows API
#include <cstdlib>//библиотека, содержащая в себе функции преобразования типов
using namespace std; //подключение стандартного пространства имен

class People //создание переменных-полей, в которых будут хранится данные о работниках организации
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
	class People* ppl;//создание массива из переменных класса People
	void line() // функция для оформления вывода
	{
		const char* line = "______________________________________";
		cout << line << line << line << endl << line << line << line;
	};
	void load() { // функция чтения данных из файла 
		char temp[200];
		num_people = 0;
		ifstream file("people.txt");
		while (!file.eof())
		{
			file.getline(temp, 200);
			num_people++;
		} // подсчет строк в файле people.txt
		file.close();
		ppl = new People[num_people]; // создание динамического массива
		ifstream fin("people.txt");
		for (int i = 0; i < num_people; i++) // запись данных в переменные
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
	void show() { // функция выводящая данные на экран консоли

		system("cls");
		line();
		cout << endl;
		cout << setw(7) << "Номер" << setw(10) << "Имя" << setw(15) << "Фамилия" << setw(15) << "Принятие" << setw(15) << "Увольнение" << setw(19) << "Причина" << setw(19) << "Благодарность" << setw(9) << "Стаж" << endl << endl;
		for (int i = 0; i < num_people; i++)
		{
			cout << setw(7) << ppl[i].num << setw(10) << ppl[i].name << setw(15) << ppl[i].firstname << setw(15) << ppl[i].date_hiring << setw(15) << ppl[i].date_firing << setw(19) << ppl[i].reason_firing << setw(18) << ppl[i].gratitude << setw(10) << ppl[i].experience << endl << endl;
		}
	};
	void sort_by(int a) { // функция сортировки

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
	void sort(int i) { // тело сортировки
		/*из-за того, что сам процесс сортировки пузырьком не отличается в зависимости от поля, по которому сортируют, то было принято решение вынести алгоритм сортировки, тем самым оптимизируя код*/
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

	void add_people() { // функция добавляющая запись в файл
		system("cls");
		string name;
		string firstname;
		string date_hiring;
		string date_firing;
		string reason_firing;
		string gratitude;
		string experience;
		cout << endl;
		cout << "Введите имя работника" << endl;
		cin >> name;
		cout << "Введите фамилию" << endl;
		cin >> firstname;
		cout << "Дата принятия на работу" << endl;
		cin >> date_hiring;
		cout << "Дата увольнения" << endl;
		cin >> date_firing;
		cout << "Причина увольнения" << endl;
		cin >> reason_firing;
		cout << "Наличие благодарности за работу" << endl;
		cin >> gratitude;
		cout << "Стаж работы" << endl;
		cin >> experience;
		cout << "Запись добавлена успешно" << endl;
		ofstream out("people.txt", ios::app);
		out << endl << num_people + 1 << " " << name << " " << firstname << " " << date_hiring << " " << date_firing << " " << reason_firing << " " << gratitude << " " << experience;
		out.close();
	};
	void del_people() { // функция удаляющая запись из файла
		system("cls");
		int num;
		int check = 0;

		cout << endl << "Введите номер удаляемой записи:  ";
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
			cout << endl << "Ошибка!!!" << endl;
		else
			cout << endl << "Запись удалена успешно!" << endl;

		out.close();

	};
	void calcul() { // функция вычисляющая сколько месяцев работник проработал в организации
		system("cls");
		char date1[11], date2[11];
		int mass[11], mass2[11];
		line();
		cout << endl << setw(7) << "Номер" << setw(10) << "Имя" << setw(15) << "Фамилия" << setw(30) << "Срок работы в организации" << endl << endl;
		for (int i = 0; i < num_people; i++)
		{
			strcpy_s(date1, ppl[i].date_hiring.c_str()); // перепись данных формата строка в формат массив символов
			strcpy_s(date2, ppl[i].date_firing.c_str());
			for (int j = 0; j < 11; j++) // преобразование данных типа char к типу данных int
			{
				mass[j] = date1[j];
				mass[j] = mass[j] - 48;
				mass2[j] = date2[j];
				mass2[j] = mass2[j] - 48;
			}
			int time = 0;
			time = (((mass2[0] * 1000 + mass2[2] * 10 + mass2[3]) - (mass[0] * 1000 + mass[2] * 10 + mass[3])) * 12) + ((mass2[5] * 10 + mass2[6]) - (mass[5] * 10 + mass[6])); // расчет количества месяцев
			cout << setw(7) << ppl[i].num << setw(10) << ppl[i].name << setw(15) << ppl[i].firstname << setw(10) << time << " месяцев" << endl << endl;
		}

	};
};
