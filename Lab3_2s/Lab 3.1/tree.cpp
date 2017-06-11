#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "stack.h"

ftree *inittree()
{
	ftree *buf;
	buf = new ftree;
	buf->left = NULL;
	buf->right = NULL;
	return buf;
}

ftree *readtree(char fname[30], stack *S)
{
	char input;
	FILE *fin = fopen(fname, "r");
	ftree *buf, *root, *left, *right;

	while (fscanf(fin, "%c", &input) != EOF)
	{
		printf_s("%c", input);
		if (input != '(' && input != ')')
		{
			buf = inittree();
			buf->data = input;
			inst(buf, S);
		}
		if (input == ')')
		{
			right = outst(S);
			root = outst(S);
			left = outst(S);

			root->left = left;
			root->right = right;
			inst(root, S);
		}
	}
	fclose(fin);
	return outst(S);
}

void prefix(ftree *T, stack *S)
{
	ftree *buf = T;
	printf_s("\n\n Прямой обход: ");

	while (buf != NULL)
	{
		printf_s("%c", buf->data);
		if (buf->left != NULL && buf->right != NULL)
		{
			(inst(buf->right, S));
			buf = buf->left;
		}
		else
			if (buf->left == NULL && buf->right == NULL)
				if (!stEmpty(S)) buf = outst(S);
				else buf = NULL;
			else
				if (buf->left != NULL) buf = buf->left;
				else buf = buf->right;
	}
}

void infix(ftree *T, stack *S)
{
	ftree *buf = T;
	printf_s("\n\n Обратный обход: ");
	bool flag = true;

	while (flag)
	{
		while (buf != NULL)
		{
			inst(buf, S);
			buf = buf->left;
		}
		if (!stEmpty(S))
		{
			buf = outst(S);
			printf_s("%c", buf->data);
			buf = buf->right;
		}
		else flag = false;
	}
}

bool isOper(char input)
{
	if (input == '+' || input == '-' || input == '*') return 1;
	else return 0;
}

void postfix(ftree *T, stack *S, char mode)
{
	bool flag;
	pfstack *pfS = initPfStack();
	resstack *resS = initResStack();
	ftree *buf = T;

	if (mode == 'P') printf_s("\n\n Концевой обход: ");
	if (mode == 'C') printf_s("\n\n Значение формулы: ");

	do
	{
		while (buf != NULL)
		{
			inst(buf, S);
			inPfSt(false, pfS);
			buf = buf->left;
		}
		if (!stEmpty(S))
		{
			do
			{
				buf = outst(S);
				flag = outPfSt(pfS);
				if (flag)
					switch (mode)
				{
					case 'P': printf_s("%c", buf->data); break;
					case 'D': delete buf; break;
					case 'C':
					{
						char cbuf = buf->data;
						if (!isOper(cbuf))
							inResSt(cbuf - '0', resS);
						else
						{
							int R = outResSt(resS), L = outResSt(resS);
							switch (cbuf)
							{
							case '+': inResSt(L + R, resS); break;
							case '-': inResSt(L - R, resS); break;
							case '*': inResSt(L * R, resS); break;
							}
						}
					} break;
				}
			} while (flag && !stEmpty(S));
			if (!flag)
			{
				inst(buf, S);
				inPfSt(true, pfS);
				buf = buf->right;
			}
		}
	} while (!stEmpty(S));

	if (mode == 'C') printf_s("%d", outResSt(resS));
	delete resS;
	delete pfS;
}