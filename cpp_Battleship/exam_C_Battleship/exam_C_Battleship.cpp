#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;

#define SIZE 10 //������� ��� ������/������ ���� �������� �� ����� ������ (�� 10 �� 26)
short ships[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 }; // ������� ��� ������� �������

void NullArrays();
void RefreshScreen();
void DifficultyLevel();
void ArraysInitialization();
bool InitUsersField(short longShip);
char GetCorrectDirection();
short GetCorrectCharacter();
short GetCorrectNumber();
void GetCorrectString(char *pString, short longString);
bool InitCompField(short longShip);
bool TestVerticalLine(struct BattleField *p, short longShip, short x, short y);
bool TestHorizontalLine(struct BattleField *p, short longShip, short x, short y);
void PlayGame(short *shipsSum);
short CompsShot();
bool IntellectualShot(short *x, short *y);
short UsersShot();
void GameResults();
void ShowUsersFields();
void ShowCompsFields();

struct BattleField
{
	char mainField[SIZE][SIZE];
	char verificationField[SIZE][SIZE];
	char gamerName[24];
	short score;
} user, comp;

char choice = ' ';
char inputField[24] = { 0 };
bool difficultyLevel = 0;
short shipsNumber = 0;
short shipsSum = 0;

void main()
{
	system("color F0");
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	NullArrays();
	ArraysInitialization();
	RefreshScreen();
	DifficultyLevel();
	RefreshScreen();
	PlayGame(&shipsSum);
	GameResults();
}

void NullArrays()
{
	for (short i = 0; i < SIZE; i++)
	{
		for (short j = 0; j < SIZE; j++)
			user.mainField[i][j] = ' ';
	}
	for (short i = 0; i < SIZE; i++)
	{
		for (short j = 0; j < SIZE; j++)
			user.verificationField[i][j] = ' ';
	}
	user.score = 0;
	comp = user;
}

void RefreshScreen()
{
	system("cls");
	printf("\t\t***��� �������� �I�***\n\n");
	printf("ʳ������ ���� ����\'�����: %i\n���� ������� ����: %i\n\n", comp.score, user.score);
	ShowUsersFields();
	//ShowCompsFields(); // ������������� �������, ���� ������ ������ ���� ����'����� �� ��� ���
}

void DifficultyLevel()
{
	printf("\n������ ����� ���������! (\"0\" - ������� �����, ��� ����-��� ���� ������, ��� �������� �����): ");
	choice = _getch();
	if (choice == '0')
		difficultyLevel = 0;
	else
		difficultyLevel = 1;
	printf("\n\n������ ���� ��\'�: ");
	GetCorrectString(user.gamerName, 23);
	strcpy_s(comp.gamerName, inputField);
	strcpy_s(comp.gamerName, "����\'����");
}

void ArraysInitialization()
{
	shipsNumber = _countof(ships);
	for (short i = 0; i < shipsNumber; i++)
		shipsSum += ships[i];
	for (short i = 0; i < shipsNumber; i++)
	{
		RefreshScreen();
		for (; !InitUsersField(ships[i]); );
		for (; !InitCompField(ships[i]); );
	}
}

bool InitUsersField(short longShip)
{
	printf("I��������� � ��������� �������: ������ �������� ���������� �������. ������ �� ������ ���� �����!\n");
	short x = 0, y = 0;
	char direction = 'v';
	if (longShip != 1)
	{
		printf("\n������ �������� ��� %i-��������� ������� (\"V\" - ������������ ��� \"H\" - ��������������): ", longShip);
		direction = GetCorrectDirection();
	}
	printf("\n������ ����� �� ���������� ��� %i-��������� �������: ", longShip);
	x = GetCorrectCharacter();
	printf("\n������ ����� �� �������� ��� %i-��������� �������: ", longShip);
	y = GetCorrectNumber();
	if ((direction == 'V' || direction == 'v') && (y <= SIZE - longShip) && TestVerticalLine(&user, longShip, y, x))
	{
		for (short z = 0; z < longShip; z++)
			user.mainField[y + z][x] = 'O';
	}
	else if ((direction == 'H' || direction == 'h') && (x <= SIZE - longShip) && TestHorizontalLine(&user, longShip, y, x))
	{
		for (short z = 0; z < longShip; z++)
			user.mainField[y][x + z] = 'O';
	}
	else
	{
		printf("\n\n��� ������� �� ���� ���� ��� ������������! �������� ����!\n");
		return 0;
	}
}

char GetCorrectDirection()
{
	char temp = _getche();
	if (temp == 'V' || temp == 'v' || temp == 'H' || temp == 'h')
		return temp;
	else
	{
		printf("\n���� ����� �������! ������ ����� \"V\" ��� \"H\"! ");
		GetCorrectDirection();
	}
}

short GetCorrectCharacter()
{
	char temp = ' ';
	temp = _getche();
	if (temp >= 65 && temp < 65 + SIZE)
		return temp - 65;
	if (temp >= 97 && temp < 97 + SIZE)
		return temp - 97;
	else
	{
		printf("\n���� ����� �������! ������ ����� � ��������� ����! ");
		GetCorrectCharacter();
	}
}

short GetCorrectNumber()
{
	if (SIZE <= 10)
	{
		inputField[0] = _getche();
		if (atoi(inputField) >= 0 && atoi(inputField) < SIZE)
			return atoi(inputField);
		else
		{
			printf("\n���� ����� ������! ������ ����� � ����� ���������! ");
			GetCorrectNumber();
		}
	}
	else
	{
		GetCorrectString(inputField, 2);
		if (atoi(inputField) >= 0 && atoi(inputField) < SIZE)
			return atoi(inputField);
		else
		{
			printf("\n���� ����� ������! ������ ����� � ����� ���������! ");
			GetCorrectNumber();
		}
	}
}

void GetCorrectString(char *pString, short longString)
{
	for (int i = 0; ; i++)
	{
		pString[i] = _getche();
		if (pString[i] == 13)
		{
			pString[i] = '\0';
			break;
		}
		else if (i == longString - 1)
		{
			pString[longString] = '\0';
			break;
		}
	}
	if (!strlen(pString))
		GetCorrectString(pString, longString);
}

bool TestVerticalLine(struct BattleField *p, short longShip, short x, short y)
{
	for (short a = x - 1; a <= x + longShip; a++)
	{
		for (short b = y - 1; b < y + 2; b++)
		{
			if (a < 0 || a >= SIZE || b < 0 || b >= SIZE)
				continue;
			if (p -> mainField[a][b] == 'O')
				return 0;
		}
	}
	return 1;
}

bool TestHorizontalLine(struct BattleField *p, short longShip, short x, short y)
{
	for (short a = x - 1; a < x + 2; a++)
	{
		for (short b = y - 1; b <= y + longShip; b++)
		{
			if (a < 0 || a >= SIZE || b < 0 || b >= SIZE)
				continue;
			if (p -> mainField[a][b] == 'O')
				return 0;
		}
	}
	return 1;
}

bool InitCompField(short longShip)
{
	srand((unsigned)time(NULL));
	unsigned short x = rand() % (SIZE - longShip);
	unsigned short y = rand() % SIZE;
	if (TestVerticalLine(&comp, longShip, x, y))
	{
		for (short z = 0; z < longShip; z++)
			comp.mainField[x + z][y] = 'O';
		return 1;
	}
	else if (TestHorizontalLine(&comp, longShip, y, x))
	{
		for (short z = 0; z < longShip; z++)
			comp.mainField[y][x + z] = 'O';
		return 1;
	}
	else
		return 0;
}

short CompsShot()
{
	srand((unsigned)time(NULL));
	short x = 0, y = 0;
	if (difficultyLevel && IntellectualShot(&x, &y))
		;
	else
	{
		x = rand() % SIZE;
		y = rand() % SIZE;
	}
	if (user.mainField[x][y] == 'O')
	{
		user.mainField[x][y] = 'X';
		comp.verificationField[x][y] = 'X';
		return 2;
	}
	else if (user.mainField[x][y] == 'X' || user.mainField[x][y] == (char)149)
		return 1;
	else
	{
		user.mainField[x][y] = 149;
		comp.verificationField[x][y] = 149;
		return 0;
	}
}

bool IntellectualShot(short *x, short *y)
{
	for (short i = 0; i < SIZE; i++)
	{
		for (short j = 0; j < SIZE; j++)
		{
			if (comp.verificationField[i][j] == 'X' && j != SIZE - 1 && comp.verificationField[i][j + 1] == ' ')
			{
				*x = i;
				*y = j + 1;
				return 1;
			}
			else if (comp.verificationField[i][j] == 'X' && j && comp.verificationField[i][j - 1] == ' ')
			{
				*x = i;
				*y = j - 1;
				return 1;
			}
			else if (comp.verificationField[i][j] == 'X' && i != SIZE - 1 && comp.verificationField[i + 1][j] == ' ')
			{
				*x = i + 1;
				*y = j;
				return 1;
			}
			else if (comp.verificationField[i][j] == 'X' && i && comp.verificationField[i - 1][j] == ' ')
			{
				*x = i - 1;
				*y = j;
				return 1;
			}
			else
				continue;
		}
	}
	return 0;
}

short UsersShot()
{
	short x = 0, y = 0;
	printf("\n������ ����� �� ���������� ��� ������� ����\'�����: ");
	x = GetCorrectCharacter();
	printf("\n������ ����� �� �������� ��� ������� ����\'�����: ");
	y = GetCorrectNumber();
	if (comp.mainField[y][x] == 'O')
	{
		comp.mainField[y][x] = 'X';
		user.verificationField[y][x] = 'X';
		return 2;
	}
	else if (comp.mainField[y][x] == 'X' || comp.mainField[y][x] == (char)149)
		return 1;
	else
	{
		comp.mainField[y][x] = 149;
		user.verificationField[y][x] = 149;
		return 0;
	}
}

void PlayGame(short *shipsSum)
{
	short temp = 0;
	do
	{
		do
		{
			printf("\n���� ����� ������ ������.");
			temp = UsersShot();
			if (temp == 2)
			{
				user.score++;
				RefreshScreen();
				printf("\n\n\a�����, ������� ������!!!\n");
			}
			else if (temp == 1)
				printf("\n\n�� ��� ������ ������ � ��� �������!!! �������� ������!\n");
			else
			{
				RefreshScreen();
				printf("\n�� ����, �� �� �������!!!\n�������� ����-��� ������ � ����\'���� ������ ��� ���!\n");
				_getch();
			}
		} while (temp && user.score < *shipsSum);
		if (user.score == *shipsSum)
			return;
		printf("\n\t\t\t����� ����\'����� ������ ������. ����������...");
		do
		{
			temp = CompsShot();
			if (temp == 2)
			{
				comp.score++;
				RefreshScreen();
				printf("\n\t\t\t\a����\'���� ������ � ��� ��������!!!\n\t\t\t�������� ����-��� ������ � ����\'���� ����������!\n");
				_getch();
			}
			else if (!temp)
			{
				RefreshScreen();
				printf("\n\n\t\t\t����\'���� �� ������!!!\n\t\t\t�������� ����-��� ������ � ������ ��� ���!\n");
				_getch();
			}
		} while (temp && comp.score < *shipsSum);
	} while (comp.score < *shipsSum && user.score < *shipsSum);
	return;
}

void GameResults()
{
	system("cls");
	FILE *file;
	fopen_s(&file, "results.txt", "a+");
	fprintf_s(file, "\t\t***���������� ���***\n");
	fprintf_s(file, "(��� �������� %s � %s)\n", __DATE__, __TIME__);
	fprintf_s(file, "(����� %s �� %s)\n", comp.gamerName, user.gamerName);

	printf("\t\t***���������� ���***\n\n");
	if (comp.score == shipsSum)
	{
		printf("\n����\'���� ������ � �������� %i:%i!!!\n", comp.score, user.score);
		fprintf_s(file, "\n����\'���� ������ � �������� %i:%i!!!\n", comp.score, user.score);
	}
	else if (user.score == shipsSum)
	{
		printf("\n�� ��������� � �������� %i:%i!!!\n", user.score, comp.score);
		fprintf_s(file, "\n%s ������ � �������� %i:%i!!!\n", user.gamerName, user.score, comp.score);
	}
	short temp = SIZE * SIZE;
	for (short i = 0; i < SIZE; i++)
	{
		for (short j = 0; j < SIZE; j++)
		{
			if (comp.verificationField[i][j] == ' ')
				temp--;		
		}	
	}
	printf("\nʳ������ ��������� ����\'������ ����: %i", temp);
	printf("\n³������ ������� ������� ����\'�����: %i", 100 * comp.score / temp);
	fprintf_s(file, "\nʳ������ ��������� ����\'������ ����: %i", temp);
	fprintf_s(file, "\n³������ ������� ������� ����\'�����: %i", 100 * comp.score / temp);
	temp = SIZE * SIZE;
	for (short i = 0; i < SIZE; i++)
	{
		for (short j = 0; j < SIZE; j++)
		{
			if (user.verificationField[i][j] == ' ')
				temp--;
		}
	}
	printf("\n\nʳ������ ��������� ���� ����: %i", temp);
	printf("\n³������ ����� ������� �������: %i\n\n", 100 * user.score / temp);

	fprintf_s(file, "\n\nʳ������ ����, �� ������ %s: %i", user.gamerName, temp);
	fprintf_s(file, "\n³������ ������� �������, �� ������ %s: %i\n\n", user.gamerName, 100 * user.score / temp);
	fprintf_s(file, "************************************************\n\n", user.gamerName, 100 * user.score / temp);
	fclose(file);
	ShowCompsFields();
	_getch();
}

void ShowUsersFields()
{
	printf("   ���� ������ ����:");
	for (short i = 0; i < SIZE; i += 5)
		printf("\t ");
	printf(" ���� ��� ������������:\n    ");
	for (short i = 0; i < 2; i++)
	{
		for (short j = 65; j < 65 + SIZE; j++)
			printf("%c ", j);
		if (i == 0)
			printf(" \t    ");
	}
	printf("\n   _");
	for (short i = 0; i < 2; i++)
	{
		for (short j = 0; j < SIZE; j++)
			printf("__");
		if (i == 0)
			printf("  \t   _");
	}
	printf(" \n");
	for (short i = 0; i < SIZE; i++)
	{
		printf("%2i| ", i);
		for (short j = 0; j < SIZE; j++)
			printf("%c ", user.mainField[i][j]);
		printf("| \t%2i| ", i);
		for (short j = 0; j < SIZE; j++)
			printf("%c ", user.verificationField[i][j]);
		printf("|\n");
	}
	printf("  |_");
	for (short i = 0; i < 2; i++)
	{
		for (short j = 0; j < SIZE; j++)
			printf("__");
		if (i == 0)
			printf("|  \t  |_");
	}
	printf("|\n\n");
}

void ShowCompsFields()
{
	printf("   ������ ���� ����\'�����:");
	for (short i = 0; i < SIZE; i += 10)
		printf("\t ");
	printf(" ���� ����\'����� ��� ������������:\n    ");
	for (short i = 0; i < 2; i++)
	{
		for (short j = 65; j < 65 + SIZE; j++)
			printf("%c ", j);
		if (i == 0)
			printf(" \t    ");
	}
	printf("\n   _");
	for (short i = 0; i < 2; i++)
	{
		for (short j = 0; j < SIZE; j++)
			printf("__");
		if (i == 0)
			printf("  \t   _");
	}
	printf(" \n");
	for (short i = 0; i < SIZE; i++)
	{
		printf("%2i| ", i);
		for (short j = 0; j < SIZE; j++)
			printf("%c ", comp.mainField[i][j]);
		printf("| \t%2i| ", i);
		for (short j = 0; j < SIZE; j++)
			printf("%c ", comp.verificationField[i][j]);
		printf("|\n");
	}
	printf("  |_");
	for (short i = 0; i < 2; i++)
	{
		for (short j = 0; j < SIZE; j++)
			printf("__");
		if (i == 0)
			printf("|  \t  |_");
	}
	printf("|\n\n");
}