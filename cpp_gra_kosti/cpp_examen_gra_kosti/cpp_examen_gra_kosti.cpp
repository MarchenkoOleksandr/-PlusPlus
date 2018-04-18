//���������i��� ������ �������� ����������
//��� � ����I

//�������� ����: ���i�� i �����i ����i������� � �������� ����i � ����� �����i����� ������������ i���i ������ i���� �������
//��� �� ����� ���� ��������� ���i�� i �����i � �i����i����� �����, ���i ���������� i ����i������� � �i������� ������i
//I����i� i��� ����i������ � �������� ����i
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
	cout << "\n\n������ ��� ����: ";
	getline(cin, login);
	cout << "������ ��� ������: ";
	getline(cin, password);
	if (!login.size() || !password.size())
	{
		cout << "\n���� ��/��� ������ �� ������ ���� �������! ��������� �� ���!!!" << endl;
		Initial_gamer();
	}
	if (load_gamer())
		cout << "\n" << login << ", ����� � ��!\n";
	else
		Initial_gamer();
}

void Gamer::Print_results(short throws)
{
	cout << login << " ������� �� " << points << " ����. ";
	cout << "� ���������� �� ��� �� ������ �������� " << (float)points / throws / 2 << " ����." << endl;
}

void Gamer::Gamer_Play()
{
	srand((unsigned)time(NULL));
	int point1 = 0, point2 = 0;
	point1 = rand() % 6 + 1;
	point2 = rand() % 6 + 1;
	points += point1 + point2;
	cout << login << " ���� ����:\n";
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
		cout << "�� �� ������ ��������������� i�\'� \"Computer\"";
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
				cout << "�������� ���� ������ �� �i����i�� ���i�� \"" << login << "\". ��������� �� ���!!!" << endl;
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
	cout << "\n\n��������� � ������ �����, �� ������ ���� �� ������ ������ ����: ";
	char inputField[16] = { 0 };
	do
		gets_s(inputField, 15);
	while (!strlen(inputField));
	strncpy_s(inputField, 3, inputField, 2);
	if (atoi(inputField) <= 0)
	{
		cout << "\n������� �����! ������ ����� ���� �� ����!";
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

	cout << "***��� � ����I***\n";
	do
	{
		g = new Gamer();
		g->Initial_gamer();
		count_gamers++;
		V.push_back(*g);
		cout << "\n\n���� �� ������ ������ �� ������ ������ - ������i�� ����i�� \"Enter\".";
		cout << "\n���� ��i �����i ��� �����������i - ������i�� ����-��� i��� ����i��: ";
		choice = _getch();
	} while (choice == 13);
	if (!count_gamers)
	{
		g = new Gamer("Computer", "Computer");
		count_gamers++;
		V.push_back(*g);
		cout << "\n\n" << V[0].Get_gamers_name() << "! ��� �� ��� �� ��� �� ��������. ����� ������������� ���� ����\'����!";
	}

	cout << "\n\n����, �i���� � ��i:";
	for (short i = 0; i < V.size(); i++)
		cout << "\n������� ����� " << i + 1 << ": " << V[i].Get_gamers_name();

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

	cout << "***���������� ���***\n" << endl;
	for (short i = 0; i < V.size(); i++)
		V[i].Print_results(throws);

	ofstream outfile("results.txt", ios::out | ios::app);
	outfile << "\n\n��� �������� " << __DATE__ << " �� " << __TIME__ << endl;
	outfile << "������:" << endl;
	for (short i = 0; i < V.size(); i++)
		outfile << V[i].Get_gamers_name() << " - ������� ��� " << (float)V[i].Get_gamers_points() / throws / 2 << " � 6 ��������" << endl;
	outfile.close();
	cout << "\n\n���������� �������� � ���� \"results.txt!\"" << endl << endl << endl;
	system("pause");
}