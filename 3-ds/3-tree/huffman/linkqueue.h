#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"


typedef struct _linkqueue_ {
	int size;
	int len;
	LinkNode *front,
			 *rear;
}LinkQueue;

LinkQueue *creat_empty_linkqueue(int size);
int is_empty(LinkQueue *lq);
int is_full(LinkQueue *lq);
int enqueue(LinkQueue *lq, ListData data);
ListData dequeue(LinkQueue *lq);
int free_queue(LinkQueue *lq);
void _debug_(LinkQueue *lq);

#endif
