#include <stdio.h>
#include <stdlib.h>

typedef struct _seqlist_{
	int clen;
	int tlen;
	int *data;
}seqlist_t;

seqlist_t *seqlist_init(int len);
int seqlist_free(seqlist_t *list);
int seqlist_insert(seqlist_t *list, int value);
int seqlist_show(seqlist_t *list);
int _seqlist_locate_(seqlist_t *list, int obj);
int seqlist_search(seqlist_t *list, int value);
int seqlist_modify(seqlist_t *list, int obj, int value);
int seqlist_delete(seqlist_t *list, int obj);

int main(int argc, const char *argv[])
{
	int num = 100;
	seqlist_t *list = NULL;
	int value;

	list = seqlist_init(10);

	while (-1 != seqlist_insert(list, num)) {
		num ++;
	}

	value = 1001;
	if (seqlist_search(list, value))
		printf("%d exists\n", value);
	else
		printf("%d NOT exists\n", value);
	
	seqlist_modify(list, 1090, 100);

	seqlist_delete(list, 1090);

	seqlist_show(list);
	seqlist_free(list);
	return 0;
}

seqlist_t *seqlist_init(int len)
{
	seqlist_t *list = NULL;

	list = (seqlist_t *)malloc(sizeof(seqlist_t));
	list->clen = 0;
	list->tlen = len;
	list->data = (int *)malloc(sizeof(int) * len);

	return list;
}


int seqlist_free(seqlist_t *list)
{
	free(list->data);
	free(list);

	return 0;
}

int seqlist_insert(seqlist_t *list, int value)
{
	if (list->clen >= list->tlen)
		return -1;
	list->data[list->clen++] = value;

	return 0;
}

int seqlist_show(seqlist_t *list)
{
	int index;
	
	printf("tlen: %d\t clen: %d\n", list->tlen, list->clen);

	for (index = 0; index < list->clen; index ++)
		printf("%5d", list->data[index]);
	putchar('\n');

	return 0;
}

int _seqlist_locate_(seqlist_t *list, int obj)
{
	int index;

	for (index = 0; index < list->clen; index ++) {
		if (list->data[index] == obj)
			return index;
	}
	return -1;
}

int seqlist_search(seqlist_t *list, int value)
{
	if (-1 == _seqlist_locate_(list, value))
		return 0;
	return 1;
}

int seqlist_modify(seqlist_t *list, int obj, int value)
{
	int position;
	
	if (-1 == (position = _seqlist_locate_(list, obj)))
		return -1;
	list->data[position] = value;

	return 0;
}

int seqlist_delete(seqlist_t *list, int obj)
{
	int position;
	int index;

	if (-1 == (position = _seqlist_locate_(list, obj)))
		return -1;

	for (index = position; index < list->clen - 1; index ++)
		list->data[index] = list->data[index + 1];
	list->clen --;

	return 0;
}
