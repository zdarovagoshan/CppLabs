#ifndef OPERATIONS_H
#define OPERATIONS_H
#define N 5
struct queue { int end; int data[N]; };
int Pusta(queue *q);
void Ochistka(queue *q);
int input(int x, queue *q);
int output(queue *q, int &num);
int show(queue q);
#endif