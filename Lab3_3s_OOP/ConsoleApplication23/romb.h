#ifndef ROMB
#define ROMB
#include <windows.h> 
#include <stdio.h>

//���� ������
#define OUTSIDE_BORDERS "������ �� ��������� ����\n"
#define NEG_VALUE "�������� �������� ������� ����\n"
#define WRONG_PARALLEL "��������������� ������� �� �����������\n"
#define IO_ERR "���� �� ���������� ��� �������� �������� ������ ������\n"
#define TYPE_ERR "������� ������ ��� ������� ��� �������\n"
#define RGB_ERR "������� ����� ���� ������� ��� �������\n"
#define WRONG_DLINA "����� ������ �� �����\n"

struct color { int r, g, b; };

class romb
{
private:
	POINT t[4];
	color pcolor, bcolor;
	int ptype, btype;
	int width;
public:
	void SetPos(int new_x, int new_y);
	void SetFigure(POINT* new_t);
	void SetPStyle(int new_ptype, int new_width, color new_pcolor);
	void SetBStyle(int new_btype, color new_bcolor);

	POINT* GetCoord();
	int* GetPchar();
	int* GetBchar();

	float slope(POINT a, POINT b);
	void check_figure(POINT *ppt);
	void check_borders(POINT *ppt);

	void draw();
	void load(FILE *fptr);
	void save(FILE *fptr);
};
#endif