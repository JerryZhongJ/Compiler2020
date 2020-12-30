#ifndef __MIPS32__
#define __MIPS32__
#include"InterCode.h"

extern struct Operand_;
typedef struct ARGList {
    struct Operand_* arg;
    struct ARGList *next;
} ARGList;

typedef struct RefRecord{
    // + for reference, - for assign
    int lineno;
    struct RefRecord *next;
} RefRecord;
void preprocess();
void process();
#endif