#include <stdio.h>
#include "romb.h"
#include "colors.h"
#include <fstream>
#include <iostream>

void PrintMenu(unsigned __int8 flags)
{
	using namespace std;
	header();
	cout << "Выберите действие:" << endl;
	items();
	cout << "[1] - Задать новую фигуру" << endl;
	cout << "[2] - Загрузить новую фигуру" << endl;
	if (!(flags & 0x01)) grayed();
	cout << "[3] - Изменить фигуру" << endl;
	cout << "[7] - Сохранить фигуру в файл" << endl;
	if (!(flags & 0x02)) grayed();
	cout << "[4] - Нарисовать фигуру-контур" << endl;
	if (!(flags & 0x04)) grayed();
	cout << "[5] - Нарисовать фигуру с заливкой" << endl;
	if (!(flags & 0x08)) grayed();
	cout << "[6] - Нарисовать фигуру с полостью" << endl;
	items();
	cout << "[m]- Показать меню" << endl;
	cout << "[ESC] - Выход" << endl;
	plain();
}

void EditMenu(unsigned __int8 flags)
{
	using namespace std;
	header();
	cout << "\tВыберите действие:" << endl;
	items();
	cout << "\t[1] - Изменить контур" << endl;
	cout << "\t[2] - Изменить заливку" << endl;
	cout << "\t[4] - Переместить фигуру" << endl;
	if (!(flags & 0x04)) grayed();
	cout << "\t[3] - Изменить полость" << endl;
	items();
	cout << "\t[ESC] - Отмена" << endl;
	plain();
}