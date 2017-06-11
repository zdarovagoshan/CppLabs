#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "tables.h"
void main(){
	table avtovladelcy;
	ahuman man;
	tablem suspects;
	setlocale(LC_CTYPE, "Russian");
	FILE *fp, *fpp, *fpm;
	fp = fopen("Авто.txt", "r");
	fpp = fopen("Аварии.txt", "r");
	fpm = fopen("Подозреваемые.txt", "w");
	int i = 0;
	avtovladelcy.n = 0;
	while (fscanf(fp, "%s", &man.number) != EOF && avtovladelcy.n<19){
		fscanf(fp, "%s%s%s%s", &man.mark, &man.name.F, &man.name.I, &man.name.O);
		avtovladelcy.human[i] = man;
		avtovladelcy.n++;
		i++;
	}
	// heapSort(&avtovladelcy);
	quickSortR(avtovladelcy.human, avtovladelcy.n);
	review(fpp, fpm, &suspects, avtovladelcy);
	fclose(fp);
	fclose(fpp);
	fclose(fpm);
}