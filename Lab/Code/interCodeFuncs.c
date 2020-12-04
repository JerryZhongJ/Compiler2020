#include "interCodeFucs.h"
Cond conds[CONDS_NUM];
//conds[0] means no condition
//conds[1] means goto func
int conds_idx = 0;
Logic_Node *address[2][LABEL_NUM];
void make_Logic_Link(InterCode *head)
{
    conds[0].constant = conds[1].constant = 1;
    InterCode *cur = head;
    BasicBlock bcur;
    int flcur = 0, ncur = 0;
    int state = 0;
    while (cur != NULL)
    {
        int no = 0;
        switch (cur->kind)
        {
        case CODE_FUNC:
        {
            bcur.head = NULL;
            state = CODE_FUNC;
            NEW_LOGIC_NODE(tmp)
            tmp->funcORlabel = FUNC_ADDRESS;
            flcur = FUNC_ADDRESS;
            ncur = cur->label.label_name->label_no;
            address[flcur][ncur] = tmp;
        }
        break;
        case CODE_LABEL:
        {
            bcur.head = NULL;
            state = CODE_LABEL;
            NEW_LOGIC_NODE(tmp);
            no = cur->label.label_name->label_no;
            //needs link this node in some condition
            if (state != CODE_JMP && state != CODE_RET)
            {
                if (state == CODE_COND_JMP)
                {
                    address[flcur][ncur]->false_next_no = no;
                }
                else
                {
                    address[flcur][ncur]->true_next_no = no;
                }
                address[flcur][ncur]->next_funcORlabel = LABEL_ADDRESS;
            }
            ncur = no;
            flcur = LABEL_ADDRESS;
            address[flcur][ncur] = tmp;
        }
        break;
        case CODE_JMP:
        {
            bcur.head = NULL;
            state = CODE_JMP;
            no = cur->jmp.label_name->label_no;
            address[flcur][ncur]->next_funcORlabel = LABEL_ADDRESS;
            address[flcur][ncur]->true_next_no = no;
        }
        break;
        case CODE_RET:
        {
            bcur.head = NULL;
            state = CODE_RET;
        }
        break;
        case CODE_CALL:
        {
            bcur.head = NULL;
            state = CODE_CALL;
            no = cur->func.label_name->label_no;
            address[flcur][ncur]->cond_no = GOTO_FUNC;
            address[flcur][ncur]->true_next_no = no;
            address[flcur][ncur]->next_funcORlabel = FUNC_ADDRESS;
            ncur = no;
            flcur = FUNC_ADDRESS;
        }
        break;
        case CODE_COND_JMP:
        {
            bcur.head = NULL;
            state = CODE_COND_JMP;
            no = cur->cond_jmp.label_name->label_no;
            address[flcur][ncur]->cond_no = conds_idx;
            Cond c = {cur->cond_jmp.op1, cur->cond_jmp.op2, cur->cond_jmp.relop, -1};
            conds[conds_idx++] = c;
            address[flcur][ncur]->true_next_no = cur->cond_jmp.label_name->label_no;
            address[flcur][ncur]->next_funcORlabel = LABEL_ADDRESS;
        }
        break;
        default:
        {
            if (bcur.head == NULL)
            {
                address[flcur][ncur]->basic_block = bcur;
                bcur.head = cur;
            }
            else
            {
                bcur.tail = cur;
            }
        }
        break;
        }
        cur = cur->next;
    }
}

#define CONST_EXPR_BETTER(opr)                                                         \
    do                                                                                 \
    {                                                                                  \
        if (cur->opr.op1->kind == OPR_CONST && cur->opr.op2->kind == OPR_CONST)        \
        {                                                                              \
            cur->kind = CODE_ASSIGN;                                                   \
            cur->assign.left = cur->opr.res;                                           \
            cur->assign.right = cur->opr.op1->const_value / cur->opr.op2->const_value; \
        }                                                                              \
    } while (0)

#define REGIST_CONST_VAL(const_operand)                      \
    do                                                       \
    {                                                        \
        tmpValsPtrs[const_operand->var_no] = &vals[idx];     \
        vals[idx].no.const_val = const_operand->const_value; \
        vals[idx++].kind = CONST_VAR;                        \
    } while (0)

#define REGIST_VAL(operand_left, operand_right)         \
    do                                                  \
    {                                                   \
        tmpValsPtrs[operand_left->var_no] = &vals[idx]; \
        vals[idx].no.var_no = operand_right->var_no;    \
        vals[idx++].kind = VAR;                         \
    } while (0);

#define CHECK_AND_SET_VAL(operand)                                                 \
    do                                                                             \
    {                                                                              \
        if (tmpValsPtrs[operand->var_no] != NULL)                                  \
        {                                                                          \
            if (tmpValsPtrs[operand->var_no]->kind == CONST_VAR)                   \
            {                                                                      \
                operand->kind = OPR_CONST;                                         \
                operand->const_value = tmpValsPtrs[operand->var_no]->no.const_val; \
            }                                                                      \
            else if (tmpValsPtrs[operand->var_no]->kind == VAR)                    \
            {                                                                      \
                operand->var_no = tmpValsPtrs[operand->var_no]->no.var_no;         \
            }                                                                      \
        }                                                                          \
    } while (0)

#define MIN(v1, v2) ((v1 < v2) ? v1 : v2)
#define VAR_NUM_BITS 7
#define VAR_NUM 1 << VAR_NUM_BITS
#define VAR_EXPR 1 << (VAR_NUM_BITS + VAR_NUM_BITS + 1)
#define BOTH_VAR 1
#define ONE_CONST 0
#define TWIN_NO(vno1, vno2, both_var) ((((MIN(vno1, vno2) << VAR_NUM_BITS) | MIN(vno1, vno2)) << 1) | both_var)

#define EXPR_PROCESS(expr)                                                                                                         \
    do                                                                                                                             \
    {                                                                                                                              \
        if (cur->expr.op1->kind == OPR_CONST && cur->expr.op2->kind == OPR_CONST)                                                  \
        {                                                                                                                          \
            cur->kind = CODE_ASSIGN;                                                                                               \
            cur->assign.right = cur->expr.op1->const_value + cur->expr.op2->const_value;                                           \
        }                                                                                                                          \
        else                                                                                                                       \
        {                                                                                                                          \
            if (cur->expr.op1->kind != OPR_CONST)                                                                                  \
            {                                                                                                                      \
                CHECK_AND_SET_VAL(cur->expr.op1);                                                                                  \
            }                                                                                                                      \
            if (cur->expr.op2->kind != OPR_CONST)                                                                                  \
            {                                                                                                                      \
                CHECK_AND_SET_VAL(cur->expr.op2);                                                                                  \
            }                                                                                                                      \
            if (cur->expr.op1 != OPR_CONST && cur->expr.op2 != OPR_CONST)                                                          \
            {                                                                                                                      \
                if (twinValsPtrs[TWIN_NO(cur->expr.op1->var_no, cur->expr.op2->var_no, BOTH_VAR)] != NULL)                         \
                {                                                                                                                  \
                    cur->kind = CODE_ASSIGN;                                                                                       \
                    cur->assign.left = cur->expr.res;                                                                              \
                    cur->assign.right = twinValsPtrs[TWIN_NO(cur->expr.op1->var_no, cur->expr.op2->var_no, BOTH_VAR)]->no.var_no;  \
                }                                                                                                                  \
                else                                                                                                               \
                {                                                                                                                  \
                    twinValsPtrs[TWIN_NO(cur->expr.op1->var_no, cur->expr.op2->var_no, BOTH_VAR)] = &twinVals[tidx];               \
                    twinVals[idx++].no.var_no = cur->expr.res->var_no;                                                             \
                }                                                                                                                  \
            }                                                                                                                      \
            else                                                                                                                   \
            {                                                                                                                      \
                if (twinValsPtrs[TWIN_NO(cur->expr.op1->var_no, cur->expr.op2->var_no, ONE_CONST)] != NULL)                        \
                {                                                                                                                  \
                    cur->kind = CODE_ASSIGN;                                                                                       \
                    cur->assign.left = cur->expr.res;                                                                              \
                    cur->assign.right = twinValsPtrs[TWIN_NO(cur->expr.op1->var_no, cur->expr.op2->var_no, ONE_CONST)]->no.var_no; \
                }                                                                                                                  \
                else                                                                                                               \
                {                                                                                                                  \
                    twinValsPtrs[TWIN_NO(cur->expr.op1->var_no, cur->expr.op2->var_no, ONE_CONST)] = &twinVals[tidx];              \
                    twinVals[idx++].no.var_no = cur->expr.res->var_no;                                                             \
                }                                                                                                                  \
            }                                                                                                                      \
        }                                                                                                                          \
    } while (0)
void compileTimeValueBetter(BasicBlock b)
{
    Var *tmpValsPtrs[VAR_NUM]; //point to vals
    Var vals[VAR_NUM];
    Var *twinValsPtrs[VAR_EXPR];
    Var twinVals[VAR_EXPR];
    int idx = 0;
    int tidx = 0;
    InterCode *cur = b.head;
    for (int i = 0; i < 100; ++i)
    {
        tmpValsPtrs[i] = NULL;
    }
    while (cur != b.tail)
    {
        switch (cur->kind)
        {

        case CODE_ASSIGN:
        CODE_ASSIGN_INTO:
        {
            if (cur->assign.right->kind == OPR_CONST)
            {
                REGIST_CONST_VAL(cur->assign.left);
            }
            else
            {
                CHECK_AND_SET_VAL(cur->assign.right);
                REGIST_VAL(cur->assign.left, cur->assign.right);
            }
        }
        break;
        case CODE_PLUS:
        {
            EXPR_PROCESS(plus);
        }
        break;
        case CODE_SUB:
        {
            EXPR_PROCESS(sub);
        }
        break;
        case CODE_MUL:
        {
            EXPR_PROCESS(mul);
        }
        break;
        case CODE_DIV:
        {
            EXPR_PROCESS(div);
        }
        break;
        default:
            break;
        }
    }
}
//TODO:我认定变量都有一个独自的var_no
//我没有处理取地址操作

void print_goto(int no)
{
    //GOTO LABEL <no>
}

void print_cond_goto(Cond c, int no_true, ...)
{
    //IF cond :GOTO no_true
    //(maybe) GOTO no_false
}

int const_cond(Cond c) //0:false 1:true,-1:undef
{
    if (c.op1->kind == OPR_CONST && c.op2->kind == OPR_CONST)
    {
        int res = c.op1->const_value - c.op2->const_value;
        switch (c.relop)
        {
        case EQ:
            return res == 0;
            break;
        case NOT_EQ:
            return res != 0;
            break;
        case LES_EQ:
            return res <= 0;
            break;
        case GRT:
            return res > 0;
            break;
        case GRT_EQ:
            return res >= 0;
            break;
        case LES:
            return res < 0;
            break;
        default:
            return -1;
            break;
        }
    }
    return -1;
}

#define CHECK_AND_PRINT(no)                                         \
    do                                                              \
    {                                                               \
        if (nmap[no] == NULL)                                       \
        {                                                           \
            basic_block_print(next->basic_block, no, NORMAL_LABEL); \
            nmap[no] = next;                                        \
        }                                                           \
        else                                                        \
        {                                                           \
            print_goto(no);                                         \
        }                                                           \
    } while (0)

void logic_print(Logic_Node *nmap[], Logic_Node *node)
{
    if (node->cond_no == NO_COND)
    {
        if (node->true_next_no == UNUSED_NO)
        {
            return;
        }
        Logic_Node *next = address[LABEL_ADDRESS][node->true_next_no];
        CHECK_AND_PRINT(node->true_next_no);
        logic_print(nmap, next);
    }
    else
    {
        int res = const_cond(conds[node->cond_no]);
        if (res == 1)
        {
            Logic_Node *next = address[LABEL_ADDRESS][node->true_next_no];
            CHECK_AND_PRINT(node->true_next_no);
            logic_print(nmap, next);
        }
        else if (res == 0)
        {
            Logic_Node *next = address[LABEL_ADDRESS][node->false_next_no];
            CHECK_AND_PRINT(node->false_next_no);
            logic_print(nmap, next);
        }
        else
        {
            Logic_Node *true_next = address[LABEL_ADDRESS][node->true_next_no];
            Logic_Node *false_next = address[LABEL_ADDRESS][node->false_next_no];
            if (nmap[node->true_next_no] != NULL && nmap[node->false_next_no] != NULL)
            {
                print_cond_goto(conds[node->cond_no], node->true_next_no, node->false_next_no);
            }
            else
            {
                if (nmap[node->true_next_no] == NULL)
                {
                    conds[node->cond_no].relop = -conds[node->cond_no].relop; //not operation
                    print_cond_goto(conds[node->cond_no], node->false_next_no);
                    basic_block_print(true_next->basic_block, node->true_next_no, NORMAL_LABEL);
                    nmap[node->cond_no] = true_next;
                }
                else
                {
                    print_cond_goto(conds[node->cond_no], node->true_next_no);
                    basic_block_print(false_next->basic_block, node->false_next_no, NORMAL_LABEL);
                    nmap[node->cond_no] = false_next;
                }
            }
            logic_print(nmap, true_next);
            logic_print(nmap, false_next);
        }
    }
}

void logic_print() //优化单入单出的节点，将其基本块和父节点合并，输出这张图
{
    for (int i = 0; i < LABEL_NUM; ++i)
    {
        if (address[FUNC_ADDRESS][i] != NULL)
        {
            Logic_Node *n_map[LABEL_NUM];
            for (int i = 0; i < LABEL_NUM; ++i)
            {
                n_map[i] = NULL;
            }
            basic_block_print(address[FUNC_ADDRESS][i]->basic_block, i, FUNC_LABEL);
            logic_print(n_map, address[FUNC_ADDRESS][i]);
        }
    }
}