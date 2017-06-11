#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "tables.h"
#include <string.h>
#include <locale.h>
void molodcy(hesh *&c, ahuman M )
{
	hesh *p, *h;
	p = c;
	h = p;
	if (c != NULL){
		if (strcmp(c->man.number, M.number)==0)
		{
			c = c->next; delete p;
		}
		else {
			while ((p->next != NULL) && strcmp(p->man.number, M.number)!=0){
				h = p;
				p = p->next;
			}
			if (strcmp(p->man.number, M.number)==0){
				h->next = p->next; delete p;
			}
		}
	}
}
int key(ahuman T){
	int k = (int)(T.number[0])+64;
	return k;
}
void create(hesh *&b, ahuman M) {
	hesh *p;
if (b == NULL)
{ b = new hesh; b->man = M; b->next = NULL; }
else {
	p = b;
	while (p->next != NULL){
		p = p->next;
	}
	p->next = new hesh;
	p = p->next;
	p->man = M;
	p->next = NULL;
}
}