#define _CRT_SECURE_NO_WARNINGS
#include <windows.h> 
#include <windowsx.h> 
#include <stdio.h> 
#include <locale.h>
#include <conio.h> 
#include <iostream>
#include <string.h>
#include "user.h"
/////
void main()
{
	setlocale(LC_CTYPE, "Russian");
	bool exit = false, showMenu = true;
	char fin[30], fout[30], input;
	romb sq, sw, se;
	POINT tk[5];
	int  tptype, tbtype, twidth;
	color tpcol, tbcol;
	bool est = false;;
	Stack *rs=NULL;
	RECT rt;
	HWND hwnd = GetConsoleWindow();
	while (!exit)
	{
		if (showMenu) { printMenu(); showMenu = false; }
		input = _getch();
		switch (input)
		{
		case '1': //загрузка
		{
			GetClientRect(hwnd, &rt);
			printf_s("Введите имя файла: ");
			scanf("%s", &fin);
			if (rs) rs->~Stack();
			rs = NULL;
			try
			{
				rs= new Stack(fin);
			}
			catch (char *err) { printf_s("%s", err); }

		} break;

		case '2': //сохранение
		{
			try 
			{
				if (!rs) throw EMPTY_STACK;
				printf_s("Введите имя файла: ");
				scanf("%s", &fout);
				rs->save(fout); 
			}
			catch (char *err) { printf_s("%s", err); }
		} break;

		case '3': //ручной ввод ромба и его последующее добавление в стек
		{
			printf_s("Задайте параметры фигуры: координаты точек:\n");
			scanf_s("%d %d %d %d %d %d %d %d;", &tk[0].x, &tk[0].y, &tk[1].x, &tk[1].y, &tk[2].x, &tk[2].y, &tk[3].x, &tk[3].y);
			printf_s("Задайте стиль границы (тип[0-6], толщина, цвет в формате RGB):\n");
			scanf_s("%d %d (%d, %d, %d)", &tptype, &twidth, &tpcol.r, &tpcol.g, &tpcol.b);
			printf_s("Задайте стиль заливки (тип[-2 - без заливки; -1 - сплошная][-2 - 5], цвет RGB):\n");
			scanf_s("%d (%d, %d, %d)", &tbtype, &tbcol.r, &tbcol.g, &tbcol.b);
			tk[4] = tk[0];
			try {
				sq.SetFigure(tk);
				sq.SetPStyle(tptype, twidth, tpcol);
				sq.SetBStyle(tbtype, tbcol);
				if (!rs) rs=new Stack;
				rs->push(sq);
				
			}
			catch (char *err) { printf_s("%s", err); }
		}

		case '4': //удаление ромба из стека
		{
			try
			{
				if (!rs) throw EMPTY_STACK;
				sw = rs->pop();
				est = true;
			}
			catch (char *err) { printf_s("%s", err); }
		} break;

		case '5': //отобразить ромб из памяти
		{
			if (est == false) printf("В памяти ничего не лежит \n");
			else {
				try {
					sw.draw();
				}
				catch (char *err) { printf_s("%s", err); }
			}
		} break;

		case '6': //поиск фигуры
		{
			try
			{
					if (!rs) throw EMPTY_STACK;
					printf_s("Задайте параметры фигуры: координаты точек:\n");
					scanf_s("%d %d %d %d %d %d %d %d;", &tk[0].x, &tk[0].y, &tk[1].x, &tk[1].y, &tk[2].x, &tk[2].y, &tk[3].x, &tk[3].y);
					printf_s("Задайте стиль границы (тип[0-6], толщина, цвет в формате RGB):\n");
					scanf_s("%d %d (%d, %d, %d)", &tptype, &twidth, &tpcol.r, &tpcol.g, &tpcol.b);
					printf_s("Задайте стиль заливки (тип[-2 - без заливки; -1 - сплошная][-2 - 5], цвет RGB):\n");
					scanf_s("%d (%d, %d, %d)", &tbtype, &tbcol.r, &tbcol.g, &tbcol.b);
					tk[4] = tk[0];
					sq.SetFigure(tk);
					sq.SetPStyle(tptype, twidth, tpcol);
					sq.SetBStyle(tbtype, tbcol);
					if (rs->search(sq))
					{
						printf("Такая фигура есть в стеке \n");
						printf("Отобразить найденную фигуру?[Y/N]\n");
						input = _getch();
						switch (input) {
						case 'y':
						{
							sq.draw();
						}
						case 'n': {}
						}
					}
					else printf("Такой фигуры в стеке нет\n");
				}
				catch (char *err) { printf_s("%s", err); }
				break; }

		case '7': //отобразить стек
		{
			try
			{
				if (!rs) throw EMPTY_STACK;
				rs->DrawSt();
			}
			catch (char *err) { printf_s("%s", err); }
		} break;

		case 'm': { showMenu = true; } break;	//показать меню

		case 27: { exit = true;} break;		//выход

		}	
	}
}