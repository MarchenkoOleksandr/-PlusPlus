#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;

#define SIZE 10 //задайте тут висоту/ширину поля відповідно до Ваших правил (від 10 до 26)
short ships[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 }; // задайте тут довжини кораблів

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
	printf("\t\t***ГРА МОРСЬКИЙ БIЙ***\n\n");
	printf("Кількість балів комп\'ютера: %i\nВаша кількість балів: %i\n\n", comp.score, user.score);
	ShowUsersFields();
	//ShowCompsFields(); // розкоментуйте функцію, якщо хочете бачити поле комп'ютера під час гри
}

void DifficultyLevel()
{
	printf("\nОберіть рівень складності! (\"0\" - простий рівень, або будь-яку іншу клавішу, щоб складний рівень): ");
	choice = _getch();
	if (choice == '0')
		difficultyLevel = 0;
	else
		difficultyLevel = 1;
	printf("\n\nВведіть Ваше ім\'я: ");
	GetCorrectString(user.gamerName, 23);
	strcpy_s(comp.gamerName, inputField);
	strcpy_s(comp.gamerName, "Комп\'ютер");
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
	printf("Iнструкція з розміщення кораблів: введіть початкові координати кораблів. Кораблі не можуть бути поруч!\n");
	short x = 0, y = 0;
	char direction = 'v';
	if (longShip != 1)
	{
		printf("\nВведіть напрямок для %i-палубного корабля (\"V\" - вертикальний або \"H\" - горизонтальний): ", longShip);
		direction = GetCorrectDirection();
	}
	printf("\nВведіть літеру по горизонталі для %i-палубного корабля: ", longShip);
	x = GetCorrectCharacter();
	printf("\nВведіть цифру по вертикалі для %i-палубного корабля: ", longShip);
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
		printf("\n\nЦей корабль не може бути тут розташований! Повторіть вибір!\n");
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
		printf("\nТака літера відсутня! Введіть літеру \"V\" або \"H\"! ");
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
		printf("\nТака літера відсутня! Введіть літеру з верхнього ряду! ");
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
			printf("\nТаке число відсутнє! Введіть число з лівого стовпчика! ");
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
			printf("\nТаке число відсутнє! Введіть число з лівого стовпчика! ");
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
	printf("\nВведіть літеру по горизонталі для корабля комп\'ютера: ");
	x = GetCorrectCharacter();
	printf("\nВведіть цифру по вертикалі для корабля комп\'ютера: ");
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
			printf("\nВаша черга робити постріл.");
			temp = UsersShot();
			if (temp == 2)
			{
				user.score++;
				RefreshScreen();
				printf("\n\n\aСупер, влучний постріл!!!\n");
			}
			else if (temp == 1)
				printf("\n\nВи вже робили постріл у цей квадрат!!! Повторіть спробу!\n");
			else
			{
				RefreshScreen();
				printf("\nНа жаль, Ви не влучили!!!\nНатисніть будь-яку клавішу і комп\'ютер зробіть свій хід!\n");
				_getch();
			}
		} while (temp && user.score < *shipsSum);
		if (user.score == *shipsSum)
			return;
		printf("\n\t\t\tЧерга комп\'ютера робити постріл. Секундочку...");
		do
		{
			temp = CompsShot();
			if (temp == 2)
			{
				comp.score++;
				RefreshScreen();
				printf("\n\t\t\t\aКомп\'ютер влучив у Ваш корабель!!!\n\t\t\tНатисніть будь-яку клавішу і комп\'ютер продовжить!\n");
				_getch();
			}
			else if (!temp)
			{
				RefreshScreen();
				printf("\n\n\t\t\tКомп\'ютер не влучив!!!\n\t\t\tНатисніть будь-яку клавішу і зробіть свій хід!\n");
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
	fprintf_s(file, "\t\t***СТАТИСТИКА ГРИ***\n");
	fprintf_s(file, "(гра відбулася %s о %s)\n", __DATE__, __TIME__);
	fprintf_s(file, "(грали %s та %s)\n", comp.gamerName, user.gamerName);

	printf("\t\t***СТАТИСТИКА ГРИ***\n\n");
	if (comp.score == shipsSum)
	{
		printf("\nКомп\'ютер переміг з рахунком %i:%i!!!\n", comp.score, user.score);
		fprintf_s(file, "\nКомп\'ютер переміг з рахунком %i:%i!!!\n", comp.score, user.score);
	}
	else if (user.score == shipsSum)
	{
		printf("\nВи перемогли з рахунком %i:%i!!!\n", user.score, comp.score);
		fprintf_s(file, "\n%s переміг з рахунком %i:%i!!!\n", user.gamerName, user.score, comp.score);
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
	printf("\nКількість зроблених комп\'ютером ходів: %i", temp);
	printf("\nВідсоток влучних пострілів комп\'ютера: %i", 100 * comp.score / temp);
	fprintf_s(file, "\nКількість зроблених комп\'ютером ходів: %i", temp);
	fprintf_s(file, "\nВідсоток влучних пострілів комп\'ютера: %i", 100 * comp.score / temp);
	temp = SIZE * SIZE;
	for (short i = 0; i < SIZE; i++)
	{
		for (short j = 0; j < SIZE; j++)
		{
			if (user.verificationField[i][j] == ' ')
				temp--;
		}
	}
	printf("\n\nКількість зроблених Вами ходів: %i", temp);
	printf("\nВідсоток Ваших влучних пострілів: %i\n\n", 100 * user.score / temp);

	fprintf_s(file, "\n\nКількість ходів, які зробив %s: %i", user.gamerName, temp);
	fprintf_s(file, "\nВідсоток влучних пострілів, які зробив %s: %i\n\n", user.gamerName, 100 * user.score / temp);
	fprintf_s(file, "************************************************\n\n", user.gamerName, 100 * user.score / temp);
	fclose(file);
	ShowCompsFields();
	_getch();
}

void ShowUsersFields()
{
	printf("   Ваше ігрове поле:");
	for (short i = 0; i < SIZE; i += 5)
		printf("\t ");
	printf(" Поле для самоконтролю:\n    ");
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
	printf("   Ігрове поле комп\'ютера:");
	for (short i = 0; i < SIZE; i += 10)
		printf("\t ");
	printf(" Поле комп\'ютера для самоконтролю:\n    ");
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