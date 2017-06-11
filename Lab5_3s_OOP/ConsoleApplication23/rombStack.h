#include "romb.h"
#include <iostream>

#ifndef ROMB_CONTAINER
#define ROMB_CONTAINER

#define EMPTY_STACK "Стек пуст \n"

//Открытый стек
template <class Type> class Stack
{
private:
	struct RbStack { Type sq; RbStack *next; } *top;
	bool compare(Type rb, Type rb2);
	bool comparePOINTs(POINT k1[4], POINT k2[4]);
public:
	Stack() { top = NULL; };
	~Stack()
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

	Stack(FILE *fptr)
	{
		if (!fptr) throw IO_ERR;
		Type squ;
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
	};


	void push(Type rb)
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
	};

	Type pop()
	{
		if (top == NULL) throw EMPTY_STACK;
		else if (top->next == NULL)
		{
			Type gt = top->sq;
			top = NULL;
			return gt;
		}
		else
		{
			Type gt = top->sq;
			top = top->next;
			return gt;
		}
	};

	bool search(Type rb)
	{
		RbStack *St = top;
		if (top == NULL) throw EMPTY_STACK;
		while (St != NULL) {
			if (compare(rb, St->sq)) return true;
			St = St->next;
		}
		return false;
	};
	void DrawSt()
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
	};
	void save(char *fname)
	{
		RbStack *St = top;
		Type rb;
		FILE *fptr = fopen(fname, "r");
		if (!fptr) throw IO_ERR;
		if (top == NULL) throw EMPTY_STACK;
		while (St != NULL) {
			St->sq.save(fptr);
			St = St->next;
		}
		fclose(fptr);
	};

};

#endif