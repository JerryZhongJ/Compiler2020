#ifndef __MIPS32__
#define __MIPS32__
#include"InterCode.h"
#define BLOCK_END 0x80000000
typedef struct ShowRecord{
    // + for reference, - for assign or BLOCK_END
    int lineno;
    struct ShowRecord *next;
} ShowRecord;
void preprocess();
void process(FILE *file);
#endif