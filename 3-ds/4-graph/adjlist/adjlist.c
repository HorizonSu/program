#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
#include "stack.h"

typedef struct _graph_node_ {
	int data;
	struct _graph_node_ *next;
}gnode_st;

typedef struct _graph_adjlist_ {
	int vn;
	gnode_st *relation;
	char *visit;
}graph_st;

graph_st *graph_init(int vn);
int graph_show(graph_st *graph);
int graph_free(graph_st *graph);
int graph_add_edge(graph_st *graph, int vx, int vy);
gnode_st *graph_create_gnode(int data);
int graph_first_adj(graph_st *graph, int vx);
int graph_next_adj(graph_st *graph, int vx, int vy);
int graph_dfs(graph_st *graph, int start);
int graph_bfs(graph_st *graph, int start);

int main()
{
	int i;
	graph_st *graph = NULL;
	char edge[][2] = {
		0,1,
		0,2,
		0,4,
		1,3,
		3,4,
	};
	
	graph = graph_init(5);

	for (i = 0; i < sizeof(edge) / sizeof(*edge); i ++)
		graph_add_edge(graph, edge[i][0], edge[i][1]);

	graph_show(graph);

#if 0
	i = 2;
	vx = graph_first_adj(graph, i);
	puts("----------- first adjacency ---------");
	printf("V%d: V%d\n", i, vx);

	vy = graph_next_adj(graph, i, vx);
	printf("V%d: V%d, V%d\n", i, vx, vy);
#endif

	puts("------------ DFS -----------");
	graph_dfs(graph, 0);
	puts("\b ");

#if 0
	puts("-------------- BFS ------------ ");
	graph_bfs(graph, 0);
	puts("\b ");
#endif
	graph_free(graph);

	return 0;
}

graph_st *graph_init(int vn)
{
	graph_st *graph = NULL;

	graph = (graph_st *)malloc(sizeof(*graph));
	graph->vn = vn;
	graph->relation = malloc(sizeof(gnode_st) * vn);
	memset(graph->relation, 0, sizeof(*graph->relation) * vn);
	graph->visit = malloc(sizeof(*graph->visit) * vn);
	memset(graph->visit, 0, sizeof(*graph->visit) * vn);

	return graph;
}


int graph_free(graph_st *graph)
{
	gnode_st *p = NULL;
	gnode_st *tmp = NULL;
	int i;

	for (i = 0; i < graph->vn; i++) {
		p = graph->relation[i].next;
		while (NULL != p) {
			tmp = p;
			p = p->next;
			free(tmp);
		}
	}
	free(graph->relation);
	free(graph->visit);
	free(graph);
	
	return 0;
}

gnode_st *graph_create_gnode(int data)
{
	gnode_st *node = NULL;

	node = (gnode_st *)malloc(sizeof(*node));
	node->data = data;
	node->next = NULL;

	return node;
}

int _graph_add_edge1_(graph_st *graph, int vx, int vy)
{
	gnode_st *p = graph->relation + vx;
	gnode_st *new = NULL;

	while (p->next != NULL && p->next->data < vy)
		p = p->next;

	if (p->next == NULL || p->next->data > vy) {
		new = graph_create_gnode(vy);
		new->next = p->next;
		p->next = new;
	}

	return 0;
}

int graph_add_edge(graph_st *graph, int vx, int vy)
{
	if (vx < 0 || vx >= graph->vn || vy < 0 || vy >= graph->vn)
		return -1;

	_graph_add_edge1_(graph, vx, vy);
	_graph_add_edge1_(graph, vy, vx);

	return 0;
}

int graph_show(graph_st *graph)
{
	gnode_st *p = NULL;
	int i;
	
	for (i = 0; i < graph->vn; i++) {	
		printf("V%d: ", i);

		p = graph->relation[i].next;
		while (NULL != p) {
			printf(" V%d,", p->data);
			p = p->next;
		}
		puts("\b ");
	}

	return 0;
}

int graph_first_adj(graph_st *graph, int vx)
{
	gnode_st *p = graph->relation + vx;

	if (p->next == NULL)
		return -1;
	return p->next->data;
}

int graph_next_adj(graph_st *graph, int vx, int vy)
{
	gnode_st *p = graph->relation[vx].next;

	while (NULL != p && p->data != vy)
		p = p->next;
	if (p == NULL || p->next == NULL)
		return -1;
	return p->next->data;
}

#if 0
/* using recursion */
int graph_dfs(graph_st *graph, int start)
{
	int vtmp;
	
	if (graph->visit[start])
		return 0;

	printf(" V%d,", start);
	graph->visit[start] = 1;

	vtmp = graph_first_adj(graph, start);
	while (vtmp != -1) {
		graph_dfs(graph, vtmp);
		vtmp = graph_next_adj(graph, start, vtmp);
	}

	return 0;
}

#else
/* using stack */
int graph_dfs(graph_st *graph, int vertex)
{
	int vtmp;
	stack_st *stack = NULL;
	
	stack = stack_init(graph->vn);
//	stack_push(stack, vertex);
//	stack_push(stack, vertex);

	do {
		if (vertex != -1) {
			if (!graph->visit[vertex]) {
				printf(" V%d,", vertex);
				graph->visit[vertex] = 1;
				stack_push(stack, vertex);
				vtmp = vertex;
				vertex = graph_first_adj(graph, vertex);
			} else {
				vertex = graph_next_adj(graph, vtmp, vertex);
			}
		} else {
			stack_pop(stack, &vertex);
			vertex = graph_next_adj(graph, vertex, vtmp);
		}
	} while (!stack_isempty(stack));
	stack_free(stack);

	return 0;
	
}

#endif

int graph_bfs(graph_st *graph, int start)
{
	int vtmp;
	queue_st *queue = NULL;

	queue = queue_init(graph->vn);
	graph->visit[start] = 1;
	queue_enqueue(queue, start);

	while (!queue_isempty(queue)) {
		queue_dequeue(queue, &start);
		printf(" V%d,", start);
		
		vtmp = graph_first_adj(graph, start);
		while (vtmp != -1) {
			if (!graph->visit[vtmp]) {
				graph->visit[vtmp] = 1;
				queue_enqueue(queue, vtmp);
			}
			vtmp = graph_next_adj(graph, start, vtmp);
		}
	}

	queue_free(queue);

	return 0;
}
