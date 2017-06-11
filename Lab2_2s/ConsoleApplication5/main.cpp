#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include "Operations.h"
void main(){
	setlocale(LC_CTYPE, "Russian");
	int k, showmenu = 1, exitFlag = 0, b;
	char a;
	queue s;
	Ochistka(&s);
	do {
		if (showmenu){
			printf("<1> - поместить элемент в очередь\n");
			printf("<2> - извлечь элемент из очереди\n");
			printf("<3> - очистить очередь\n");
			printf("<4> - пуста ли очередь?\n");
			printf("<5> - показать содержимое очереди\n");
			printf("<m> - показать меню\n");
			printf("<e> - завершение программы\n");
		}
		int repeatFlag = 0;
		showmenu = 0;
		do{
			a = _getch();
			switch (a)
			{
			case '1': 
				printf("Введите элемент:\n");
				scanf_s("%d", &b);
				if (input(b, &s) == 0) printf("Не удалось поместить элемент в очередь\n");
				else printf("Элемент помещен в очередь: %d\n", b);
				break;
			case '2': 
				if (output(&s, k) == 0) printf("Не удалось взять элемент из очереди\n");
				else printf("Взят элемент: '%d'\n", k);
				break;
			case '3': {
				Ochistka(&s);
				printf("Очередь очищена\n"); }
				break;
			case '4': {
				if (Pusta(&s) == 1) printf("Очередь пуста\n");
				else printf("Очередь не пуста\n");
			}  break;
			case '5': 
				if (show(s) == 0) printf("Очередь пуста\n");
				break;
			case 'm': 
				showmenu = 1;
				repeatFlag = 1;
				break;
			case 'e': 
				exitFlag = 1;
				break;
			default: printf("ОШИБКА: неверный номер команды\n");
				repeatFlag = 1;
			}
		} while (!repeatFlag && !exitFlag);
	} while (!exitFlag);
}