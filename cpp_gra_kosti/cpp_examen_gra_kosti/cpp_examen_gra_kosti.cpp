//Екзаменацiйна робота Марченка Олександра
//ГРА У КОСТI

//Короткий опис: логiни i паролi зберiгаються в окремому файлi з метою запобiгання використання iменi гравця iншим гравцем
//Щоб не можна було прочитати логiни i паролi з вiдповiдного файла, данi шифруються i зберiгаються у бiнарному виглядi
//Iсторiя iгор зберiгається в окремому файлi
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>
#include <memory>
#include <time.h>
#include <windows.h>
using namespace std;

class Gamer
{
	string login;
	string password;
	short points;
public:
	Gamer() { points = 0; };
	Gamer(string l, string p);
	void Initial_gamer();
	string Get_gamers_name() { return login; };
	short Get_gamers_points() { return points; };
	void Print_results(short throws);
	void Gamer_Play();
	void CubeSymbol(int, int);
	bool load_gamer();
	void save_gamer();
	~Gamer() {};
};

Gamer::Gamer(string l, string p)
{
	login = l;
	password = p;
	points = 0;
}

void Gamer::Initial_gamer()
{
	cout << "\n\nВведіть Ваш логін: ";
	getline(cin, login);
	cout << "Введіть Ваш пароль: ";
	getline(cin, password);
	if (!login.size() || !password.size())
	{
		cout << "\nЛогін та/або пароль не можуть бути пустими! Спробуйте ще раз!!!" << endl;
		Initial_gamer();
	}
	if (load_gamer())
		cout << "\n" << login << ", вітаємо у грі!\n";
	else
		Initial_gamer();
}

void Gamer::Print_results(short throws)
{
	cout << login << " загалом має " << points << " балів. ";
	cout << "У середньому за гру на кубику випадало " << (float)points / throws / 2 << " балів." << endl;
}

void Gamer::Gamer_Play()
{
	srand((unsigned)time(NULL));
	int point1 = 0, point2 = 0;
	point1 = rand() % 6 + 1;
	point2 = rand() % 6 + 1;
	points += point1 + point2;
	cout << login << " кидає кості:\n";
	CubeSymbol(point1, point2);
}

void Gamer::CubeSymbol(int point1, int point2)
{
	switch (point1)
	{
	case 1:
		cout << " _______\n/______/|\n|      ||\n|   *  ||\n|      ||\n|______|/\t\n";
		break;
	case 2:
		cout << " _______\n/______/|\n|      ||\n|   *  ||\n|  *   ||\n|______|/\t\n";
		break;
	case 3:
		cout << " _______\n/______/|\n|    * ||\n|   *  ||\n|  *   ||\n|______|/\t\n";
		break;
	case 4:
		cout << " _______\n/______/|\n|      ||\n| *  * ||\n| *  * ||\n|______|/\t\n";
		break;
	case 5:
		cout << " _______\n/______/|\n| *  * ||\n|   *  ||\n| *  * ||\n|______|/\t\n";
		break;
	case 6:
		cout << " _______\n/______/|\n| *  * ||\n| *  * ||\n| *  * ||\n|______|/\t\n";
		break;
	}
	switch (point2)
	{
	case 1:
		cout << "\t _______\n\t/______/|\n\t|      ||\n\t|   *  ||\n\t|      ||\n\t|______|/\t\n";
		break;
	case 2:
		cout << "\t _______\n\t/______/|\n\t|      ||\n\t|   *  ||\n\t|  *   ||\n\t|______|/\t\n";
		break;
	case 3:
		cout << "\t _______\n\t/______/|\n\t|    * ||\n\t|   *  ||\n\t|  *   ||\n\t|______|/\t\n";
		break;
	case 4:
		cout << "\t _______\n\t/______/|\n\t|      ||\n\t| *  * ||\n\t| *  * ||\n\t|______|/\t\n";
		break;
	case 5:
		cout << "\t _______\n\t/______/|\n\t| *  * ||\n\t|   *  ||\n\t| *  * ||\n\t|______|/\t\n";
		break;
	case 6:
		cout << "\t _______\n\t/______/|\n\t| *  * ||\n\t| *  * ||\n\t| *  * ||\n\t|______|/\t\n";
		break;
	}
}

bool Gamer::load_gamer()
{
	if (login == "Computer")
	{
		cout << "Ви не можете використовувати iм\'я \"Computer\"";
		return false;
	}
	string temp_login, temp_password;
	ifstream file("gamers.dat", ios::in | ios::binary);
	int length = 0;
	if (file.is_open())
	{
		while (!file.eof())
		{
			file.read((char*)&length, sizeof(int));
			temp_login.resize(length);
			file.read((char*)temp_login.c_str(), length * sizeof(char));
			file.read((char*)&length, sizeof(int));
			temp_password.resize(length);
			file.read((char*)temp_password.c_str(), length * sizeof(char));

			for (int i = 0; i < temp_login.length(); i++)
				temp_login[i] += 64;
			for (int i = 0; i < temp_password.length(); i++)
				temp_password[i] += 64;

			if (!login.compare(temp_login) && !password.compare(temp_password))
			{
				file.close();
				return true;
			}
			else if (!login.compare(temp_login) && password.compare(temp_password))
			{
				file.close();
				cout << "Введений Вами пароль не вiдповiдає логiну \"" << login << "\". Спробуйте ще раз!!!" << endl;
				return false;
			}
		}
	}
	file.close();
	save_gamer();
	return true;
}

void Gamer::save_gamer()
{
	ofstream outfile("gamers.dat", ios::out | ios::app | ios::binary);
	int len = login.size();
	outfile.write((char*)&len, sizeof(len));
	for (int i = 0; i < login.length(); i++)
		login[i] -= 64;
	outfile.write(login.c_str(), login.length());
	len = password.size();
	outfile.write((char*)&len, sizeof(len));
	for (int i = 0; i < password.length(); i++)
		password[i] -= 64;
	outfile.write(password.c_str(), password.length());

	for (int i = 0; i < login.length(); i++)
		login[i] += 64;
	for (int i = 0; i < password.length(); i++)
		password[i] += 64;
	outfile.close();
}

short GetPositiveShort()
{
	cout << "\n\nДомовтеся і вкажіть число, по скільки разів ви будете кидати кості: ";
	char inputField[16] = { 0 };
	do
		gets_s(inputField, 15);
	while (!strlen(inputField));
	strncpy_s(inputField, 3, inputField, 2);
	if (atoi(inputField) <= 0)
	{
		cout << "\nПомилка вводу! Введіть число вище за нуль!";
		GetPositiveShort();
	}
	else
		return atoi(inputField);
}

void main()
{
	system("color F0");
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char choice = NULL;
	Gamer *g;
	vector<Gamer> V;
	short count_gamers = -1;

	cout << "***ГРА У КОСТI***\n";
	do
	{
		g = new Gamer();
		g->Initial_gamer();
		count_gamers++;
		V.push_back(*g);
		cout << "\n\nЯкщо Ви бажаєте додати ще одного гравця - натиснiть клавiшу \"Enter\".";
		cout << "\nЯкщо всi гравцi вже зареєстрованi - натиснiть будь-яку iншу клавiшу: ";
		choice = _getch();
	} while (choice == 13);
	if (!count_gamers)
	{
		g = new Gamer("Computer", "Computer");
		count_gamers++;
		V.push_back(*g);
		cout << "\n\n" << V[0].Get_gamers_name() << "! Сам на сам ми Вас не залишимо. Вашим супротивником буде комп\'ютер!";
	}

	cout << "\n\nОтже, вiтаємо у грi:";
	for (short i = 0; i < V.size(); i++)
		cout << "\nГравець номер " << i + 1 << ": " << V[i].Get_gamers_name();

	short throws = GetPositiveShort();
	system("cls");
	for (int j = 0; j < throws; j++)
	{
		for (short i = 0; i < V.size(); i++)
		{
			V[i].Gamer_Play();
			system("pause");
		}
		system("cls");
	}

	cout << "***СТАТИСТИКА ГРИ***\n" << endl;
	for (short i = 0; i < V.size(); i++)
		V[i].Print_results(throws);

	ofstream outfile("results.txt", ios::out | ios::app);
	outfile << "\n\nГра відбулася " << __DATE__ << " об " << __TIME__ << endl;
	outfile << "Гравці:" << endl;
	for (short i = 0; i < V.size(); i++)
		outfile << V[i].Get_gamers_name() << " - середній бал " << (float)V[i].Get_gamers_points() / throws / 2 << " з 6 можливих" << endl;
	outfile.close();
	cout << "\n\nРезультати збережені у файлі \"results.txt!\"" << endl << endl << endl;
	system("pause");
}