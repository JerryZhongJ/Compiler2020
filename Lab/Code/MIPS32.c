#include"InterCode.h"
#include<stdlib.h>
#include"assert.h"
#include<stdio.h>
// Caller 2-3, 8-15, 24-25
// Callee 4-7, 16-23, 
Operand REGS[32];
int sp_offset;
static FILE* f;

void overflow(int reg_num) {
    if (REGS[reg_num] == NULL) return;
    assert(REGS[reg_num]->type == OPR_VARIABLE);
    if (REGS[reg_num]->var_mem == 0) {
        // this only happen when var is a temporary variable
        assert(REGS[reg_num]->var_tmp == 1);
        sp_offset += 4;
        REGS[reg_num]->var_mem = sp_offset;
    }
    fprintf(f, "subu $sp, $sp, 4\n");
    fprintf(f, "sw $%d, ($sp)\n", reg_num);
}
// allocate in the order of reg_num
int allocate(int lineno, Operand var, bool load) {
    assert(var->type == OPR_VARIABLE);
    // allocate reg for var
    if (var->var_reg != -1) return var->var_reg;
    int chosen = -1;
    int farrest = 0;
    
    for (int i = 2; i <= 23; i++) {
        if (REGS[i] == NULL || REGS[i]->var_refrec->lineno < 0){
            chosen = i;
            break;
        }else if(chosen == -1 ||REGS[i]->var_refrec->lineno - lineno > farrest){
                chosen = i;
                farrest = REGS[i]->var_refrec->lineno - lineno;
        }
    }
    // chosen reg is being used
    if(REGS[chosen] != NULL){
        // overflow only if the value in chosen reg is active
        if (REGS[chosen]->var_refrec->lineno > 0) overflow(chosen);
        REGS[chosen]->var_reg = -1;
    }
    REGS[chosen] = var;
    var->var_reg = chosen;
    return chosen;
}
void preprocess(){
    // code involving const
    // move the dec to the function
    // change all the duplicate label name to the same (the last one)
    InterCode* func_head;
    for (InterCode* c = codes; c != NULL; c = c->next) {
         switch(c->type){
             case CODE_LABEL:
                 for (InterCode* d = c->next; d->type == CODE_LABEL;d = d->next)
                     c->label.label_name->label_no =
                         d->label.label_name->label_no;
                 break;
            case CODE_FUNC:
            case CODE_PARAM:
                func_head = c;
                break;
            case CODE_MUL:
            case CODE_DIV:
                if(c->mul.op2->type == OPR_CONST){
                    Operand t = getVarName(true);
                    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
                    tmp->type = CODE_ASSIGN;
                    tmp->assign.left = t;
                    tmp->assign.right = c->mul.op2;
                    tmp->prev = c->prev;
                    tmp->next = c;
                    c->prev->next = tmp;
                    c->prev = tmp;
                    c->mul.op2 = t;
                }
                // do not break, continue to process op1
            case CODE_PLUS:
            case CODE_SUB:
                if(c->plus.op1->type == OPR_CONST){
                    Operand t = getVarName(true);
                    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
                    tmp->type = CODE_ASSIGN;
                    tmp->assign.left = t;
                    tmp->assign.right = c->plus.op1;
                    tmp->prev = c->prev;
                    tmp->next = c;
                    c->prev->next = tmp;
                    c->prev = tmp;
                    c->mul.op1 = t;
                }
                break;
            case CODE_DEC:
                if(c->prev != func_head){
                InterCode* tmp = c->prev;
                c->prev->next = c->next;
                c->next->prev = c->prev;

                c->prev = func_head;
                c->next = func_head->next;

                func_head->next->prev = c;
                func_head->next = c;

                c = tmp;
            }
                break;
         }
    }
}

InterCode* funcProcess(InterCode *start) { sp_offset = 0; }

InterCode* blockProcess(InterCode *start) {
    // remember not generate duplicate label
}

void process(FILE* file) { f = file; }
