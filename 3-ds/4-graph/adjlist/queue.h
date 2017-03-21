#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_DEBUG	1

typedef struct _qnode_ {
	int data;
	struct _qnode_ *next;
}qnode_st;

typedef struct _queue_ {
	int total;
	int current;
	qnode_st *head,
				*tail;
}queue_st;

qnode_st *create_qnode(int value);
queue_st *queue_init(int len);
int queue_free(queue_st *queue);
int queue_enqueue(queue_st *queue, int value);
int queue_dequeue(queue_st *queue, int *value);
int queue_isfull(queue_st *queue);
int queue_isempty(queue_st *queue);
#if QUEUE_DEBUG
void _queue_debug_(queue_st *queue);
#endif

#endif /* __QUEUE_H__ */
