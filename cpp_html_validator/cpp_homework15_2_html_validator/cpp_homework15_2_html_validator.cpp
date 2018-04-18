#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
using namespace std;

void main()
{
	system("color F0");
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "³���� � ������� ""HTML-��������""!\n" << endl;
	string str, address, buffer;

	int found_open = 0, found_close = 0, row = 0, test = 0;
	cout << "������ ������ ���������� (.txt) ��� (.html) ����� � ������ \"D:\\...\\����� �����.html\": ";
	getline(cin, address);
	ifstream file(address, ios::in);
	if (file.is_open())
	{
		ifstream::streampos filesize = file.tellg();
		str.reserve(filesize);
		file.seekg(0);
		cout << "\n��������� ������:" << endl;
		while (getline(file, buffer))
		{
			row++;
			for (auto i = buffer.begin(); i != buffer.end(); ++i)
			{
				if (*i == '<')
					found_open++;
				else if (*i == '>')
					found_close++;
			}
			if (found_open != found_close)
			{
				test += abs(found_open - found_close);
				cout << "\n\n�������� " << abs(found_open - found_close) << " ������������(������) � " << row << "-�� ������!\n" << endl;
				cout << buffer << endl;
			}
			found_open = 0, found_close = 0;
		}
		cout << "\n\n������������ �������: "  << row << endl;
		if (test)
			cout << "�������� ��������������: " << test;
		else
			cout << "�������������� �� ��������";
	}
	else
		cout << "���� �� ������� \"" << address << "\" �� ���������!!!\n\n";
	file.close();

	cout << endl << endl;
	system("pause");
}