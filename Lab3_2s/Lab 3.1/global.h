#ifndef GLOBAL_H
#define GLOBAL_H

struct ftree { char data; ftree *left, *right; };	//������
struct stack { ftree *elem; stack *next; };			//�������� ����
struct pfstack { bool flag; pfstack *next; };		//���� ������ ��� ��������� ������
struct resstack { int value; resstack *next; };		//���� ����������� ����������

#endif // GLOBAL_H