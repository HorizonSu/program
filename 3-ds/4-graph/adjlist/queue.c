#include "queue.h"

queue_st *queue_init(int len)
{
	queue_st *queue = NULL;

	queue = (queue_st *)malloc(sizeof(queue_st));
	queue->total = len;
	queue->current = 0;
	queue->head = create_qnode(0);
	queue->tail = queue->head;

	return queue;
}

qnode_st *create_qnode(int value)
{
	qnode_st *node = NULL;

	node = (qnode_st *)malloc(sizeof(qnode_st));
	node->data = value;
	node->next = NULL;

	return node;
}

int queue_free(queue_st *queue)
{
	qnode_st *p = queue->head;
	qnode_st *tmp = NULL;
	
	while (NULL != p) {
		tmp = p;
		p = tmp->next;
		free(tmp);
	}
	free(queue);

	return 0;
}

int queue_enqueue(queue_st *queue, int value)
{
	qnode_st *node = NULL;

	if (queue_isfull(queue))
		return -1;

	node = create_qnode(value);
	queue->tail->next = node;
	queue->tail = node;

	queue->current ++;

	return 0;
}

int queue_dequeue(queue_st *queue, int *value)
{
	qnode_st *tmp = queue->head;

	if (queue_isempty(queue))
		return -1;

	queue->head = tmp->next;
	free(tmp);

	*value = queue->head->data;
	queue->current --;

	return 0;
}

int queue_isfull(queue_st *queue)
{
	if (queue->current >= queue->total)
		return 1;
	return 0;
}

int queue_isempty(queue_st *queue)
{
	if (queue->head == queue->tail)
		return 1;
	return 0;
}

#if QUEUE_DEBUG
void _queue_debug_(queue_st *queue)
{
	qnode_st *p = queue->head->next;

	puts("------------------------ QUEUE_DEBUG ---------------------");
	printf("Total: %d\tCurrent: %d\n", queue->total, queue->current);
	while (NULL != p) {
		printf("%5d", p->data);
		p = p->next;
	}
	puts("\n------------------------------------------------");

}
#endif
