#define _CRT_SECURE_NO_WARNINGS
#include <windows.h> 
#include <windowsx.h> 
#include <stdio.h> 
#include <locale.h>
#include <conio.h> 
#include <iostream>
#include <string.h>
#include "user.h"

void main()
{
	setlocale(LC_CTYPE, "Russian");
	bool exit = false, showMenu = true;
	char fin[30], fout[30], input;
	romb sq;
	RECT rt;
	POINT* k;
	HWND hwnd = GetConsoleWindow();
	while (!exit)
	{
		if (showMenu) { printMenu(); showMenu = false; }
		input = _getch();
		switch (input)
		{
		case '1': //��������
		{
			GetClientRect(hwnd, &rt);
			printf_s("������� ��� �����: ");
			scanf("%s", &fin);
			try { sq.load(fin); sq.draw(); }
			catch (int err) { errMsg(err); }

		} break;

		case '2': //����������
		{
			printf_s("������� ��� �����: ");
			scanf("%s", &fout);
			try { sq.save(fout); }
			catch (int err) { errMsg(err); }
		} break;

		case '3': //������� ����� ������
		{
			POINT tk[5];
			int tside, tptype, tbtype, twidth;
			color tpcol, tbcol;
			bool OK = false;
			while (!OK)
			{
				printf_s("������� ��������� ������ ���������� �����:\n");
				scanf_s("%d %d %d %d %d %d %d %d", &tk[0].x, &tk[0].y, &tk[1].x, &tk[1].y, &tk[2].x, &tk[2].y, &tk[3].x, &tk[3].y);
				printf_s("������� ����� ������� (���[0-6], �������, ���� � ������� RGB):\n");
				scanf_s("%d %d %d %d %d", &tptype, &twidth, &tpcol.r, &tpcol.g, &tpcol.b);
				printf_s("������� ����� ������� (���[-2 - ��� �������; -1 - ��������][-2 - 5], ���� RGB):\n");
				scanf_s("%d %d %d %d", &tbtype, &tbcol.r, &tbcol.g, &tbcol.b);
				try
				{
					tk[4] = tk[0];
					sq.check_figure(tk);
					sq.check_borders(tk);
					sq.SetFigure(tk);
					sq.SetPStyle(tptype, twidth, tpcol);
					sq.SetBStyle(tbtype, tbcol);
					sq.draw();
					OK = true;
				}
				catch (int err) { errMsg(err); }
			}
		} break;

		case '4': //����������� ������
		{
			int new_x, new_y;
			printf_s("������� ���������� �����������(�� �� � �� ��):\n");
			scanf_s("%d%d", &new_x, &new_y);
			try {
				sq.SetPos(new_x, new_y);
				sq.draw();
			}
			catch (int err) { errMsg(err); }
		} break;

		case '5': //�������� ������
		{ sq.draw();} break;

		case 'm': { showMenu = true; } break;	//�������� ����

		case 27: { exit = true; } break;		//�����

		}
	}
}