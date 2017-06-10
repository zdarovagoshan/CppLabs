#include <stdio.h>
#include <stdlib.h>
#include "Operations.h"
int Pusta(queue *q) {
	if (q->end == 0) return 1;
	else return 0;
}
void Ochistka(queue *q){
	q->end=0;
}
int input(int x, queue *q){
	if (q->end == N) return 0;
	else {
		q->data[q->end] = x; q->end++;
		return 1;
	}
}
int output(queue *q, int &num){
	int i, r, y;
	if (q->end == 0) return 0;
	else {
		num= q->data[0];
		r = q->end;
		Ochistka(q);
		for (i = 1; i < r; i++) y=input(q->data[i], q); return 1;
	}
}
int show(queue q){
	queue w;
	int numr, y;
	w = q;
	if (Pusta(&w) == 1) return 0;
	else{
		while (Pusta(&w) == 0) { y=output(&w, numr); printf("%d ", numr); }
		printf("\n");
		return 1;
	}
}