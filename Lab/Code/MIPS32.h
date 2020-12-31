#ifndef __MIPS32__
#define __MIPS32__
#include"InterCode.h"

typedef struct RefRecord{
    // + for reference, - for assign
    int lineno;
    struct RefRecord *next;
} RefRecord;
void preprocess();
void process();
#endif