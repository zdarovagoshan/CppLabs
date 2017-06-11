#define _CRT_SECURE_NO_WARNINGS

#include "rombStack.h"
#include <stdio.h>

Stack::Stack() { top = NULL; };
Stack::~Stack() 
{ 
	if (top != NULL) 
	{
		RbStack *St;
		while (top != NULL) 
		{
			St = top;
			top = top->next;
			delete St;
			St = top;
		}
	}
};

Stack::Stack(char *fname)
{
	FILE *fptr = fopen(fname, "r");
	if (!fptr) throw IO_ERR;
	romb squ;
	squ.load(fptr);
	top = new RbStack;
	top->sq = squ;
	top->next = NULL;
	while (!feof(fptr)) 
	{
		squ.load(fptr);
		push(squ);
	}
	fclose(fptr);
}


void Stack::push(romb rb)
{
	if (top == NULL) 
	{
		top = new RbStack;
		top->sq = rb;
		top->next = NULL;
	}
	else 
	{
		RbStack *puch = new RbStack;
		puch->next = top;
		top = puch;
		puch->sq = rb;
	}
}

romb Stack::pop() 
{
	if (top == NULL) throw EMPTY_STACK;
	else if (top->next==NULL) 
	{
		romb gt = top->sq;
		top = NULL;
		return gt;
	}
	else 
	{
		romb gt = top->sq;
		top = top->next;
		return gt;
	}
}

bool Stack::search(romb rb) 
{
	RbStack *St = top;
	if (top == NULL) throw EMPTY_STACK;
	while (St != NULL) {
		if (compare(rb, St->sq)) return true;
		St = St->next;
	}
	return false;
}

bool Stack::compare(romb rb, romb rb2) 
{
	POINT*k1 = rb.GetCoord();
	int*p1 = rb.GetPchar();
	int*b1 = rb.GetBchar();
	POINT*k2 = rb2.GetCoord();
	int*p2 = rb2.GetPchar();
	int*b2 = rb2.GetBchar();
	if ((comparePOINTs(k1, k2)) &&  p1 == p2 && b1 == b2) return true;
	else return false;
}

bool Stack::comparePOINTs(POINT k1[4], POINT k2[4])
{
	if (k1[0].x == k2[0].x && k1[0].y == k2[0].y &&k1[1].x == k2[1].x && k1[1].y == k2[1].y && k1[2].x == k2[2].x && k1[2].y == k2[2].y && k1[3].x == k2[3].x && k1[3].y == k2[3].y) return true;
	else return false;

}
void Stack::DrawSt() 
{
	if (top == NULL) throw EMPTY_STACK;
	else {
		RbStack *St = top;
		while (St != NULL)
		{
			St->sq.draw();
			St = St->next;
		}
	}
}

void Stack::save(char *fname)
{
	RbStack *St = top;
	romb rb;
	FILE *fptr = fopen(fname, "w");
	if (!fptr) throw IO_ERR;
	if (top == NULL) throw EMPTY_STACK;
	while (St != NULL) {
		St->sq.save(fptr);
		St = St->next;
	}
	fclose(fptr);
}