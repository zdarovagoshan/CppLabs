#include "global.h"

#ifndef TREE_H
#define TREE_H

ftree *inittree();

ftree *readtree(char fname[30], stack *S);

void prefix(ftree *T, stack *S);

void infix(ftree *T, stack *S);

void postfix(ftree *T, stack *S, char mode);

#endif //TREE_H