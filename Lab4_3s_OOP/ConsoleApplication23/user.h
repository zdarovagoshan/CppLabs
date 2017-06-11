#include <stdio.h>
#include "romb.h"
#include "colors.h"
#include <fstream>
#include <iostream>

void PrintMenu(unsigned __int8 flags)
{
	using namespace std;
	header();
	cout << "�������� ��������:" << endl;
	items();
	cout << "[1] - ������ ����� ������" << endl;
	cout << "[2] - ��������� ����� ������" << endl;
	if (!(flags & 0x01)) grayed();
	cout << "[3] - �������� ������" << endl;
	cout << "[7] - ��������� ������ � ����" << endl;
	if (!(flags & 0x02)) grayed();
	cout << "[4] - ���������� ������-������" << endl;
	if (!(flags & 0x04)) grayed();
	cout << "[5] - ���������� ������ � ��������" << endl;
	if (!(flags & 0x08)) grayed();
	cout << "[6] - ���������� ������ � ��������" << endl;
	items();
	cout << "[m]- �������� ����" << endl;
	cout << "[ESC] - �����" << endl;
	plain();
}

void EditMenu(unsigned __int8 flags)
{
	using namespace std;
	header();
	cout << "\t�������� ��������:" << endl;
	items();
	cout << "\t[1] - �������� ������" << endl;
	cout << "\t[2] - �������� �������" << endl;
	cout << "\t[4] - ����������� ������" << endl;
	if (!(flags & 0x04)) grayed();
	cout << "\t[3] - �������� �������" << endl;
	items();
	cout << "\t[ESC] - ������" << endl;
	plain();
}