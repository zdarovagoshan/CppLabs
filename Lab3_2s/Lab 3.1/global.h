#ifndef GLOBAL_H
#define GLOBAL_H

struct ftree { char data; ftree *left, *right; };	//Дерево
struct stack { ftree *elem; stack *next; };			//Основной стэк
struct pfstack { bool flag; pfstack *next; };		//Стэк флагов для концевого обхода
struct resstack { int value; resstack *next; };		//Стэк результатов вычисления

#endif // GLOBAL_H