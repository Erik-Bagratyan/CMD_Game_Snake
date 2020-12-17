#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

using namespace std;

bool gameOver;
const int height = 20, width = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 2;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
HANDLE col_game = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Setup()
{	
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	tailX[0] = x;
	tailY[0] = y + 1;
	for(int i = 1; i < nTail; i++)
	{
		tailX[i] = tailX[i-1];
		tailY[i] = tailY[i-1] + 1;
	}
	Xfr :
	fruitX = rand() % width;
	if(fruitX == 0) goto Xfr;
	Yfr :
	fruitY = rand() % height;
	if(fruitY == 0) goto Yfr;
	score = 0;
}

void Draw_Map()
{	
	for(int i = 0; i < width + 2; i++)
		cout << "#";
	cout << "\n";
	for(int i = 0; i< height; i++)
	{
		for(int j = 0; j < width + 2; j++) {
			if(j == 0 || j == width + 1)
				cout << "#";
			else cout << " ";
		}
		cout << endl;
	}
	for(int i = 0; i < width + 2; i++)
		cout << "#";
	SetConsoleTextAttribute(col_game,2);
	cout << "\nScore : " << score << "\n";
}

void Draw_Snake()
{	
	gotoxy(fruitX,fruitY);
	SetConsoleTextAttribute(col_game,FOREGROUND_GREEN);
	cout << "@";
	gotoxy(x,y);
	SetConsoleTextAttribute(col_game,7);
	cout << "O";
	for(int i = 0; i < nTail; i++)
	{
		gotoxy(tailX[i],tailY[i]);
		cout << "o";
	}
	Sleep(250);
}

void Input()
{
	if(_kbhit())
	{
		switch(_getch())
		{
			case 'a':
				if(dir != RIGHT)
				dir = LEFT;
				break;
			case 'd':
				if(dir != LEFT)
				dir = RIGHT;
				break;
			case 'w':
				if(dir != DOWN)
				dir = UP;
				break;
			case 's':
				if(dir != UP)
				dir = DOWN;
				break;
			case 'x':
				{
					system("cls");
					gameOver = true;
					gotoxy(30,8);
					cout << "End Game!!!\n";
					gotoxy(0,20);
				}
				break;
		}
	}
}

void Logic()
{		
	if(x == fruitX && y == fruitY)
	{
		score += 10;
		gotoxy(8,22);
		SetConsoleTextAttribute(col_game,2);
		cout << score;
		Xfr :
		fruitX = rand() % width;
		if(fruitX == 0) goto Xfr;
		Yfr :
		fruitY = rand() % height;
		if(fruitY == 0) goto Yfr;
		nTail++;
	}
	
	if(dir != STOP)
	{
		int prevX = tailX[0];
		int prevY = tailY[0];
		int prev2X, prev2Y;
		tailX[0] = x;
		tailY[0] = y;
		for(int i = 1; i < nTail + 1; i++)
		{
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
		gotoxy(tailX[nTail],tailY[nTail]);
		cout << " ";
	}
	
	switch(dir)
	{
		case LEFT: x--; break;
		case RIGHT: x++; break;
		case UP: y--; break;
		case DOWN: y++; break;
	}
	
	if(x >= width + 1) { x = 1; }
	else if(x <= 0) { x = width; }	
	if(y >= height + 1)	{ y = 1; }
	else if(y <= 0) { y = height; }
	
	for(int i = 3; i < nTail; i++)
		if(tailX[i] == x && tailY[i] == y)
		{	
			system("cls");
			gameOver = true;
			gotoxy(30,8);
			cout << "Game Over!!!\n";
			gotoxy(28,9);
			cout << "Your Score : " << score << "\n";
			gotoxy(0,20);	
			break;
		}
}

int main()
{
	Draw_Map();
	Setup();
	while(!gameOver)
	{	
		Draw_Snake();
		Input();
		Logic();
	}
	system("Pause");
	return 0;
}
