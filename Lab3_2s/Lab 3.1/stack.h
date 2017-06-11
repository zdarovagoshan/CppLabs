#include "global.h"

#ifndef STACK_H
#define STACK_H

//Основной стэк
stack *initstack();

bool stEmpty(stack *s);

void inst(ftree *input, stack *s);

ftree *outst(stack *s);

//Стэк флагов для концевого обхода
pfstack *initPfStack();

bool pfStEmpty(pfstack *s);

void inPfSt(bool input, pfstack *s);

bool outPfSt(pfstack *s);

//Стэк результатов вычисления формулы
resstack *initResStack();

bool resStEmpty(resstack *s);

void inResSt(int input, resstack *s);

int outResSt(resstack *s);

#endif // STACK_H
