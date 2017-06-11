#define _CRT_SECURE_NO_WARNINGS
#include <windows.h> 
#include <windowsx.h> 
#include <stdio.h> 
#include <locale.h>
#include <conio.h> 
#include <iostream>
#include <string.h>

//Коды ошибок
#define outside_borders 1
#define wrong_dlina 2
#define wrong_parallel 3
#define outside_figure 4

int check_FinF(POINT m1, POINT m2, POINT *n)
{
	int t = 0, z;
	for (int i = 0; i < 4; i++)
	{
		z = (n[i].x - m1.x)*(m2.y - m1.y) - (n[i].y - m1.y)*(m2.x - m1.x);
		if (z < 0) t++;
		else return 0;
	}
	return t;
}

float slope(POINT a, POINT b)
{
	if ((b.x-a.x)!=0)
	return (b.y - a.y) / (b.x - a.x);
	else return 3000;
}

int check_figure(POINT *ppt)
{
	float koef[4];
	float dl[4];
	int i;
	for (i = 0; i < 4; i++)
	{
		koef[i] = slope(ppt[i], ppt[i + 1]);
		dl[i] = sqrt((ppt[i].x - ppt[i + 1].x)*(ppt[i].x - ppt[i + 1].x) + (ppt[i].y - ppt[i + 1].y)*(ppt[i].y - ppt[i + 1].y));
	}
	for (i = 0; i < 3; i++)
	{
		if (dl[i] != dl[i + 1] || dl[i] == 0) return wrong_dlina;
	}
	for (i = 0; i < 2; i++)
	{
		if (koef[i] != koef[i + 2]) return wrong_parallel;
	}
	return 0;
}
int check_borders(POINT *ppt, long rr, long rb)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		if (ppt[i].x >= rr || ppt[i].y >= rb) return outside_borders;
	}
	return 0;
}
int line(HWND hwnd, HDC hdc, POINT *ppt)
{
	int a;
	RECT rt;
	char buf[100];
	GetClientRect(hwnd, &rt);
	sprintf_s(buf, "Размер окна %d на %d пикселей", rt.right, rt.bottom);
	TextOutA(hdc, 10, 10, buf, strlen(buf));
	a = check_borders(ppt, rt.right, rt.bottom);
	if (a != 0) return a;
	Polyline(hdc, ppt, 5);
	return 0;
}
int figure(HWND hwnd, HDC hdc, POINT *ppt)
{
	int a;
	RECT rt;
	char buf[100];
	GetClientRect(hwnd, &rt);
	sprintf_s(buf, "Размер окна %d на %d пикселей", rt.right, rt.bottom);
	TextOutA(hdc, 10, 10, buf, strlen(buf));
	a = check_borders(ppt, rt.right, rt.bottom);
	if (a != 0) return a;
	Polygon(hdc, ppt, 4);
	return 0;
}
int FinF(HWND hwnd, HDC hdc, POINT *ppt, POINT *ppt2, HBRUSH brush, HPEN pen)
{
	int a, i;
	RECT rt;
	char buf[100];
	GetClientRect(hwnd, &rt);
	sprintf_s(buf, "Размер окна %d на %d пикселей", rt.right, rt.bottom);
	TextOutA(hdc, 10, 10, buf, strlen(buf));
	a = check_borders(ppt, rt.right, rt.bottom);
	if (a != 0) return a;
	a = check_borders(ppt2, rt.right, rt.bottom);
	if (a != 0) return a;
	for (i = 0; i < 4; i++)
	{
		if (check_FinF(ppt[i], ppt[i + 1], ppt2) == 0) return outside_figure;
	}
	Polygon(hdc, ppt, 4);
	SelectBrush(hdc, brush);
	SelectPen(hdc, pen);
	Polygon(hdc, ppt2, 4);
	return 0;
}
void main()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	char a;
	int i, exitFlag = 0, error, error2=0, penColour[2][3], brushColour[2][3];
	POINT ppt[5], ppt2[5];
	setlocale(LC_CTYPE, "Russian");
	FILE *fp;
	fp = fopen("ok.txt", "r");
	for (i = 0; i < 4; i++)
	{
		fscanf_s(fp, "%d %d", &ppt[i].x, &ppt[i].y);
		if (ppt[i].x < 0 || ppt[i].y < 0) error2 = 1;
	}
	ppt[4].x = ppt[0].x;
	ppt[4].y = ppt[0].y;
	error = check_figure(ppt);
	if (error == 0 && error2==0)
	{
		for (i = 0; i < 3; i++)
		{
			fscanf_s(fp, "%d", &penColour[0][i]);
		}
		for (i = 0; i < 3; i++)
		{
			fscanf_s(fp, "%d", &brushColour[0][i]);
		}
		for (i = 0; i < 4; i++)
		{
			fscanf_s(fp, "%d %d", &ppt2[i].x, &ppt2[i].y);
			if (ppt[i].x < 0 || ppt[i].y < 0) error2 = 1;
		}
		ppt2[4].x = ppt2[0].x;
		ppt2[4].y = ppt2[0].y;
		error = check_figure(ppt2);
		if (error == 0 && error == 0)
		{
			for (i = 0; i < 3; i++)
			{
				fscanf_s(fp, "%d", &penColour[1][i]);
			}
			for (i = 0; i < 3; i++)
			{
				fscanf_s(fp, "%d", &brushColour[1][i]);
			}
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(255, 0, 0));
			HPEN hPen = CreatePen(PS_SOLID, 3, RGB(penColour[0][0], penColour[0][1], penColour[0][2]));
			HPEN hPen2 = CreatePen(PS_SOLID, 3, RGB(penColour[1][0], penColour[1][1], penColour[1][2]));
			HPEN hOldPen = SelectPen(hdc, hPen);
			HBRUSH hBrush = CreateSolidBrush(RGB(brushColour[0][0], brushColour[0][1], brushColour[0][2]));
			HBRUSH hBrush2 = CreateSolidBrush(RGB(brushColour[1][0], brushColour[1][1], brushColour[1][2]));
			HBRUSH hOldBrush = SelectBrush(hdc, hBrush);
			do {
				printf("<1> - построить контур 1-й фигуры\n");
				printf("<2> - построить 1-ую фигуру\n");
				printf("<3> - построить две фигуры\n");
				printf("<ESC> - завершение программы\n\n");
				int repeatFlag = 0;
				do {
					a = _getch();
					switch (a)
					{
					case '1':
						SelectBrush(hdc, hBrush);
						SelectPen(hdc, hPen);
						if (line(hwnd, hdc, ppt) != 0)
							printf("Часть фигуры лежит за границами окна\n");
						break;
					case '2':
						SelectBrush(hdc, hBrush);
						SelectPen(hdc, hPen);
						if (figure(hwnd, hdc, ppt) != 0)
							printf("Часть фигуры лежит за границами окна\n");
						break;
					case '3':
						SelectBrush(hdc, hBrush);
						SelectPen(hdc, hPen);
						error = FinF(hwnd, hdc, ppt, ppt2, hBrush2, hPen2);
						if (error == 1)
							printf("Часть фигуры лежит за границами окна\n");
						if (error == 4)
							printf("Одна фигура не входит в другую\n");
						break;
					case 27:
						exitFlag = 1;
						break;
					default: printf("ОШИБКА: неверный номер команды\n");
						repeatFlag = 1;
					}
				} while (!repeatFlag && !exitFlag);
			} while (!exitFlag);
			ReleaseDC(hwnd, hdc);
		}
		else
		{
			if (error2 == 1) printf("Неверные координаты");
			else printf("Вторая фигура не является ромбом.");
			_getch();
		}
	}
	else
	{
		if (error2 == 1) printf("Неверные координаты");
		else printf("Первая фигура не является ромбом.");
		_getch();
	}
}