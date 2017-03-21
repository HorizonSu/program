#ifndef __EXPRESS_H__
#define __EXPRESS_H__

#include "stack.h"

extern int process_oprator(SeqStack *opdstack, SeqStack *optstack, int opt);
extern int compute(int opd1, int opd2, int opt);
extern int priority(int operator);
extern int express(char *buff);

#endif
