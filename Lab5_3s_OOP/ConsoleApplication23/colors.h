#include <windows.h>

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void header()
{
	SetConsoleTextAttribute(hStdOut,
		BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void grayed()
{
	SetConsoleTextAttribute(hStdOut,
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void result()
{
	SetConsoleTextAttribute(hStdOut,
		FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void plain()
{
	SetConsoleTextAttribute(hStdOut,
		FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE |
		FOREGROUND_INTENSITY);
}

void items()
{
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN |
		FOREGROUND_INTENSITY);
}

void red()
{
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED |
		FOREGROUND_INTENSITY);
}