#define _CRT_SECURE_NO_WARNINGS
#include <windows.h> 
#include <windowsx.h>
#include "romb.h"
#include <iostream>

//коды ошибок
#define OUTSIDE_BORDERS 1
#define NEG_VALUE 2
#define WRONG_PARALLEL 3
#define IO_ERR 4
#define TYPE_ERR 5
#define RGB_ERR 6
#define WRONG_DLINA 7

HWND hwnd = GetConsoleWindow();
RECT rt;

//функция перемещения фигуры
void romb::SetPos(int new_x, int new_y)
{
	int i;
	GetClientRect(hwnd, &rt);
	for (i = 0; i < 4; i++)
	{
		if (t[i].x + new_x < 0 || t[i].x + new_x > rt.right || t[i].y + new_y < 0 || t[i].y + new_y > rt.bottom) throw OUTSIDE_BORDERS;
	}
	for (i = 0; i < 4; i++)
	{
		t[i].x += new_x;
		t[i].y += new_y;
	}
}

//функция присваивания значения новых координат вершин
void romb::SetFigure(POINT* new_t) 
{
	int i;
	for (i = 0; i < 4; i++) {
		t[i].x = new_t[i].x; t[i].y = new_t[i].y;
	}
}

//функция вычисляющая коэффициент наклона прямой
float romb::slope(POINT a, POINT b)
{
	if ((b.x - a.x) != 0)
		return (b.y - a.y) / (b.x - a.x);
	else return 3000;
}

//функция проверки фигуры(является ли ромбом)
void romb::check_figure(POINT *ppt)
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
		if (dl[i] != dl[i + 1] || dl[i] == 0) throw WRONG_DLINA;
	}
	for (i = 0; i < 2; i++)
	{
		if (koef[i] != koef[i + 2]) throw WRONG_PARALLEL;
	}
}

//функция проверки выхода фигуры за границы окна
void romb::check_borders(POINT *ppt)
{
	GetClientRect(hwnd, &rt);
	int i;
	for (i = 0; i < 4; i++)
	{
		if (ppt[i].x >= rt.right || ppt[i].y >= rt.bottom || ppt[i].x<0 || ppt[i].y<0) throw OUTSIDE_BORDERS;
	}
}

//Получение координат фигуры
POINT* romb::GetCoord() 
{ 
	return t; 
}

//характеристик пера
int* romb::GetPchar()
{
	int a[5];
	a[2] = pcolor.r;
	a[3] = pcolor.g;
	a[4] = pcolor.b;
	a[0] = ptype;
	a[1] = width;
	return a;
}

//характеристик кисти
int* romb::GetBchar()
{
	int a[4];
	a[0] = bcolor.r;
	a[1] = bcolor.g;
	a[2] = bcolor.b;
	a[3] = btype;
	return a;
}

//установка стиля пера
void romb::SetPStyle(int new_ptype, int new_width, color new_pcolor)
{
	if (new_ptype < 0 || new_ptype > 6) throw TYPE_ERR;
	if (new_width < 0) throw NEG_VALUE;
	if (new_pcolor.r < 0 || new_pcolor.r > 255) throw RGB_ERR;
	if (new_pcolor.g < 0 || new_pcolor.g > 255) throw RGB_ERR;
	if (new_pcolor.b < 0 || new_pcolor.b > 255) throw RGB_ERR;
	ptype = new_ptype;
	width = new_width;
	pcolor = new_pcolor;
}

//установка стиля кисти
void romb::SetBStyle(int new_btype, color new_bcolor)
{
	if (new_btype < -2 || new_btype > 5) throw TYPE_ERR;
	if (new_bcolor.r < 0 || new_bcolor.r > 255) throw RGB_ERR;
	if (new_bcolor.g < 0 || new_bcolor.g > 255) throw RGB_ERR;
	if (new_bcolor.b < 0 || new_bcolor.b > 255) throw RGB_ERR;
	btype = new_btype;
	bcolor = new_bcolor;
}

//рисование ромба
void romb::draw()
{
	HDC hdc = GetDC(hwnd);
	COLORREF BG = GetPixel(hdc, 10, 10);
	HPEN pen = CreatePen(ptype, width, RGB(pcolor.r, pcolor.g, pcolor.b));
	HBRUSH brush;

	if (btype == -2) brush = GetStockBrush(NULL_BRUSH);
	else
		if (btype == -1) brush = CreateSolidBrush(RGB(bcolor.r, bcolor.g, bcolor.b));
		else brush = CreateHatchBrush(btype, RGB(bcolor.r, bcolor.g, bcolor.b));

		SetBkColor(hdc, BG);
		SelectPen(hdc, pen);
		SelectBrush(hdc, brush);
		Polygon(hdc, t, 4);
		ReleaseDC(hwnd, hdc);
}

//загрузка фигуры из файла
void romb::load(char *fname)
{
	GetClientRect(hwnd, &rt);
	POINT tk[5];
	FILE *fptr = fopen(fname, "r");
	if (!fptr) throw IO_ERR;
	if (!fscanf(fptr, "%d %d %d %d %d %d %d %d; ", &tk[0].x, &tk[0].y, &tk[1].x, &tk[1].y, &tk[2].x, &tk[2].y, &tk[3].x, &tk[3].y)) throw IO_ERR;
	tk[4] = tk[0];
	check_figure(tk);
	check_borders(tk);
	SetFigure(tk);
	int type, twidth;
	color tcol;
	if (!fscanf(fptr, "%d %d (%d, %d, %d) ", &type, &twidth, &tcol.r, &tcol.g, &tcol.b)) throw IO_ERR;
	SetPStyle(type, twidth, tcol);

	if (!feof(fptr))
	{
		if (!fscanf(fptr, "%d (%d, %d, %d)", &type, &tcol.r, &tcol.g, &tcol.b)) throw IO_ERR;
		SetBStyle(type, tcol);
	}
	else SetBStyle(-2, tcol);
	fclose(fptr);
}

//сохранение фигуры в файл
void romb::save(char *fname)
{
	POINT*k=GetCoord();
	printf("%d %d %d %d %d %d %d %d; ", k[0].x, k[0].y, k[1].x, k[1].y, k[2].x, k[2].y, k[3].x, k[3].y);
	int*p = GetPchar();
	printf("%d %d (%d, %d, %d) ", p[0], p[1], p[2], p[3], p[4]);
	int*b = GetBchar();
	printf("%d (%d, %d, %d) ", b[0], b[1], b[2], b[3]);
	FILE *fptr = fopen(fname, "w");
	if (!fptr) throw IO_ERR;
	fprintf(fptr, "%d %d %d %d %d %d %d %d; ", t[0].x, t[0].y, t[1].x, t[1].y, t[2].x, t[2].y, t[3].x, t[3].y);
	fprintf(fptr, "%d %d (%d, %d, %d) ", ptype, width, pcolor.r, pcolor.g, pcolor.b);
	if (btype != -2) fprintf(fptr, "%d (%d, %d, %d)", btype, bcolor.r, bcolor.g, bcolor.b);
	fclose(fptr);
}