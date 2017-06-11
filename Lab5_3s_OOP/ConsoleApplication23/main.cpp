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
	bool exit = false, showMenu = true, ContExists = false;
	char fin[30], fout[30], input;
	POINT tk[5], tki[5];
	int  tptype, tbtype, twidth;
	color tpcol, tbcol;
	bool est = false, canf = true, canh = true;
	Stack <romb> *st=NULL;
	Stack <SolidRomb> *sst = NULL;
	Stack <HollowRomb> *hst = NULL;
	romb rb;
	SolidRomb srb;
	HollowRomb hrb;
	RECT rt;
	HWND hwnd = GetConsoleWindow();
	while (!exit)
	{
		if (showMenu) { printMenu(ContExists); showMenu = false; }
		input = _getch();
		switch (input)
		{
		case '1': //загрузка
		{
			ContExists = false;
			GetClientRect(hwnd, &rt);
			cout << "Введите имя файла: "; cin >> fin;
			FILE *fptr = fopen(fin, "r");
			if (!fptr)
			{
				red(); cout << "Не удалось открыть файл"; plain();
			}
			else
			{
				if (st) { st->~Stack(); st = NULL; };
				if (sst) { sst->~Stack(); sst = NULL; };
				if (hst) { hst->~Stack(); hst = NULL; };

				char type[20];
				fscanf(fptr, "%s", type);
				if (strcmp(type, "romb") == 0)
				{
					try { st = new Stack <romb>(fptr); ContExists = true;  canf = false; canh = false; }
					catch (char *err) { red(); cout << err << endl; plain(); }
				}
				if (strcmp(type, "solid") == 0)
				{
					try { sst = new Stack <SolidRomb>(fptr); ContExists = true; canh = false; canf = true; }
					catch (char *err) { red(); cout << err << endl; plain(); }
				}
				if (strcmp(type, "hollow") == 0)
				{
					try { hst = new Stack <HollowRomb>(fptr); ContExists = true; canh = true; }
					catch (char *err) { red(); cout << err << endl; plain(); }
				}
			}

		} break;

		case '2': //ручной ввод ромба и его последующее добавление в стек
		{
			header(); printf_s("Задайте параметры фигуры: координаты точек:\n");
			scanf_s("%d %d %d %d %d %d %d %d", &tk[0].x, &tk[0].y, &tk[1].x, &tk[1].y, &tk[2].x, &tk[2].y, &tk[3].x, &tk[3].y);
			printf_s("Задайте стиль границы (тип[0-6], толщина, цвет в формате RGB):\n");
			tk[4] = tk[0];
			scanf_s("%d %d %d %d %d", &tptype, &twidth, &tpcol.r, &tpcol.g, &tpcol.b);
			ContExists = true;
			if (canf) {
				printf_s("Будет ли эта фигура закрашенной?[Y]/[N]");
				input = _getch();
				switch (input)
				{
				case 'y':
				{
					printf_s("Задайте стиль заливки (тип[-1 - сплошная][-1 - 5], цвет RGB):\n");
					scanf_s("%d %d %d %d", &tbtype, &tbcol.r, &tbcol.g, &tbcol.b);
					if (canh) {
						printf_s("Будет ли эта фигура полой?[Y]/[N]");
						switch (input)
						{
						case 'y':
						{
							printf_s("Задайте координаты точек внутренней полости:\n");
							scanf_s("%d %d %d %d %d %d %d %d", &tki[0].x, &tki[0].y, &tki[1].x, &tki[1].y, &tki[2].x, &tki[2].y, &tki[3].x, &tki[3].y);
							tki[4] = tki[0];
						}
						default: 
						{
							canh = false;
						}
						}
					}
				}
				default:
				{
					canf = false; canh = false;
				}
				}
			}
			try {
				if (canh == true) {
					hrb.validate(tk, tptype, twidth, tpcol, tbtype, tbcol, tki);
					hrb.SetFigure(tk);
					hrb.SetFrameStyle(tptype, twidth, tpcol);
					hrb.SetFillStyle(tbtype, tbcol);
					hrb.SetInnerFigure(tki);
					if (!hst) hst = new Stack<HollowRomb>();
					hst->push(hrb);
					ContExists = true;
					canf = false;
				}
				else if (canf == true) {
					srb.validate(tk, tptype, twidth, tpcol, tbtype, tbcol);
					srb.SetFigure(tk);
					srb.SetFrameStyle(tptype, twidth, tpcol);
					srb.SetFillStyle(tbtype, tbcol);
					if (!sst) sst = new Stack<SolidRomb>();
					sst->push(srb);
					ContExists = true;
					canh = false;
				}
				else {
					rb.validate(tk, tptype, twidth, tpcol);
					rb.SetFigure(tk);
					rb.SetFrameStyle(tptype, twidth, tpcol);
					if (!st) st = new Stack<romb>();
					st->push(rb);
					ContExists = true; canh = false; canf = false;
				}
			}
			catch (char *err) { red(); cout << err << endl; plain(); }
		} break;

		case '3': //сохранение
		{
			try
			{
				if (canh) {
					if (!hst) throw EMPTY_STACK;
				}
				else if (canf) {
					if (!sst) throw EMPTY_STACK;
				}
				else if (!st) throw EMPTY_STACK;
				printf_s("Введите имя файла: ");
				scanf("%s", &fout);
				if (canh) {
					hst->save(fout);
				}
				else if (canf) {
					sst->save(fout);
				}
				else { st->save(fout); }
			}
			catch (char *err) { red(); cout << err << endl; plain(); }
		} break;

		case '4': //удаление ромба из стека
		{
			try
			{
				if (canh) {
					if (!hst) throw EMPTY_STACK;
					hrb=hst->pop(); est = true;
				}
				else if (canf) {
					if (!sst) throw EMPTY_STACK;
					srb=sst->pop(); est = true;
				}
				else {
					if (!st) throw EMPTY_STACK;
					rb=st->pop(); est = true;
				}
			}
			catch (char *err) { red(); cout << err << endl; plain(); }
		} break;

		case '5': //отобразить ромб из памяти
		{
			if (est == false) printf("В памяти ничего не лежит \n");
			else {
				try {
					if (canh) {
						hrb.draw();
					}
					else if (canf) {
						srb.draw();
					}
					else { rb.draw(); }
				}
				catch (char *err) { red(); cout << err << endl; plain(); }
			}
		} break;

		case '6': //поиск фигуры
		{
			try
			{
				if (canh) {
					if (!hst) throw EMPTY_STACK;
				}
				else if (canf) {
					if (!sst) throw EMPTY_STACK;
				}
				else if (!st) throw EMPTY_STACK;
				printf_s("Задайте параметры фигуры: координаты точек:\n");
				scanf_s("%d %d %d %d %d %d %d %d;", &tk[0].x, &tk[0].y, &tk[1].x, &tk[1].y, &tk[2].x, &tk[2].y, &tk[3].x, &tk[3].y);
				tk[4] = tk[0];
				if (canh) {
					printf_s("Задайте координаты вершин полости:\n");
					scanf_s("%d %d %d %d %d %d %d %d;", &tki[0].x, &tki[0].y, &tki[1].x, &tki[1].y, &tki[2].x, &tki[2].y, &tki[3].x, &tki[3].y);
					tki[4] = tki[0];
					hrb.SetFigure(tk);
					hrb.SetInnerFigure(tki);
					if (hst->search(hrb)) {
						printf("Такая фигура есть в стеке \n");
					}
					else printf("Такой фигуры в стеке нету\n");
				}
				else if (canf) 
				{
					srb.SetFigure(tk);
					if (sst->search(srb)) 
					{
						printf("Такая фигура есть в стеке \n");
					}
					else printf("Такой фигуры в стеке нету\n");
				}
				else {
					rb.SetFigure(tk);
					if (st->search(rb))
					{
						printf("Такая фигура есть в стеке \n");
					}
					else printf("Такой фигуры в стеке нету\n");
				}
			}
			catch (char *err) { red(); cout << err << endl; plain(); }
			break; }

		case '7': //отобразить стек
		{
			try
			{
				if (canh) 
				{
					if (!hst) throw EMPTY_STACK;
					hst->DrawSt();
				}
				else if (canf) 
				{
					if (!sst) throw EMPTY_STACK;
					sst->DrawSt();
				}
				else 
				{ 
					if (!st) throw EMPTY_STACK;
					st->DrawSt();
				}

			}
			catch (char *err) { red(); cout << err << endl; plain();
			}
		} break;

		case 'm': { showMenu = true; } break;	//показать меню

		case 27: { exit = true; } break;		//выход

		}
	}
}