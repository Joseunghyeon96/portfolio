#include "stdafx.h"
#include "Borland.h"



int Borland::wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	return csbiInfo.dwCursorPosition.X;

}

int Borland::wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	return csbiInfo.dwCursorPosition.Y;
}

void Borland::gotoxy(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
}

void Borland::gotoxy(const Vector2 * pos)
{

	if (!pos) return;
	gotoxy((*pos).X(), (*pos).Y());
}

void Borland::gotoxy(const Vector2& pos)
{

	gotoxy(pos.X(), pos.Y());
}
