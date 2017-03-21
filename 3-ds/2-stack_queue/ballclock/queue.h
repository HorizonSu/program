#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_DEBUG	0

typedef struct _qnode_ {
	int data;
	struct _qnode_ *next;
}qnode_t;

typedef struct _queue_ {
	qnode_t *head;
	qnode_t *tail;
	int tlen;
	int clen;
}queue_t;

extern qnode_t *create_qnode(int value);
extern queue_t *queue_init(int len);
extern int queue_destroy(queue_t *queue);
extern int queue_enqueue(queue_t *queue, int value);
extern int queue_dequeue(queue_t *queue, int *value);
extern int queue_isfull(queue_t *queue);
extern int queue_isempty(queue_t *queue);
#if QUEUE_DEBUG
extern void _queue_debug_(queue_t *queue);
#endif

#endif /* __QUEUE_H__ */
