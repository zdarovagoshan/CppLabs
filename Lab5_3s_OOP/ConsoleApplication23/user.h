#include <stdio.h>
#include "romb.h"
#include "rombStack.h"
#include "colors.h"
#include <fstream>
#include <iostream>

void printMenu(bool extended)
{
	header();
	printf_s("�������� ��������:\n");
	items();
	printf_s("[1] - ��������� ������ �� �����\n");
	printf_s("[2] - ������ ���� ����� � ��� ����������� ���������� � ����\n");
	if (!extended) grayed();
	printf_s("[3] - ��������� ������ � ����\n");
	printf_s("[4] - ������� ���� �� �����\n");
	printf_s("[5] - ���������� ���� �� ������\n");
	printf_s("[6] - ����� ������\n");
	printf_s("[7] - ���������� ����\n");
	items();
	printf_s("[m] - �������� ����\n");
	printf_s("[esc] - ����� �� ���������\n");
	plain();
}