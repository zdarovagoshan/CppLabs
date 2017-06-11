#include "global.h"

#ifndef STACK_H
#define STACK_H

//�������� ����
stack *initstack();

bool stEmpty(stack *s);

void inst(ftree *input, stack *s);

ftree *outst(stack *s);

//���� ������ ��� ��������� ������
pfstack *initPfStack();

bool pfStEmpty(pfstack *s);

void inPfSt(bool input, pfstack *s);

bool outPfSt(pfstack *s);

//���� ����������� ���������� �������
resstack *initResStack();

bool resStEmpty(resstack *s);

void inResSt(int input, resstack *s);

int outResSt(resstack *s);

#endif // STACK_H
