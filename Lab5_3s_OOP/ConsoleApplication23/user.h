#include <stdio.h>
#include "romb.h"
#include "rombStack.h"
#include "colors.h"
#include <fstream>
#include <iostream>

void printMenu(bool extended)
{
	header();
	printf_s("Выберите действие:\n");
	items();
	printf_s("[1] - загрузить данные из файла\n");
	printf_s("[2] - ручной ввод ромба и его последующее добавление в стек\n");
	if (!extended) grayed();
	printf_s("[3] - сохранить данные в файл\n");
	printf_s("[4] - удалить ромб из стека\n");
	printf_s("[5] - отобразить ромб из памяти\n");
	printf_s("[6] - поиск фигуры\n");
	printf_s("[7] - отобразить стек\n");
	items();
	printf_s("[m] - показать меню\n");
	printf_s("[esc] - выход из программы\n");
	plain();
}