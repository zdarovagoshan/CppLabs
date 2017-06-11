#ifndef TABLES_H
#define TABLES_H
struct FIO{ char F[20], I[20], O[20]; };
struct ahuman{ char number[14], mark[30]; FIO name; };
struct bhuman{ char number[14]; FIO name; };
struct table{ ahuman human[19]; int n; };
struct tablem{ bhuman thief[19]; int n; };
void review(FILE *fpr, FILE *fpn, tablem *T, table L);
void siftDown(table *numbers, int root, int bottom);
void heapSort(table *numbers);
void quickSortR(ahuman *a, int N);
#endif