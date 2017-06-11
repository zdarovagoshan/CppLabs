#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
struct a { float chislo; a*next; } *L, *curr;
void menyaem() {
	a *sled, *pred;
	curr = L;
	pred = NULL;
	sled = curr->next;
	while (sled->next) {
		(curr->next) = pred;
		pred = curr;
		curr = sled;
		sled = (sled->next);
	}
	sled->next = curr;
	curr->next = pred;
	L = sled;
}
void main() {
	FILE *fp;
	float t;
	bool s = true;
	if (fp = fopen("input.txt", "r")) {
		L = new a;
		curr = L;
		fscanf(fp, "%f", &(curr->chislo));
		while (fscanf(fp, "%f", &t) != EOF) {
			curr->next = new a;
			if (curr->chislo > t)
				s = false;
			curr = (curr->next);
			curr->chislo = t;
		}
		curr->next = NULL;
		fclose(fp);
		if (s == false)
			menyaem();
		if (fp = fopen("output.txt", "w")) {
			curr = L;
			while (curr != NULL) {
				fprintf(fp, "%f ", curr->chislo);
				curr = (curr->next);
			}
			fclose(fp);
		}
		else perror("error");
	}
	else perror("error");
}
