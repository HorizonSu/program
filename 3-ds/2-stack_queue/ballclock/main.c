#include <stdio.h>
#include "stack.h"
#include "queue.h"

#define QUEUE_LEN	27
#define STACK_LEN_M1	4
#define STACK_LEN_M5	11
#define STACK_LEN_H1	11

int check_queue(queue_t *queue);

int main()
{
	queue_t *queue = NULL;
	stack_t *m1 = NULL;
	stack_t *m5 = NULL;
	stack_t *h1 = NULL;
	int ball;
	int tmp;
	int time = 0;
	
	queue = queue_init(QUEUE_LEN);
	m1 = stack_init(STACK_LEN_M1);
	m5 = stack_init(STACK_LEN_M5);
	h1 = stack_init(STACK_LEN_H1);

	ball = 1;
	while (0 == queue_enqueue(queue, ball))
		ball++;

	while (1) {
		queue_dequeue(queue, &ball);

		if (0 == stack_push(m1, ball))
			continue;
		while (0 == stack_pop(m1, &tmp))
			queue_enqueue(queue, tmp);

		if (0 == stack_push(m5, ball))
			continue;
		while (0 == stack_pop(m5, &tmp))
			queue_enqueue(queue, tmp);

		if (0 == stack_push(h1, ball))
			continue;
		while (0 == stack_pop(h1, &tmp))
			queue_enqueue(queue, tmp);

		queue_enqueue(queue, ball);
		time++;

		if (check_queue(queue))
			break;
	}

	printf("%dD-%dH\n", time / 2, (time % 2) * 12);
	
	queue_destroy(queue);
	stack_destroy(m1);
	stack_destroy(m5);
	stack_destroy(h1);

	return 0;
}

int check_queue(queue_t *queue)
{
	qnode_t *p = queue->head->next;

	while (NULL != p && NULL != p->next) {
		if (p->data > p->next->data)
			return 0;
		p = p->next;
	}
	return 1;
}
