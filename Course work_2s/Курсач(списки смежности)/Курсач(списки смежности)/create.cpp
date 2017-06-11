#include <stdio.h>
#include <iostream>
#include "create.h"

void createSetGraphs(unsigned long long *&gr, int M){
	int a1, a2, a3, a4, a5, a6, a7, a8, i, tp, notiz;
	int *g = new int [8];
	for (a1 = 1; a1 <= M; a1++){
		g[0] = a1;
		for (a2 = a1+1; a2 <= M; a2++){
			g[1] = a2;
			for (a3 = a1; a3 <= M; a3++){
				g[2] = a3;
				for (a4 = a3+1; a4 <= M; a4++){
					g[3] = a4;
					for (a5 = a3; a5 <= M; a5++){
						g[4] = a5;
						for (a6 = a5+1; a6 <= M; a6++){
							g[5] = a6;
							for (a7 = a5; a7 <= M; a7++){
								g[6] = a7;
								for (a8 = a7+1; a8 <= M; a8++){
									g[7] = a8;
									notiz = 0;
									for (i = 0; i < 3 && !notiz; i++){

										//Действия исключающие повторения одного и того же графа
										if (g[i * 2] == g[(i + 1) * 2])
											if (g[i * 2 + 1] >= g[(i + 1) * 2 + 1])
												notiz = 1;
									}

									//Создание множеств количества типов графов
									if (!notiz){
										tp = type_graph(g);
										gr[tp]++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

int type_graph(int* &a){
	int i, j, q, w, b2, a2, Q,  exit;
	int vertex[8];
	int degree[8];
	for (i = 0; i < 8; i++){
		degree[i] = 0;
	}
	q = 0;
	//Действия считающие степень каждой вершины
	for (i = 0; i < 8; i++){
		exit = 0;
		for (j = 0; j < i && !exit; j++){
			if (a[i] == a[j]) exit = 1;
		}
		if (!exit){
			vertex[q] = a[i];
			for (w = 0; w < 8; w++){
				if (vertex[q] == a[w]){
					degree[q]++;
				}
			}
			q++;
		}
	}
	Q = q;

	//Установление типа графа по степеням вершин
	b2 = 0;
	for (i = 0; i < Q; i++){
		a2 = 0;
		if (degree[i] == 4) return 4;
		if (degree[i] == 3) {
			for (j = 0; j < Q; j++){
				if (degree[j] == 2) a2++;
			}
			if (a2 == 2) return 0;
			else return 3;
		}
		if (degree[i] == 2) b2++;
	}
	if (b2 == 4) return 1;
	if (b2 == 1) return 8;
	if (b2 == 0) return 9;

	for (i = 0; i < Q-1; i++){
		if (degree[i] == 1){
			j = i + 1;
				if (degree[j] == 1){
					for (q = 0; q < 4; q++){
						if (a[q * 2] == vertex[i] && a[q * 2 + 1] == vertex[j]){
							if (b2 == 3) return 5;
							return 7;
						}
					}
			}
		}
	}
	
	if (b2 == 3) return 2; 
	return 6;
}