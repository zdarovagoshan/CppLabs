#include "create.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <locale.h>

void main(){
	setlocale(LC_CTYPE, "Russian");
	int n, i, j;
	unsigned long long answer;
	unsigned long long *group=new unsigned long long[10];    //������ � ������� �������� ���������� ������ ������� ���� ������������ (����� 10 �����)
	printf("������� ���������� ������: ");
	scanf_s("%d", &n);

	//�������� ������������ ��������� ������ � 4 ������� � N ��������� ������� ��������
	for (i = 0; i < 10; i++){
		group[i] = 0;
	}
	createSetGraphs(group, n);
	answer = 0;
	i = 0;
	printf("���������� ������ ������� ����: \n");
	while (group[i] != 0 && i<10){
		j = i+1;
		printf("%llu ", group[i]);
		while (group[j] != 0 && j<10){
			answer += group[i] * group[j];
			j++;
		}
		i++;
	}
	printf("\n���������� ������� ������������ ������ � %d ��������� � 4-�� ������� �����: \n%llu", n, answer);
	_getch();
}
