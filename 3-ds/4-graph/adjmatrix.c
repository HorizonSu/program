#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A	0
#define B	1
#define C	2
#define D	3
#define E	4

typedef struct _graph_ {
	void *relation;
	int vn;
}graph_t;

graph_t *graph_init(int vn);
int graph_free(graph_t *graph);
int graph_add_edge(graph_t *graph, int vx, int vy);
int graph_show(graph_t *graph);

int main()
{
	char edges[][2] = {
		{A,B},
		{A,C},
		{A,D},
		{B,E},
		{C,D},
		{C,E}
	};
	graph_t *graph = NULL;
	int i;
	
	graph = graph_init(5);

	for (i = 0; i < sizeof(edges) / sizeof(edges[1]); i ++)
		graph_add_edge(graph, edges[i][0], edges[i][1]);
	
	graph_show(graph);

	graph_free(graph);

	return 0;
}

graph_t *graph_init(int vn)
{
	graph_t *graph = NULL;

	graph = (graph_t *)malloc(sizeof(graph_t));
	graph->vn = vn;
	graph->relation = (char *)malloc(vn * vn);
	memset(graph->relation, 0, vn * vn);

	return graph;
}

int graph_free(graph_t *graph)
{
	free(graph->relation);
	free(graph);

	return 0;
}

int graph_add_edge(graph_t *graph, int vx, int vy)
{
#if 0
	((char(*)[graph->vn])graph->relation)[vx][vy] = 1;
	((char(*)[graph->vn])graph->relation)[vy][vx] = 1;
#else
	char (*relation)[graph->vn] = graph->relation;
	relation[vy][vx] = 1;
	relation[vx][vy] = 1;
#endif

	return 0;
}

int graph_show(graph_t *graph)
{
	int line,column;
	char (*relation)[graph->vn] = graph->relation;

	for (line = 0; line < graph->vn; line ++) {
		printf("%c: ", 'A' + line);
		for (column = 0; column < graph->vn; column ++) {
			if (relation[line][column])
				printf(" %c,", 'A' + column);
		}
		puts("\b ");
	}

	return 0;
}
