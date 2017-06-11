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
	unsigned long long *group=new unsigned long long[10];    //Массив в котором хранится количество графов каждого типа изоморфности (всего 10 типов)
	printf("Введите количество вершин: ");
	scanf_s("%d", &n);

	//Создание всевозможных вариантов графов с 4 ребрами и N вершинами методом перебора
	for (i = 0; i < 10; i++){
		group[i] = 0;
	}
	createSetGraphs(group, n);
	answer = 0;
	i = 0;
	printf("Количество графов каждого типа: \n");
	while (group[i] != 0 && i<10){
		j = i+1;
		printf("%llu ", group[i]);
		while (group[j] != 0 && j<10){
			answer += group[i] * group[j];
			j++;
		}
		i++;
	}
	printf("\nКоличество попарно неизоморфных графов с %d вершинами и 4-мя ребрами равно: \n%llu", n, answer);
	_getch();
}
