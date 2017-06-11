#include <conio.h>
#include <locale.h>
#include "tree.h"
#include "stack.h"

void main()
{
	setlocale(LC_CTYPE, "russian");

	stack *S = initstack();
	ftree *T = readtree("input.txt", S);

	prefix(T, S);
	infix(T, S);
	postfix(T, S, 'P');
	postfix(T, S, 'C');
	postfix(T, S, 'D');
	delete S;
	_getch();
}