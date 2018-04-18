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
	cout << "³����!\n�� �������� ����� �������� � ����� �� ��������� �����!" << endl;
	do
	{
		cout << "\n\n������ ��������� ����� (������ ������):" << endl;
		cout << "1 - ������ �����" << endl;
		cout << "2 - �������� �� �����" << endl;
		cout << "3 - �������� �����" << endl;
		cout << "4 - ������ ��������" << endl;
		cout << "5 - �������� ������ ��������" << endl;
		cout << "6 - ��������� �������� �� ���� �����" << endl;
		cout << "7 - �������� ��������" << endl;
		cout << "0 - ������� ���������\n" << endl;
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
			cout << "���� �������! ������� ������ ����� �� 0 �� 7!";
			break;
		}
	} while (choice != '0');
}

void Group::AddGroup()
{
	if (groupID == MAXGROUPS)
	{
		cout << "������ ��� �������� ���� ��� ��������� ����!";
		return;
	}
	groupID++;
	cout << "������ ����� ���� �����: ";
	do
		gets_s(inputField, 63);
	while (!strlen(inputField));
	strncpy_s(groupNumber[groupID].groupName, 9, inputField, 8);
	_strupr(groupNumber[groupID].groupName);
	groupNumber[groupID].groupID = groupID;
	cout << "������ ���� ����� \"" << groupNumber[groupID].groupName << "\" � ID " << groupNumber[groupID].groupID << endl;
}

void Group::ShowAllGroups()
{
	if (!groupID)
	{
		cout << "�� �� �� ������ ����� �����!";
		return;
	}
	cout << "������ ����:" << endl;
	cout << "ID \t ����� �����" << endl;
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
		cout << "�� �� �� ������ ����� �����!";
		return;
	}
	unsigned short temp = 0;
	cout << "������ ID �����, ��� ������ �������� (�� 1 �� " << groupID << ") ��� ������ ����, ��� ���������� ������ ����: ";
	temp = GetCorrectNumber();
	if (!temp)
		groupNumber[0].ShowAllGroups();
	else if (temp > groupID)
	{
		cout << "�������! ����� ����� �� ���� �� 1 �� " << groupID << ": " << endl;
		Group::DeleteGroup();
	}
	else
	{
		cout << "\n����� \"" << groupNumber[temp].groupName << "\" � ID " << temp << " ��������!" << endl;
		groupNumber[temp].groupName[0] = { 0 };
		groupNumber[temp].groupID = 0;
	}
}

void Group::GroupIDdecoding(unsigned short i)
{
	if (!strlen(groupNumber[i].groupName))
		cout << "\"����� � ID " << i << " �� ��������\"" << endl;
	else
		cout << "\"" << groupNumber[i].groupName << "\"" << endl;
	
}

void Student::AddStudent()
{
	if (studentID == MAXSTUDENTS)
	{
		cout << "������ ��� �������� ���� ��� ��������� ��������!";
		return;
	}
	studentID++;
	cout << "������ ������� ������ ��������: ";
	do
		gets_s(inputField, 63);
	while (!strlen(inputField));
	strncpy_s(studentNumber[studentID].surname, 31, inputField, 30);
	cout << "������ ��\'� ������ ��������: ";
	do
		gets_s(inputField, 63);
	while (!strlen(inputField));
	strncpy_s(studentNumber[studentID].name, 16, inputField, 15);
	cout << "������ ����� �������� ������ �������� (���� �����): ";
	do
		gets_s(inputField, 63);
	while (!strlen(inputField));
	strncpy_s(studentNumber[studentID].phoneNumber, 16, inputField, 15);
	short temp = 0;
	cout << "������ ID ����� ������ �������� ��� ������ ����, ��� ���������� ������ ����: ";
	temp = GetCorrectNumber();
	if (!temp)
	{
		cout << endl;
		groupNumber[0].ShowAllGroups();
		cout << "\n������ ID ����� ������ ��������: ";
		temp = GetPositiveNumber();
	}
	studentNumber[studentID].group = temp;
	studentNumber[studentID].studentID = studentID;
	cout << "������� ����� ������� \"" << studentNumber[studentID].surname << "\" � ID " << studentNumber[studentID].studentID << endl;
}

void Student::ShowAllStudents()
{
	if (!studentID)
	{
		cout << "�� �� �� ������ ������� ��������!";
		return;
	}
	cout << "������ ��������:" << endl;
	printf("ID    %-32s  %-16s  %-16s  %-9s\n", "�������", "��\'�", "�������", "�����");
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
	cout << "������ ID ��������, ����� ������ ��������� �� ���� ����� ��� ������ ����, ��� ���������� ������ ��������: ";
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
		cout << "�������! ����� ������� ������� � ������. ����� ID �� ���� �� 1 �� " << studentID << ": " << endl;
		Student::ChangeGroupByStudent();
	}
	else
	{
		cout << "������ ID �����, �� ��� ������� ��������� \"" << studentNumber[temp].surname << "\": ";
		studentNumber[temp].group = GetPositiveNumber();
		cout << "\"" << studentNumber[temp].surname << "\" ����������� �� ����� ";
			Group::GroupIDdecoding(studentNumber[temp].group);
	}
}

void Student::DeleteStudent()
{
	if (!studentID)
	{
		cout << "�� �� �� ������ ������� ��������!";
		return;
	}
	unsigned short temp = 0;
	cout << "������ ID ��������, ����� ������ �������� (�� 1 �� " << studentID << ") ��� ������ ����, ��� ���������� ������ ��������: ";
	temp = GetCorrectNumber();
	if (!temp)
		studentNumber[0].ShowAllStudents();
	else if (temp > studentID)
	{
		cout << "�������! ����� ������� ������� � ������. ����� ID �� ���� �� 1 �� " << studentID << ": " << endl;
		Student::DeleteStudent();
	}
	else
	{
		cout << "������� \"" << studentNumber[temp].surname << "\" � ID " << temp << " ���������!" << endl;
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
		cout << "\n������� ����� �����! ������ ����� �� ���: ";
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
		cout << "\n������� ����� �����! ������ ����� ���� �� ����: ";
		GetPositiveNumber();
	}
	return atoi(inputField);
}