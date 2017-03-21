#include "stack.h"

#define STACK_SIZE	5
#define BUFF_SIZE	128

#define IS_DIGIT(CH)	(CH >= '0' && CH <= '9')

int process_oprator(SeqStack *opdstack, SeqStack *optstack, int opt);
int compute(int opd1, int opd2, int opt);
int priority(int operator);

int main()
{
	SeqStack *optstack = NULL,
			 *opdstack = NULL;
	char *buff = NULL;
	char *p = NULL;
	int opd1 = 0,
		opd2 = 0,
		opt = 0;

	optstack = creat_seqstack(STACK_SIZE);
	opdstack = creat_seqstack(STACK_SIZE);
	buff = malloc(BUFF_SIZE);

	p = fgets(buff, BUFF_SIZE, stdin);

	while('\n' != *p)
	{
		if(IS_DIGIT(*p))
		{
			while(IS_DIGIT(*p))
			{
				opd1 *= 10;
				opd1 += *p - '0';
				p ++;
			}
			push_seqstack(opdstack, opd1);
		}
		else
		{
#if STACK_DEBUG
			puts("opdstack:");
			_debug_seqstack_(opdstack);
#endif
			process_oprator(opdstack, optstack, *p);
			opd1 = 0;
			p ++;	
		}
	}
	while(0 == pop_seqstack(optstack, &opt))
	{
		pop_seqstack(opdstack, &opd2);
		pop_seqstack(opdstack, &opd1);
		opd1 = compute(opd1, opd2, opt);
		push_seqstack(opdstack, opd1);
	}
	gettop_seqstack(opdstack, &opd1);
	printf("%d\n", opd1);

	free_seqstack(opdstack);
	free_seqstack(optstack);
	free(buff);
	return 0;
}

int priority(int operator)
{
	switch(operator)
	{
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;
		default:
			return -1;
	}
}

int compute(int opd1, int opd2, int opt)
{
	switch(opt)
	{
		case '+':
			return opd1 + opd2;
		case '-':
			return opd1 - opd2;
		case '*':
			return opd1 * opd2;
		case '/':
			return opd1 / opd2;
		default:
			return 0;
	}
}

int process_oprator(SeqStack *opdstack, SeqStack *optstack, int curr_opt)
{
	int opt, opd1, opd2, result;
	
	while(1)
	{
#if STACK_DEBUG
		puts("optstack:");
		_debug_seqstack_(optstack);
#endif
		if( 0 != gettop_seqstack(optstack, &opt))
			break;
		if( priority(curr_opt) > priority(opt))
			break;
		pop_seqstack(opdstack, &opd2);	
		pop_seqstack(opdstack, &opd1);	
		pop_seqstack(optstack, &opt);
		result = compute(opd1, opd2, opt);
		push_seqstack(opdstack, result);
	}
	push_seqstack(optstack, curr_opt);

	return 0;
}
