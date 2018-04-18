#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;

#define MAXSTUDENTS 128
#define MAXGROUPS 32

class Student
{
	unsigned short studentID;
	char surname[32];
	char name[16];
	char phoneNumber[16];
	unsigned short group;

public:
	void AddStudent();
	void ShowAllStudents();
	void ChangeGroupByStudent();
	void DeleteStudent();

	Student();
	~Student();
} studentNumber[MAXSTUDENTS];

Student::Student()
{
	studentID = 0;
	surname[0] = { 0 };
	name[0] = { 0 };
	phoneNumber[0] = { 0 };
	group = 0;
}

Student::~Student()
{
	studentID = 0;
	surname[0] = { 0 };
	name[0] = { 0 };
	phoneNumber[0] = { 0 };
	group = 0;
}

class Group
{
	unsigned short groupID;
	char groupName[9];

public:
	void AddGroup();
	void ShowAllGroups();
	void DeleteGroup();
	static void GroupIDdecoding(unsigned short i);

	Group();
	~Group();
} groupNumber[MAXGROUPS];

Group::Group()
{
	groupID = 0;
	groupName[0] = { 0 };
}

Group::~Group()
{
	groupID = 0;
	groupName[0] = { 0 };
}

int GetCorrectNumber();
int GetPositiveNumber();

char choice = ' ';
char inputField[64] = { 0 };

void main()
{
	system("color F0");
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Вітаємо!\nЦя програма описує студентів і групи за допомогою класів!" << endl;
	do
	{
		cout << "\n\nОберіть необхідне число (варіант відповіді):" << endl;
		cout << "1 - додати групу" << endl;
		cout << "2 - показати всі групи" << endl;
		cout << "3 - видалити групу" << endl;
		cout << "4 - додати студента" << endl;
		cout << "5 - показати список студентів" << endl;
		cout << "6 - перевести студента до іншої групи" << endl;
		cout << "7 - видалити студента" << endl;
		cout << "0 - закрити программу\n" << endl;
		choice = _getch();
		system("cls");
		switch (choice)
		{
		case '1': groupNumber[0].AddGroup();
			break;
		case '2': groupNumber[0].ShowAllGroups();
			break;
		case '3': groupNumber[0].DeleteGroup();
			break;
		case '4': studentNumber[0].AddStudent();
			break;
		case '5': studentNumber[0].ShowAllStudents();
			break;
		case '6': studentNumber[0].ChangeGroupByStudent();
			break;
		case '7': studentNumber[0].DeleteStudent();
			break;
		case '0':
			break;
		default:
			cout << "Вибір невірний! Потрібно ввести число від 0 до 7!";
			break;
		}
	} while (choice != '0');
}

void Group::AddGroup()
{
	if (groupID == MAXGROUPS)
	{
		cout << "Настав час збільшити місце для зберігання груп!";
		return;
	}
	groupID++;
	cout << "Введіть назву нової групи: ";
	do
		gets_s(inputField, 63);
	while (!strlen(inputField));
	strncpy_s(groupNumber[groupID].groupName, 9, inputField, 8);
	_strupr(groupNumber[groupID].groupName);
	groupNumber[groupID].groupID = groupID;
	cout << "Додана нова група \"" << groupNumber[groupID].groupName << "\" з ID " << groupNumber[groupID].groupID << endl;
}

void Group::ShowAllGroups()
{
	if (!groupID)
	{
		cout << "Ви ще не додали жодної групи!";
		return;
	}
	cout << "Перелік груп:" << endl;
	cout << "ID \t Назва групи" << endl;
	cout << "--------------------" << endl;
	for (int i = 1; i <= groupID; i++)
	{
		if (!groupNumber[i].groupID)
			continue;
		cout << groupNumber[i].groupID << " \t " << groupNumber[i].groupName << endl;
	}
}

void Group::DeleteGroup()
{
	if (!groupID)
	{
		cout << "Ви ще не додали жодної групи!";
		return;
	}
	unsigned short temp = 0;
	cout << "Введіть ID групи, яку хочете видалити (від 1 до " << groupID << ") або введіть нуль, щоб подивитись список груп: ";
	temp = GetCorrectNumber();
	if (!temp)
		groupNumber[0].ShowAllGroups();
	else if (temp > groupID)
	{
		cout << "Помилка! Номер групи має бути від 1 до " << groupID << ": " << endl;
		Group::DeleteGroup();
	}
	else
	{
		cout << "\nГрупа \"" << groupNumber[temp].groupName << "\" з ID " << temp << " видалена!" << endl;
		groupNumber[temp].groupName[0] = { 0 };
		groupNumber[temp].groupID = 0;
	}
}

void Group::GroupIDdecoding(unsigned short i)
{
	if (!strlen(groupNumber[i].groupName))
		cout << "\"група з ID " << i << " не створена\"" << endl;
	else
		cout << "\"" << groupNumber[i].groupName << "\"" << endl;
	
}

void Student::AddStudent()
{
	if (studentID == MAXSTUDENTS)
	{
		cout << "Настав час збільшити місце для зберігання студентів!";
		return;
	}
	studentID++;
	cout << "Введіть прізвище нового студента: ";
	do
		gets_s(inputField, 63);
	while (!strlen(inputField));
	strncpy_s(studentNumber[studentID].surname, 31, inputField, 30);
	cout << "Введіть ім\'я нового студента: ";
	do
		gets_s(inputField, 63);
	while (!strlen(inputField));
	strncpy_s(studentNumber[studentID].name, 16, inputField, 15);
	cout << "Введіть номер телефону нового студента (лише цифри): ";
	do
		gets_s(inputField, 63);
	while (!strlen(inputField));
	strncpy_s(studentNumber[studentID].phoneNumber, 16, inputField, 15);
	short temp = 0;
	cout << "Введіть ID групи нового студента або введіть нуль, щоб подивитись перелік груп: ";
	temp = GetCorrectNumber();
	if (!temp)
	{
		cout << endl;
		groupNumber[0].ShowAllGroups();
		cout << "\nВведіть ID групи нового студента: ";
		temp = GetPositiveNumber();
	}
	studentNumber[studentID].group = temp;
	studentNumber[studentID].studentID = studentID;
	cout << "Доданий новий студент \"" << studentNumber[studentID].surname << "\" з ID " << studentNumber[studentID].studentID << endl;
}

void Student::ShowAllStudents()
{
	if (!studentID)
	{
		cout << "Ви ще не додали жодного студента!";
		return;
	}
	cout << "Перелік студентів:" << endl;
	printf("ID    %-32s  %-16s  %-16s  %-9s\n", "прізвище", "ім\'я", "телефон", "група");
	cout << "-----------------------------------------------------------------------------------" << endl;
	for (int i = 1; i <= studentID; i++)
	{
		if (!studentNumber[i].studentID)
			continue;
		printf("%-3i   %-32s  %-16s  %-16s  ", studentNumber[i].studentID, studentNumber[i].surname, \
			studentNumber[i].name, studentNumber[i].phoneNumber);
			Group::GroupIDdecoding(studentNumber[i].group);
	}
}

void Student::ChangeGroupByStudent()
{
	short temp = 0;
	cout << "Введіть ID студента, якого бажаєте перевести до іншої групи або введіть нуль, щоб подивитись список студентів: ";
	temp = GetCorrectNumber();
	if (!temp)
	{
		cout << endl;
		studentNumber[0].ShowAllStudents();
		cout << endl;
		Student::ChangeGroupByStudent();
	}
	else if (temp > studentID)
	{
		cout << endl;
		cout << "Помилка! Такий студент відсутній у списку. Номер ID має бути від 1 до " << studentID << ": " << endl;
		Student::ChangeGroupByStudent();
	}
	else
	{
		cout << "Введіть ID групи, до якої потрібно перевести \"" << studentNumber[temp].surname << "\": ";
		studentNumber[temp].group = GetPositiveNumber();
		cout << "\"" << studentNumber[temp].surname << "\" переведений до групи ";
			Group::GroupIDdecoding(studentNumber[temp].group);
	}
}

void Student::DeleteStudent()
{
	if (!studentID)
	{
		cout << "Ви ще не додали жодного студента!";
		return;
	}
	unsigned short temp = 0;
	cout << "Введіть ID студента, якого хочете видалити (від 1 до " << studentID << ") або введіть нуль, щоб подивитись список студентів: ";
	temp = GetCorrectNumber();
	if (!temp)
		studentNumber[0].ShowAllStudents();
	else if (temp > studentID)
	{
		cout << "Помилка! Такий студент відсутній у списку. Номер ID має бути від 1 до " << studentID << ": " << endl;
		Student::DeleteStudent();
	}
	else
	{
		cout << "Студент \"" << studentNumber[temp].surname << "\" з ID " << temp << " видалений!" << endl;
		studentNumber[temp].studentID = 0;
		studentNumber[temp].surname[0] = { 0 };
		studentNumber[temp].name[0] = { 0 };
		studentNumber[temp].phoneNumber[0] = { 0 };
		studentNumber[temp].group = 0;
	}
}

int GetCorrectNumber()
{
	do
		gets_s(inputField, 63);
	while (!strlen(inputField));
	strncpy_s(inputField, 4, inputField, 3);
	if (atoi(inputField) < 0)
	{
		cout << "\nПомилка вводу даних! Введіть число ще раз: ";
		GetCorrectNumber();
	}
	return atoi(inputField);
}

int GetPositiveNumber()
{
	do
		gets_s(inputField, 63);
	while (!strlen(inputField));
	strncpy_s(inputField, 4, inputField, 3);
	if (atoi(inputField) <= 0)
	{
		cout << "\nПомилка вводу даних! Введіть число вище за нуль: ";
		GetPositiveNumber();
	}
	return atoi(inputField);
}