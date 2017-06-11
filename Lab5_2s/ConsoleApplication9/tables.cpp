#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "tables.h"
#include <string.h>
void review(FILE *fpr, FILE *fpn, tablem *T, table L){
	char mark[30];
	int i, j = 0;
	if (fscanf(fpr, "%s", &mark) != EOF)
	{
			for (i = 0; i < L.n; i++){
				if (strcmp(mark, L.human[i].mark) == 0) {
					T->thief[j].name = L.human[i].name;
					strcpy(T->thief[j].number, L.human[i].number);
					fprintf(fpn, "%s %s %s %s\n", T->thief[j].number, T->thief[j].name.F, T->thief[j].name.I, T->thief[j].name.O);
					j++;
					T->n = j;
				}
			}
	}
}
void quickSortR(ahuman *a, int N) {
	// На входе - массив a[], a[N] - его последний элемент.

	int i = 0, j = N - 1; 		// поставить указатели на исходные места
	ahuman temp, p;

	p = a[N >> 1];		// центральный элемент

	// процедура разделения
	do {
		while (strcmp (a[i].number, p.number)<0) i++;
		while (strcmp (a[j].number, p.number)>0) j--;

		if (i <= j) {
			temp = a[i]; a[i] = a[j]; a[j] = temp;
			i++; j--;
		}
	} while (i < j);

	// рекурсивные вызовы, если есть, что сортировать 
	if (j > 0) quickSortR(a, j);
	if (N > i) quickSortR(a + i, N - i);
}
/* void siftDown(table *numbers, int root, int bottom) {
	int done, maxChild;
	ahuman temp;
	done = 0; 
	while ((root * 2+1 < bottom) && (!done)) {
		if (root * 2+1 == bottom-1)
			maxChild = root * 2+1;
		else if (strcmp(numbers->human[root * 2+1].number, numbers->human[root * 2 + 2].number)>0)
			maxChild = root * 2+1;
		else
			maxChild = root * 2 + 2;
		if (strcmp(numbers->human[root].number, numbers->human[maxChild].number)<0) {
			temp = numbers->human[root];
			numbers->human[root] = numbers->human[maxChild];
			numbers->human[maxChild] = temp;
			root = maxChild;
		}
		else
			done = 1;
	}
}
void heapSort(table *numbers) {
	int i;
	ahuman temp;
	for (i = (numbers->n / 2) - 1; i >= 0; i--)
		siftDown(numbers, i, numbers->n);
	for (i = numbers->n - 1; i >= 1; i--) {
		temp = numbers->human[0];
		numbers->human[0] = numbers->human[i];
		numbers->human[i] = temp;
		siftDown(numbers, 0, i);
	}
} */
