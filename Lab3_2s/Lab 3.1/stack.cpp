#include <stdio.h>
#include "stack.h"
#include "tree.h"

//Основной стэк
stack *initstack()
{
	stack *s = new stack;
	s->next = NULL;
	return s;
}

bool stEmpty(stack *s)
{
	if (s->next == NULL) return 1;
	return 0;
}

void inst(ftree *input, stack *s)
{
	if (stEmpty(s))
	{
		s->next = initstack();
		s->next->elem = input;
	}
	else
	{
		stack *buf = s->next;
		s->next = new stack;
		s->next->next = buf;
		s->next->elem = input;
	}
}

ftree *outst(stack *s)
{
	ftree *output = s->next->elem;
	if (s->next->next == NULL)
	{
		delete s->next;
		s->next = NULL;
	}
	else
	{
		stack *buf = s->next;
		s->next = buf->next;
		delete buf;
	}
	return output;
}


//Стэк флагов для концевого обхода
pfstack *initPfStack()
{
	pfstack *s = new pfstack;
	s->next = NULL;
	return s;
}

bool pfStEmpty(pfstack *s)
{
	if (s->next == NULL) return 1;
	return 0;
}

void inPfSt(bool input, pfstack *s)
{
	if (pfStEmpty(s))
	{
		s->next = initPfStack();
		s->next->flag = input;
	}
	else
	{
		pfstack *buf = s->next;
		s->next = new pfstack;
		s->next->next = buf;
		s->next->flag = input;
	}
}

bool outPfSt(pfstack *s)
{
	bool output = s->next->flag;
	if (s->next->next == NULL)
	{
		delete s->next;
		s->next = NULL;
	}
	else
	{
		pfstack *buf = s->next;
		s->next = buf->next;
		delete buf;
	}
	return output;
}

//Стэк результатов вычисления формулы
resstack *initResStack()
{
	resstack *s = new resstack;
	s->next = NULL;
	return s;
}

bool resStEmpty(resstack *s)
{
	if (s->next == NULL) return 1;
	return 0;
}

void inResSt(int input, resstack *s)
{
	if (resStEmpty(s))
	{
		s->next = initResStack();
		s->next->value = input;
	}
	else
	{
		resstack *buf = s->next;
		s->next = new resstack;
		s->next->next = buf;
		s->next->value = input;
	}
}

int outResSt(resstack *s)
{
	int output = s->next->value;
	if (s->next->next == NULL)
	{
		delete s->next;
		s->next = NULL;
	}
	else
	{
		resstack *buf = s->next;
		s->next = buf->next;
		delete buf;
	}
	return output;
}