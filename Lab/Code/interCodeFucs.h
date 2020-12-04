#ifndef __INTERCODEFUNCS_H__
#define __INTERCODEFUNCS_H__
#include"InterCode.h"
#include<stdlib.h>


#define BLOCK_CHILD_NUM 100
#define CONDS_NUM 100
#define LABEL_NUM 100
#define FUNC_NUM 20

#define mmalloc(type,len) (type*)malloc(sizeof(type)*len)

#define NO_COND 0
#define GOTO_FUNC 1

#define FUNC_ADDRESS 0
#define LABEL_ADDRESS 1
#define UNUSED_NO -1

#define NEW_LOGIC_NODE(name)\
 Logic_Node* name = mmalloc(Logic_Node,1);\
 name->cond_no = NO_COND;\
 name->funcORlabel = UNUSED_NO;\
 name->true_next_no = UNUSED_NO;\
 name->false_next_no = UNUSED_NO;\
 name->basic_block.head = NULL;\
 name->basic_block.tail = NULL;

struct Cond_{
    Operand op1,op2;
    int relop;
};

#define RUNTIME_DECIDE -1

typedef struct Cond_ Cond;

struct BasicBlock_{
    InterCode*head;
    InterCode*tail;
};
typedef struct BasicBlock_ BasicBlock;

struct Logic_Node_{
    BasicBlock basic_block;
    int cond_no;
    int funcORlabel;
    int next_funcORlabel;
    int true_next_no;
    int false_next_no;
};
typedef struct Logic_Node_ Logic_Node;

struct Var_{
    enum{
        CONST_VAR,
        VAR,
    }kind;
    union 
    {
        int const_val;
        int var_no;
    }no;
};
typedef struct Var_ Var;


void make_Logic_Link(InterCode*head);
void better_code(InterCode*head);

#define FUNC_LABEL 0
#define NORMAL_LABEL 1
void basic_block_print(BasicBlock block,int no,int which);

void logic_print();



#endif//__INTERCODEFUNCS_H__