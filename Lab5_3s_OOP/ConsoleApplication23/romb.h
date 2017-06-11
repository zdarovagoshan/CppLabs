#ifndef ROMB
#define ROMB
#include <windows.h> 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

//коды ошибок
#define OUTSIDE_BORDERS "Фигура за границами окна\n"
#define NEG_VALUE "Неверное значение толщины пера\n"
#define WRONG_PARALLEL "Противоположные стороны не параллельны\n"
#define IO_ERR "Файл не существует или содержит неверный формат данных\n"
#define TYPE_ERR "Неверно указан тип границы или заливки\n"
#define RGB_ERR "Неверно задан цвет границы или заливки\n"
#define WRONG_DLINA "Длины сторон не равны\n"
#define OVERLAP "Внутренняя фигура больше или вне основной\n"
#define EMPTY_SLOT "Не задана фигура, с которой вы хотели бы работать. Для продолжения нарисуйте интересующую вас фигуру.\n"

struct color { int r, g, b; };

class shape
{
public:
	shape() {};

	virtual void draw() = 0;
	virtual void erase() = 0;
	virtual void SetPos(int new_x, int new_y) = 0;
	virtual void save(FILE *fptr) = 0;
	virtual void load(FILE *fptr) = 0;
};

class romb : public shape
{
protected:
	POINT t[5];
	int type, width;
	color col;
public:
	romb();
	romb(POINT* new_t);

	void SetFigure(POINT *new_t);
	inline void SetFrameStyle(int new_type, int new_width, color new_color) { type = new_type; width = new_width; col = new_color; };
	virtual void SetPos(int new_x, int new_y);

	inline POINT* GetFrameCoord() { return t; };
	inline int GetFrameType() { return type; };
	inline int GetFrameWidth() { return width; };
	inline color GetFrameColor() { return col; };

	float slope(POINT a, POINT b);
	void check_figure(POINT *ppt);
	void check_borders(POINT *ppt);
	void validate(POINT*tk, int type, int width, color col);

	virtual void draw();
	virtual void erase();
	virtual void save(FILE *fptr);
	virtual void load(FILE *fptr);
};

class RbFill
{
protected:
	int type;
	color col;
public:
	RbFill() { type = -1; col.r = 0; col.g = 0; col.b = 0; };
	RbFill(int new_type, color new_col);

	void SetFillStyle(int new_type, color new_col);

	inline int GetFillType() { return type; };
	inline color GetFillColor() { return col; };
};

class SolidRomb : public romb, public RbFill
{
public:
	void operator =(romb sq);
	void operator =(RbFill F);
	void validate(POINT*tk, int type, int width, color col, int ftype, color fcol);

	virtual void SetPos(int new_x, int new_y);
	virtual void draw();
	virtual void erase();
	virtual void save(FILE *fptr);
	virtual void load(FILE *fptr);
};

class HollowRomb : public SolidRomb
{
protected:
	POINT tin[5];
public:
	HollowRomb();
	int check_FinF(POINT m1, POINT m2, POINT *n);
	void operator =(RbFill F);
	void operator =(romb sq);
	void operator =(SolidRomb sq);
	void validate(POINT*tk, int type, int width, color col, int ftype, color fcol, POINT*tkin);
	
	void SetInnerFigure(POINT *new_t);
	inline POINT* GetInnerCoord() { return tin; };

	virtual void SetPos(int new_x, int new_y);
	virtual void draw();
	virtual void erase();
	virtual void save(FILE *fptr);
	virtual void load(FILE *fptr);
};
#endif