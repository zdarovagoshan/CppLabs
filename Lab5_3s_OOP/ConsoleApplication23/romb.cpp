#define _CRT_SECURE_NO_WARNINGS
#include <windows.h> 
#include <windowsx.h>
#include "romb.h"
#include <iostream>
#include <fstream>
#include <stdio.h>



HWND hwnd = GetConsoleWindow();
RECT rt;

//SHAPE-------------------------------------------------------------

//ROMB------------------------------------------------------------
romb::romb()
{
	t[0].x = 0; t[1].x = 10; t[2].x = 10; t[3].x = 0; t[4].x = t[0].x;
	t[0].y = 0; t[1].y = 0; t[2].y = 10; t[3].y = 10; t[4].y = t[0].y;
	type = 0; width = 1; col.r = 0; col.g = 0; col.b = 0;
};

romb::romb(POINT *new_t)
{
	int i;
	for (i = 0; i < 4; i++) {
		t[i].x = new_t[i].x; t[i].y = new_t[i].y;
	}
	t[4].x = t[0].x; t[4].y = t[0].y;
	type = 0; width = 1; col.r = 128; col.g = 128; col.b = 128;
}

//функция проверки на пренадлежность классу "romb"
void romb::validate(POINT*tk, int type, int width, color col)
{
	GetClientRect(hwnd, &rt);
	check_borders(t);
	check_figure(t);
	if (type < 0 || type > 6) throw TYPE_ERR;
	if (width < 0 || width > 6) throw NEG_VALUE;
	if (col.r < 0 || col.r > 255) throw RGB_ERR;
	if (col.g < 0 || col.g > 255) throw RGB_ERR;
	if (col.b < 0 || col.b > 255) throw RGB_ERR;
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

void romb::SetFigure(POINT *new_t)
{
	for (int i = 0; i < 4; i++) {
		t[i].x = new_t[i].x; t[i].y = new_t[i].y;
	}
	t[4].x = t[0].x; t[4].y = t[0].y;
}

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

//рисование ромба
void romb::draw()
{
	HDC hdc = GetDC(hwnd);
	COLORREF BG = RGB(0, 0, 0);
	HPEN pen = CreatePen(type, width, RGB(col.r, col.g, col.b));
	HBRUSH brush = GetStockBrush(NULL_BRUSH);

	SetBkColor(hdc, BG);
	SelectPen(hdc, pen);
	SelectBrush(hdc, brush);
	Polygon(hdc, t, 4);
	DeletePen(pen);
	ReleaseDC(hwnd, hdc);
}

void romb::erase()
{
	HDC hdc = GetDC(hwnd);
	COLORREF BG = RGB(0, 0, 0);
	HPEN pen = CreatePen(PS_SOLID, width, BG);
	HBRUSH brush = GetStockBrush(NULL_BRUSH);

	SelectPen(hdc, pen); SelectBrush(hdc, brush);
	Polygon(hdc, t, 4);
	ReleaseDC(hwnd, hdc);
}

void romb::save(FILE *fptr)
{
	fprintf(fptr, "%d %d %d %d %d %d %d %d; %d %d (%d, %d, %d)\n", t[0].x, t[0].y, t[1].x, t[1].y, t[2].x, t[2].y, t[3].x, t[3].y, type, width, col.r, col.g, col.b);
}

void romb::load(FILE *fptr)
{
	GetClientRect(hwnd, &rt);
	POINT tk[5];
	int type, twidth;
	color tcol;
	if (!fptr) throw IO_ERR;
	if (!fscanf(fptr, "%d %d %d %d %d %d %d %d; ", &tk[0].x, &tk[0].y, &tk[1].x, &tk[1].y, &tk[2].x, &tk[2].y, &tk[3].x, &tk[3].y)) throw IO_ERR;
	tk[4] = tk[0];
	if (!fscanf(fptr, "%d %d (%d, %d, %d)\n", &type, &twidth, &tcol.r, &tcol.g, &tcol.b)) throw IO_ERR;
	validate(tk, type, twidth, tcol);
	SetFigure(tk);
	SetFrameStyle(type, twidth, tcol);
}


//FILL-------------------------------------------------------------
RbFill::RbFill(int new_type, color new_col)
{
	type = new_type; col = new_col;
}

void RbFill::SetFillStyle(int new_type, color new_col)
{
	type = new_type; col = new_col;
}

//SOLIDSQUARE-------------------------------------------------------
void SolidRomb::validate(POINT*tk, int type, int width, color col, int ftype, color fcol)
{
	romb::validate(tk, type, width, col);

	if (ftype < -1 || ftype > 5) throw TYPE_ERR;
	if (fcol.r < 0 || fcol.r > 255) throw RGB_ERR;
	if (fcol.g < 0 || fcol.g > 255) throw RGB_ERR;
	if (fcol.b < 0 || fcol.b > 255) throw RGB_ERR;
}

void SolidRomb::operator =(romb sq)
{
	POINT*k=sq.GetFrameCoord();
	for (int i = 0; i < 5; i++) 
	{
		t[i] = k[i];
	}
	SetFrameStyle(sq.GetFrameType(), sq.GetFrameWidth(), sq.GetFrameColor());
}

void SolidRomb::operator =(RbFill F)
{
	SetFillStyle(F.GetFillType(), F.GetFillColor());
}

//функция перемещения фигуры
void SolidRomb::SetPos(int new_x, int new_y)
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

void SolidRomb::draw()
{
	HDC hdc = GetDC(hwnd);
	COLORREF BG = RGB(0, 0, 0);
	HPEN pen = CreatePen(romb::type, width, RGB(romb::col.r, romb::col.g, romb::col.b));
	HBRUSH brush;
	if (RbFill::type == -1)
		brush = CreateSolidBrush(RGB(RbFill::col.r, RbFill::col.g, RbFill::col.b));
	else
		brush = CreateHatchBrush(RbFill::type, RGB(RbFill::col.r, RbFill::col.g, RbFill::col.b));
	SetBkColor(hdc, BG);
	SelectPen(hdc, pen); 
	SelectBrush(hdc, brush);
	Polygon(hdc, t, 4);
	DeletePen(pen); 
	ReleaseDC(hwnd, hdc);
}

void SolidRomb::erase()
{
	HDC hdc = GetDC(hwnd);
	COLORREF BG = RGB(0, 0, 0);
	HPEN pen = CreatePen(PS_SOLID, width, BG);
	HBRUSH brush = GetStockBrush(BLACK_BRUSH);

	SelectPen(hdc, pen); SelectBrush(hdc, brush);
	Polygon(hdc, t, 4);
	ReleaseDC(hwnd, hdc);
}

void SolidRomb::save(FILE *fptr)
{
	fprintf(fptr, "%d %d %d %d %d %d %d %d; %d %d (%d, %d, %d) %d (%d, %d, %d) \n", t[0].x, t[0].y, t[1].x, t[1].y, t[2].x, t[2].y, t[3].x, t[3].y, romb::type, width, romb::col.r, romb::col.g, romb::col.b, RbFill::type, RbFill::col.r, RbFill::col.g, RbFill::col.b);
}

void SolidRomb::load(FILE *fptr)
{
	GetClientRect(hwnd, &rt);
	POINT tk[5];
	if (!fptr) throw IO_ERR;
	if (!fscanf(fptr, "%d %d %d %d %d %d %d %d; ", &tk[0].x, &tk[0].y, &tk[1].x, &tk[1].y, &tk[2].x, &tk[2].y, &tk[3].x, &tk[3].y)) throw IO_ERR;
	tk[4] = tk[0];
	int type, ftype, width;
	color col, fcol;
	if (!fscanf(fptr, "%d %d (%d, %d, %d) ", &type, &width, &col.r, &col.g, &col.b)) throw IO_ERR;
	if (!fscanf(fptr, "%d (%d, %d, %d)\n", &ftype, &fcol.r, &fcol.g, &fcol.b)) throw IO_ERR;
	validate(tk, type, width, col, ftype, fcol);
	SetFigure(tk);
	SetFrameStyle(type, width, col);
	SetFillStyle(ftype, fcol);
}

//HOLLOWSQUARE-----------------------------------------------------------
HollowRomb::HollowRomb()
{
	for (int i = 0; i < 4; i++)
	{
		tin[i] = t[i];
	}
	tin[4] = tin[0];
};

int HollowRomb::check_FinF(POINT m1, POINT m2, POINT *n)
{
	int k = 0, z;
	for (int i = 0; i < 4; i++)
	{
		z = (n[i].x - m1.x)*(m2.y - m1.y) - (n[i].y - m1.y)*(m2.x - m1.x);
		if (z < 0) k++;
		else return 0;
	}
	return k;
}

void HollowRomb::validate(POINT*tk, int type, int width, color col, int ftype, color fcol, POINT*tkin)
{
	SolidRomb::validate(tk, type, width, col, ftype, fcol);
	//check_figure(tkin);
	for (int i = 0; i < 4; i++)
	{
		if (check_FinF(tin[i], tin[i + 1], t) != 0) throw OVERLAP;
	}
}

void HollowRomb::operator =(RbFill F)
{
	SetFillStyle(F.GetFillType(), F.GetFillColor());
}

void HollowRomb::operator =(romb sq)
{
	POINT*k = sq.GetFrameCoord();
	for (int i = 0; i < 5; i++)
	{
		t[i] = k[i];
	}
	SetFrameStyle(sq.GetFrameType(), sq.GetFrameWidth(), sq.GetFrameColor());
}

void HollowRomb::operator =(SolidRomb sq)
{
	POINT*k = sq.GetFrameCoord();
	for (int i = 0; i < 5; i++)
	{
		t[i] = k[i];
	}
	SetFrameStyle(sq.GetFrameType(), sq.GetFrameWidth(), sq.GetFrameColor());
	SetFillStyle(sq.GetFillType(), sq.GetFillColor());
}

void HollowRomb::SetPos(int new_x, int new_y) 
{ 
	int i;
	GetClientRect(hwnd, &rt);
	for (i = 0; i < 4; i++)
	{
		if (t[i].x + new_x < 0 || t[i].x + new_x > rt.right || t[i].y + new_y < 0 || t[i].y + new_y > rt.bottom) throw OUTSIDE_BORDERS;
	}
	for (i = 0; i < 4; i++)
	{
		tin[i].x += new_x;
		tin[i].y += new_y;
	}
	for (i = 0; i < 4; i++) 
	{
		t[i].x += new_x;
		t[i].y += new_y;
	}
}

void HollowRomb::SetInnerFigure(POINT *new_t) 
{
	for (int i = 0; i < 4; i++) {
		tin[i].x = new_t[i].x; tin[i].y = new_t[i].y;
	}
	tin[4].x = tin[0].x; tin[4].y = tin[0].y;
}

void HollowRomb::draw()
{
	HDC hdc = GetDC(hwnd);
	COLORREF BG = RGB(0, 0, 0);
	HPEN pen = CreatePen(romb::type, width, RGB(romb::col.r, romb::col.g, romb::col.b));
	HBRUSH brush, wbrush = GetStockBrush(BLACK_BRUSH);
	if (RbFill::type == -1)
		brush = CreateSolidBrush(RGB(RbFill::col.r, RbFill::col.g, RbFill::col.b));
	else
		brush = CreateHatchBrush(RbFill::type, RGB(RbFill::col.r, RbFill::col.g, RbFill::col.b));
	SetBkColor(hdc, BG);
	SelectPen(hdc, pen); SelectBrush(hdc, brush);
	Polygon(hdc, t, 4);

	SelectBrush(hdc, wbrush);
	Polygon(hdc, tin, 4);

	DeletePen(pen); ReleaseDC(hwnd, hdc);
}

void HollowRomb::erase()
{
	HDC hdc = GetDC(hwnd);
	COLORREF BG = RGB(0, 0, 0);
	HPEN pen = CreatePen(PS_SOLID, width, BG);
	HBRUSH brush = GetStockBrush(BLACK_BRUSH);

	SelectPen(hdc, pen); SelectBrush(hdc, brush);
	Polygon(hdc, t, 4);
	ReleaseDC(hwnd, hdc);
}

void HollowRomb::save(FILE *fptr)
{
	fprintf(fptr, "%d %d %d %d %d %d %d %d; %d %d (%d, %d, %d) %d (%d, %d, %d) \n", t[0].x, t[0].y, t[1].x, t[1].y, t[2].x, t[2].y, t[3].x, t[3].y, romb::type, width, romb::col.r, romb::col.g, romb::col.b, RbFill::type, RbFill::col.r, RbFill::col.g, RbFill::col.b);
	fprintf(fptr, "%d %d %d %d %d %d %d %d\n", tin[0].x, tin[0].y, tin[1].x, tin[1].y, tin[2].x, t[2].y, t[3].x, t[3].y);
}

void HollowRomb::load(FILE *fptr)
{
	GetClientRect(hwnd, &rt);
	POINT tk[5], tki[5];
	if (!fptr) throw IO_ERR;
	if (!fscanf(fptr, "%d %d %d %d %d %d %d %d; ", &tk[0].x, &tk[0].y, &tk[1].x, &tk[1].y, &tk[2].x, &tk[2].y, &tk[3].x, &tk[3].y)) throw IO_ERR;
	tk[4] = tk[0];
	int type,ftype, width;
	color col, fcol;
	if (!fscanf(fptr, "%d %d (%d, %d, %d) ", &type, &width, &col.r, &col.g, &col.b)) throw IO_ERR;
	if (!fscanf(fptr, "%d (%d, %d, %d)", &ftype, &fcol.r, &fcol.g, &fcol.b)) throw IO_ERR;
	if (!fscanf(fptr, "%d %d %d %d %d %d %d %d\n", &tki[0].x, &tki[0].y, &tki[1].x, &tki[1].y, &tki[2].x, &tki[2].y, &tki[3].x, &tki[3].y)) throw IO_ERR;
	tki[4] = tk[0];
	validate(tk, type, width, col, ftype, fcol, tki);
	SetFigure(tk);
	SetFrameStyle(type, width, col);
	SetFillStyle(ftype, fcol);
	SetInnerFigure(tki);
}
	
	
	
	
	


