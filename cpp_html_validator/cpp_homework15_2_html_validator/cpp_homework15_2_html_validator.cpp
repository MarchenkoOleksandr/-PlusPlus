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

	cout << "Вітаємо у програмі ""HTML-валідатор""!\n" << endl;
	string str, address, buffer;

	int found_open = 0, found_close = 0, row = 0, test = 0;
	cout << "Введіть адресу текстового (.txt) або (.html) файла у форматі \"D:\\...\\назва файла.html\": ";
	getline(cin, address);
	ifstream file(address, ios::in);
	if (file.is_open())
	{
		ifstream::streampos filesize = file.tellg();
		str.reserve(filesize);
		file.seekg(0);
		cout << "\nРезультат пошуку:" << endl;
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
				cout << "\n\nЗнайдено " << abs(found_open - found_close) << " невідповідність(ностей) у " << row << "-му абзаці!\n" << endl;
				cout << buffer << endl;
			}
			found_open = 0, found_close = 0;
		}
		cout << "\n\nПроскановано абзаців: "  << row << endl;
		if (test)
			cout << "знайдено невідповідностей: " << test;
		else
			cout << "невідповідностей не знайдено";
	}
	else
		cout << "Файл за адресою \"" << address << "\" не знайдений!!!\n\n";
	file.close();

	cout << endl << endl;
	system("pause");
}