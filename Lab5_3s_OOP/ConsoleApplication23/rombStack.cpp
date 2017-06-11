#define _CRT_SECURE_NO_WARNINGS

#include "rombStack.h"
#include <stdio.h>
#include <fstream>

//template <class Type> Stack <Type>::Stack() { top = NULL; };
//template <class Type> Stack <Type>::~Stack()
//{
//	if (top != NULL)
//	{
//		RbStack *St;
//		while (top != NULL)
//		{
//			St = top;
//			top = top->next;
//			delete St;
//			St = top;
//		}
//	}
//};
//
//template <class Type> Stack <Type>::Stack(FILE *fptr)
//{
//	if (!fptr) throw IO_ERR;
//	Type squ;
//	squ.load(fptr);
//	top = new RbStack;
//	top->sq = squ;
//	top->next = NULL;
//	while (!feof(fptr))
//	{
//		squ.load(fptr);
//		push(squ);
//	}
//	fclose(fptr);
//}
//
//
//template <class Type> void Stack <Type>::push(Type rb)
//{
//	if (top == NULL)
//	{
//		top = new RbStack;
//		top->sq = rb;
//		top->next = NULL;
//	}
//	else
//	{
//		RbStack *puch = new RbStack;
//		puch->next = top;
//		top = puch;
//		puch->sq = rb;
//	}
//}

//template <class Type> Type Stack <Type>::pop()
//{
//	if (top == NULL) throw EMPTY_STACK;
//	else if (top->next == NULL)
//	{
//		Type gt = top->sq;
//		top = NULL;
//		return gt;
//	}
//	else
//	{
//		Type gt = top->sq;
//		top = top->next;
//		return gt;
//	}
//}
//
//template <class Type> bool Stack <Type>::search(Type rb)
//{
//	RbStack *St = top;
//	if (top == NULL) throw EMPTY_STACK;
//	while (St != NULL) {
//		if (compare(rb, St->sq)) return true;
//		St = St->next;
//	}
//	return false;
//}

template <> bool Stack <romb>::compare(romb rb, romb rb2)
{
	POINT*k1 = rb.GetFrameCoord();
	POINT*k2 = rb2.GetFrameCoord();
	return (comparePOINTs(k1, k2));
}

template <> bool Stack <SolidRomb>::compare(SolidRomb rb, SolidRomb rb2)
{
	POINT*k1 = rb.GetFrameCoord();
	POINT*k2 = rb2.GetFrameCoord();
	return (comparePOINTs(k1, k2));
}

template <> bool Stack <HollowRomb>::compare(HollowRomb rb, HollowRomb rb2)
{
	POINT*k1 = rb.GetFrameCoord();
	POINT*ki1 = rb.GetInnerCoord();
	POINT*k2 = rb2.GetFrameCoord();
	POINT*ki2 = rb2.GetInnerCoord();
	return (comparePOINTs(k1, k2) && comparePOINTs(ki1, ki2));
}

template <class Type> bool Stack <Type>::comparePOINTs(POINT k1[4], POINT k2[4])
{
	if (k1[0].x == k2[0].x && k1[0].y == k2[0].y &&k1[1].x == k2[1].x && k1[1].y == k2[1].y && k1[2].x == k2[2].x && k1[2].y == k2[2].y && k1[3].x == k2[3].x && k1[3].y == k2[3].y) return true;
	else return false;
}
//template <class Type> void Stack <Type>::DrawSt()
//{
//	if (top == NULL) throw EMPTY_STACK;
//	else {
//		RbStack *St = top;
//		while (St != NULL)
//		{
//			St->sq.draw();
//			St = St->next;
//		}
//	}
//}
//
//template <class Type> void Stack <Type>::save(char *fname)
//{
//	RbStack *St = top;
//	Type rb;
//	FILE fptr; fptr.open(fname);
//	if (!fptr) throw IO_ERR;
//	if (top == NULL) throw EMPTY_STACK;
//	while (St != NULL) {
//		St->sq.save(fptr);
//		St = St->next;
//	}
//	fclose(fptr);
//}