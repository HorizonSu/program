#include "queue.h"

queue_t *queue_init(int len)
{
	queue_t *queue = NULL;

	queue = (queue_t *)malloc(sizeof(queue_t));
	queue->tlen = len;
	queue->clen = 0;
	queue->head = create_qnode(0);
	queue->tail = queue->head;

	return queue;
}

qnode_t *create_qnode(int value)
{
	qnode_t *node = NULL;

	node = (qnode_t *)malloc(sizeof(qnode_t));
	node->data = value;
	node->next = NULL;

	return node;
}

int queue_destroy(queue_t *queue)
{
	qnode_t *p = queue->head;
	qnode_t *tmp = NULL;
	
	while (NULL != p) {
		tmp = p;
		p = tmp->next;
		free(tmp);
	}
	free(queue);

	return 0;
}

int queue_enqueue(queue_t *queue, int value)
{
	qnode_t *node = NULL;

	if (queue_isfull(queue))
		return -1;

	node = create_qnode(value);
	queue->tail->next = node;
	queue->tail = node;

	queue->clen ++;

	return 0;
}

int queue_dequeue(queue_t *queue, int *value)
{
	qnode_t *tmp = queue->head;

	if (queue_isempty(queue))
		return -1;

	queue->head = tmp->next;
	free(tmp);

	*value = queue->head->data;
	queue->clen --;

	return 0;
}

int queue_isfull(queue_t *queue)
{
	if (queue->clen >= queue->tlen)
		return 1;
	return 0;
}

int queue_isempty(queue_t *queue)
{
	if (queue->head == queue->tail)
		return 1;
	return 0;
}

#if QUEUE_DEBUG
void _queue_debug_(queue_t *queue)
{
	qnode_t *p = queue->head->next;

	puts("------------------------ QUEUE_DEBUG ---------------------");
	printf("tlen: %d\tclen: %d\n", queue->tlen, queue->clen);
	while (NULL != p) {
		printf("%5d", p->data);
		p = p->next;
	}
	puts("\n------------------------------------------------");
	
	return ;
}
#endif
