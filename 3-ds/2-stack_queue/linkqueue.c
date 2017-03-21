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

qnode_t *create_qnode(int value);
queue_t *queue_init(int len);
int queue_destroy(queue_t *queue);
int queue_enqueue(queue_t *queue, int value);
int queue_dequeue(queue_t *queue, int *value);
int queue_isfull(queue_t *queue);
int queue_isempty(queue_t *queue);
#if QUEUE_DEBUG
void _queue_debug_(queue_t *queue);
#endif

int main()
{
	queue_t *queue = NULL;
	int value = 100;
	
	queue = queue_init(10);

	puts("EnQueue:");
	while (0 == queue_enqueue(queue, value)) {
		printf("%5d", value);
		value += 100;
	}
	putchar('\n');

#if QUEUE_DEBUG
	_queue_debug_(queue);
#endif
	
	puts("DeQueue:");
	while (0 == queue_dequeue(queue, &value))
		printf("%5d", value);
	putchar('\n');
	
	while (0 == queue_enqueue(queue, value))
		value += 100;
#if QUEUE_DEBUG
	_queue_debug_(queue);
#endif

	queue_destroy(queue);
	
	return 0;
}

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
