#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iomanip>
using namespace std;
int isomorphic (int **c, int **v, int M){
	int i, j, q, l, s, d, w, e, p;
	bool isom;
	int **g = new int*[M];
	for (i = 0; i < M; i++){
		g[i] = new int[M];
	}
	int** o = new int*[M];
	for (i = 0; i < M; i++){
		o[i] = new int[M];
	}
	for (i = 0; i < M - 1; i++){
		q = i+1;
		for (j = q; j < M; j++){
			for (w = 0; w < M - 1; w++){
				p = w + 1;
				for (e = p; e < M; e++){
					isom = true;
					for (l = 0; l < M; l++){
						for (d = 0; d < M; d++){
							o[l][d] = c[l][d];
						}
					}
					for (l = 0; l < M; l++){
						o[l][j] = c[l][i];
						o[l][i] = c[l][j];
					}
					for (s = 0; s < M; s++){
						for (d = 0; d < M; d++){
							g[s][d] = o[s][d];
						}
					}
					for (l = 0; l < M; l++){
						g[w][l] = o[e][l];
						g[e][l] = o[w][l];
					}
					for (s = 0; s < M; s++){
						for (d = 0; d < M; d++){
							if (g[s][d] != v[s][d]) isom = false;
						}
					}
					if (isom == true) return 1;
				}
			}
		}
	}
	return 0;
}
void main(){
	setlocale(LC_CTYPE, "Russian");
	int q, j, i, k, N, w, e, r, t, y, u, z, x, notiz, answer=0;
	int g[4][2];
	printf("Введите количество вершин: ");
	scanf_s("%d", &N);
	int n = ((N*(N - 1) / 2)*((N*(N - 1) / 2) - 1)*(N*(N - 1) / 2 - 2)*(N*(N - 1) / 2 - 3)) / (2 * 3 * 4);
	int ***b = new int** [n];
	for (i = 0; i < n; i++){
	b[i] = new int* [N];
	}
	for (i = 0; i < n; i++){
		for (j = 0; j < N; j++){
			b[i][j] = new int[N];
		}
	}
	int*** a = new int**[n];
	for (i = 0; i < n; i++){
		a[i] = new int*[4];
	}
	for (i = 0; i < n; i++){
		for (j = 0; j < 4; j++){
			a[i][j] = new int[2];
		}
	}
	k = 0;
	for (q = 1; q <= N; q++){
	g[0][0] = q;
	for (w = 1; w <= N; w++){
		g[0][1] = w;
		for (e = 1; e <= N; e++){
			g[1][0] = e;
			for (r = 1; r <= N; r++){
				g[1][1] = r;
				for (t = 1; t <= N; t++){
					g[2][0] = t;
					for (y = 1; y <= N; y++){
						g[2][1] = y;
						for (u = 1; u <= N; u++){
							g[3][0] = u;
							for (i = 1; i <= N; i++){
								g[3][1] = i;
								notiz = 0;
								for (j = 0; j < 4; j++){
									if (g[j][0] >= g[j][1]) notiz =1;
								}
								if (!notiz){
									for (j = 0; j < 3; j++){
										z = g[j][0] * 10 + g[j][1];
										x = g[j + 1][0] * 10 + g[j + 1][1];
										if (z >= x) notiz = 1;
									}
								}
								if (!notiz){
									a[k][3][1] = g[3][1];
									a[k][3][0] = g[3][0];
									a[k][2][1] = g[2][1];
									a[k][2][0] = g[2][0];
									a[k][1][1] = g[1][1];
									a[k][1][0] = g[1][0];
									a[k][0][1] = g[0][1];
									a[k][0][0] = g[0][0];
									k++;
								}
							}
						}
					}
				}
			}
		}
	}
		}
	for (i = 0; i < n; i++){
		for (q = 0; q < N; q++){
			for (w = 0; w < N; w++){
				b[i][q][w] = 0;
			}
		}
	}
	for (i = 0; i < k; i++){
		for (q = 0; q < N; q++){
				b[i][a[i][q][0]-1][a[i][q][1]-1] = 1;
				b[i][a[i][q][1]-1][a[i][q][0]-1] = 1;
		}
	}
	q = 0;
	while (q < k-1){
		for (i = q+1; i < k; i++){
			if (isomorphic(b[q], b[i], N)) answer++;
		}
		q++;
	}
	for (i = 0; i < n; i++){
		for (j = 0; j < N; j++){
			for (q = 0; q < N; q++){
				printf("%d ", b[i][j][q]);
			}
			printf("\n");
		}
		printf("\n");
	}
	_getch();
}
