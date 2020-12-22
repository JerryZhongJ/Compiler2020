#include "storage.h"
#include <stdlib.h>
#define TMP_VAR_OPTION 1
#define VAR_OPTION 0
#define VAR_NUMS 1000
#define mmalloc(type, len) (type *)malloc(sizeof(type) * len)
typedef struct _Stor_Unit
{
    union
    {
        int regIdx;
        int offset;
        int val; //uncare
    };
} Stor_Unit;

static Stor_Unit *var_table[2][VAR_NUMS];

typedef struct _dNode
{
    int idx;
    struct _dNode *next;
    struct _dNode *pred;
} RegIdxNode;

static RegIdxNode unoccupiedQueueHead, *unoccupiedQueueHeadPtr, unoccupiedQueueTail, *unoccupiedQueueTailPtr;

static void push(int idx)
{
    unoccupiedQueueTailPtr->pred->next = mmalloc(RegIdxNode, 1);
    unoccupiedQueueTailPtr->pred->next->idx = idx;
    unoccupiedQueueTailPtr->pred->next->next = unoccupiedQueueTailPtr;
    unoccupiedQueueTailPtr->pred = unoccupiedQueueTailPtr->pred->next;
}

static int pop()
{
    if (unoccupiedQueueHeadPtr->next == unoccupiedQueueTailPtr)
    {
        return -1;
    }
    else
    {
        int res = unoccupiedQueueHeadPtr->next->idx;
        unoccupiedQueueHeadPtr->next = unoccupiedQueueTailPtr->next->next;
        free(unoccupiedQueueHeadPtr->next->pred);
        unoccupiedQueueHeadPtr->next->pred = unoccupiedQueueHeadPtr;
        return res;
    }
}

static int local_var_stack_element_nums;
#define ELEMENT_SIZE 4

static int _attach_memory(int is_temp_var, int _var_, int size)
{
    var_table[is_temp_var][_var_]->offset = local_var_stack_element_nums * ELEMENT_SIZE;
    local_var_stack_element_nums += size;
    return var_table[is_temp_var][_var_]->offset;
}

void initial_storage_module()
{
    local_var_stack_element_nums = 0;
    unoccupiedQueueHeadPtr = &unoccupiedQueueHeadPtr;
    unoccupiedQueueTailPtr = &unoccupiedQueueTail;
    unoccupiedQueueHeadPtr->next = unoccupiedQueueTailPtr;
    unoccupiedQueueTailPtr->pred = unoccupiedQueueHeadPtr;
    for (int i = R_T0; i <= R_T9; ++i)
    {
        push(i);
    }
    for (int i = R_S0; i <= R_S7; ++i)
    {
        push(i);
    }
    push(R_S8);
}
void free_storage_module()
{
    while(unoccupiedQueueHeadPtr->next!=unoccupiedQueueTailPtr)
    {
        unoccupiedQueueHeadPtr->next = unoccupiedQueueHeadPtr->next->next;
        free(unoccupiedQueueHeadPtr->next->pred);
    }
    unoccupiedQueueTailPtr->pred = unoccupiedQueueHeadPtr;
}

const char *get_reg_tag(int idx)
{
    return reg_tags[idx];
}

int check_attach_state(int is_temp_var, int _var_, int *is_in_reg)
{
    Stor_Unit *rec = var_table[is_temp_var][_var_];
    if (rec == NULL && is_temp_var)
    {
        rec = var_table[VAR_OPTION][_var_];
        if (rec == NULL)
        {
            if (is_in_reg)
            {
                *is_in_reg = 0;
            };
            return -1;
        }
        else
        {
            if (is_in_reg)
            {
                *is_in_reg = 0;
            };
            return rec->offset;
        }
    }
    else if (rec == NULL)
    {
        return -1;
    }
    else
    {
        if (is_in_reg)
        {
            *is_in_reg = is_temp_var;
        }
        return rec->val;
    }
}

int try_attach_reg(int temp_var_, int *ok)
{
    int res = pop();
    if (res == -1)
    {
        *ok = 0;
        return _attach_memory(TMP_VAR_OPTION, temp_var_, 1);
    }
    else
    {
        *ok = 1;
        var_table[TMP_VAR_OPTION][temp_var_] = mmalloc(Stor_Unit, 1);
        var_table[TMP_VAR_OPTION][temp_var_]->regIdx = res;
        return res;
    }
}

int attach_memory(int var_, int size)
{
    return _attach_memory(VAR_OPTION, var_, size);
}

int dis_attach_reg(int temp_var_)
{
    int in_reg = 1;
    int res = check_attach_state(in_reg,temp_var_,&in_reg);
    if(res != -1 && in_reg)
    {
        push(res);
        return 1;
    }
    return 0;
}
 