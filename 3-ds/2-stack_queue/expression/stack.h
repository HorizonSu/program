#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>

#define STACK_DEBUG	0

typedef struct _sequence_stack_{
	int top;
	int len;
	int *data;
}SeqStack;

extern SeqStack *creat_seqstack(int len);
extern int free_seqstack(SeqStack *stack);
extern int push_seqstack(SeqStack *stack, int value);
extern int pop_seqstack(SeqStack *stack, int *dest);
extern int gettop_seqstack(SeqStack *stack, int *dest);
extern void _debug_seqstack_(SeqStack *stack);

#endif
