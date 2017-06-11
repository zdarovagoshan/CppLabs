#include "romb.h"
#include <iostream>

#ifndef ROMB_CONTAINER
#define ROMB_CONTAINER

#define EMPTY_STACK "Стек пуст \n"

//Открытый стек
class Stack
{
private:
	struct RbStack { romb sq; RbStack *next; } *top;
	bool compare(romb rb, romb rb2);
	bool comparePOINTs(POINT k1[4], POINT k2[4]);
public:
	Stack();
	~Stack();
	Stack(char *fname);
	

	void push(romb rb);

	romb pop();

	bool search(romb rb);
	void DrawSt();
	void save(char *fname);
};
#endif
