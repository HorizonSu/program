#include <stdio.h>
#include <stdlib.h>

#define DEBUG	1

typedef struct _queue_{
	int *data;
	int tlen;
	int head;
	int tail;
}queue_t;

queue_t *queue_init(int len);
int queue_destroy(queue_t *queue);
int queue_isempty(queue_t *queue);
int queue_isfull(queue_t *queue);
int queue_enqueue(queue_t *queue, int value);
int queue_dequeue(queue_t *queue, int *value);
int queue_getlen(queue_t *queue);

#if DEBUG
void _queue_debug_(queue_t *queue);
#endif

int main()
{
	int value = 100;
	queue_t *queue = NULL;
	
	queue = queue_init(10);
	
	puts("EnQueue:");
	while (-1 != queue_enqueue(queue, value)) {
		printf("%5d", value);
		value += 100;
	}
	putchar('\n');
	
	printf("Clen: %d\n", queue_getlen(queue));

#if DEBUG
	_queue_debug_(queue);
#endif
	
	puts("DeQueue:");
	while (-1 != queue_dequeue(queue, &value))
		printf("%5d", value);
	putchar('\n');

#if DEBUG
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
	queue->head = 0;
	queue->tail = 0;
	queue->data = (int *)malloc(sizeof(int) * len);

	return queue;
}

int queue_destroy(queue_t *queue)
{
	free(queue->data);
	free(queue);

	return 0;
}

int queue_enqueue(queue_t *queue, int value)
{
	if (queue_isfull(queue))
		return -1;

	queue->data[queue->tail] = value;
	queue->tail = (queue->tail + 1) % queue->tlen;

	return 0;
}

int queue_isfull(queue_t *queue)
{
	if ((queue->tail + 1) % queue->tlen == queue->head)
		return 1;
	return 0;
}

int queue_dequeue(queue_t *queue, int *value)
{
	if (queue_isempty(queue))
		return -1;
	
	*value = queue->data[queue->head];
	queue->head = (queue->head + 1) % queue->tlen;

	return 0;
}

int queue_isempty(queue_t *queue)
{
	if (queue->head == queue->tail)
		return 1;
	return 0;
}

int queue_getlen(queue_t *queue)
{
	if (queue->head == queue->tail)
		return 0;

	if (queue->tail > queue->head)
		return queue->tail - queue->head;
	else
		return queue->tlen - queue->head + queue->tail;
}

#if DEBUG
void _queue_debug_(queue_t *queue)
{
	int index;

	puts("------------------- DEBUG --------------------");
	printf("tlen: %d\tHead: %d\tTail: %d\n", 
			queue->tlen, queue->head, queue->tail);
	for (index = 0; index < queue->tlen; index ++)
		printf("%5d", queue->data[index]);
	puts("\n---------------------------------------------");
}
#endif
