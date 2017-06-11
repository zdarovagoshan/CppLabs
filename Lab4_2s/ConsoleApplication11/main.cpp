#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "tables.h"
void main(){
	hesh *a[34], *p;
	ahuman mun;
	int q, i;
	setlocale(LC_CTYPE, "Russian");
	FILE *fp, *fpp, *fpm;
	fp = fopen("Авто.txt", "r");
	fpp = fopen("Аварии.txt", "r");
	fpm = fopen("Молодцы.txt", "w");
	for (i = 0; i < 34; i++){
		a[i] = NULL;
	}
	while (fscanf(fp, "%s", &mun.number) != EOF){
		fscanf(fp, "%s%s%s%s", &mun.mark, &mun.name.F, &mun.name.I, &mun.name.O);
		q = key(mun);
		create(a[q], mun);
	}
	while (fscanf(fpp, "%s", &mun.number) != EOF){
		fscanf(fpp, "%s", &mun.mark);
		int q = key(mun);
		molodcy(a[q], mun);
	}
	q = 0;
	while (q < 33){
		p = a[q];
		while (p != NULL){
			fprintf(fpm, "%s %s %s\n", p->man.name.F, p->man.name.I, p->man.name.O);
			p = p->next;
		}
		q++;
	}
	fclose(fp);
	fclose(fpp);
	fclose(fpm);
}