
#include"common.h"
#include<stdio.h>
#include"Node.h"
#include"InterCode.h"
#include"MIPS32.h"
#define OFFSET 260
extern int yynerrs;
extern void yyrestart(FILE *);

SynUnit *start;

int main(int argc, char** argv){
    if (argc <= 1) return 1;
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    if (!input || !output) {
        perror(argv[1]);
        return 1;
    }
    yyrestart(input);
    yyparse();
    if (yynerrs == 0) {
        MakeObj(program, n0, emptyPPT);
        n0.creator(&n0, start);
        if (!n0.ppt.error) {
            // preprocess();
            // printCode(output);
            process(output);
        }
    }
    return 0;
}