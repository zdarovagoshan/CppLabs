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
			printf("<1> - ��������� ������� � �������\n");
			printf("<2> - ������� ������� �� �������\n");
			printf("<3> - �������� �������\n");
			printf("<4> - ����� �� �������?\n");
			printf("<5> - �������� ���������� �������\n");
			printf("<m> - �������� ����\n");
			printf("<e> - ���������� ���������\n");
		}
		int repeatFlag = 0;
		showmenu = 0;
		do{
			a = _getch();
			switch (a)
			{
			case '1': 
				printf("������� �������:\n");
				scanf_s("%d", &b);
				if (input(b, &s) == 0) printf("�� ������� ��������� ������� � �������\n");
				else printf("������� ������� � �������: %d\n", b);
				break;
			case '2': 
				if (output(&s, k) == 0) printf("�� ������� ����� ������� �� �������\n");
				else printf("���� �������: '%d'\n", k);
				break;
			case '3': {
				Ochistka(&s);
				printf("������� �������\n"); }
				break;
			case '4': {
				if (Pusta(&s) == 1) printf("������� �����\n");
				else printf("������� �� �����\n");
			}  break;
			case '5': 
				if (show(s) == 0) printf("������� �����\n");
				break;
			case 'm': 
				showmenu = 1;
				repeatFlag = 1;
				break;
			case 'e': 
				exitFlag = 1;
				break;
			default: printf("������: �������� ����� �������\n");
				repeatFlag = 1;
			}
		} while (!repeatFlag && !exitFlag);
	} while (!exitFlag);
}