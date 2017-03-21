#include "linkqueue.h"

void _debug_(LinkQueue *lq)
{
	LinkNode *p = lq->front->next;

	puts("debug:");
	while(NULL != p)
	{
		printf("%5d",p->lndata->btdata.weight);
		p = p ->next;
	}	
	putchar(10);
}

LinkQueue *creat_empty_linkqueue(int size)
{
	LinkQueue *lq = NULL;
	
	lq = (LinkQueue *)malloc(sizeof(LinkQueue));
	lq->front = lq->rear = creat_linknode(0);
	lq->len = 0;
	lq->size = size;

	return lq;
}
int free_queue(LinkQueue *lq)
{
	LinkNode *tmp = NULL;

	while(NULL != lq->front)
	{
		tmp = lq->front;
		lq->front = lq->front->next;
		free(tmp);
	}
	free(lq);
	return 0;
}

int is_empty(LinkQueue *lq)
{
	//return lq->front == lq->rear;
//	return lq->front->next == NULL;
	return lq->len <= 0;
}

int is_full(LinkQueue *lq)
{
	return lq->len >= lq->size;
}

int enqueue(LinkQueue *lq, ListData data)
{
	LinkNode *new = NULL;

	if(is_full(lq))
		return 0;
	new = creat_linknode(data);
//	new->next = lq->rear->next;
	lq->rear->next = new;
	lq->rear = lq->rear->next;
	lq->len ++;
	return 1;
}
ListData dequeue(LinkQueue *lq)
{
	LinkNode *tmp = NULL;

	if(is_empty(lq))
		return 0;

	tmp = lq->front;
	lq->front = tmp->next;
	free(tmp);
	lq->len --;
	return lq->front->lndata;
}
