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
        if (REGS[i] == NULL || REGS[i]->var_refrec == NULL ||
                REGS[i]->var_refrec->lineno < 0) {
            chosen = i;
            break;
        } else if (chosen == -1 ||
                   REGS[i]->var_refrec->lineno - lineno > farrest) {
            chosen = i;
            farrest = REGS[i]->var_refrec->lineno - lineno;
        }
    }
    // chosen reg is being used
    if(REGS[chosen] != NULL){
        // overflow only if the value in chosen reg is active
        if (REGS[chosen]->var_refrec != NULL && REGS[chosen]->var_refrec->lineno > 0)
            overflow(chosen);
        REGS[chosen]->var_reg = -1;
    }
    REGS[chosen] = var;
    var->var_reg = chosen;
    if(load){
        assert(var->var_mem != 0);
        fprintf(f, "lw $%d, %d($fp)\n", chosen, -var->var_mem);
    }
    return chosen;
}
static inline bool isActive(Operand var){
    assert(var->type == OPR_VARIABLE);
    return var->var_refrec != NULL && var->var_refrec->lineno > 0;
}
static inline bool notInitialized(Operand var, int tail_lineno){
    assert(var->type == OPR_VARIABLE);
    return var->var_tmp == false && (var->var_refrec == NULL || var->var_refrec->lineno != tail_lineno);
}
static inline bool isEOB(InterCode *c){    //is end of block
    return tail->type != CODE_JMP || tail->type != CODE_COND_JMP ||
           tail->type != CODE_LABEL || tail->type != CODE_RET;
}
static inline void appendRefRec(Operand var, int lineno, bool assign){
    assert(var->type == OPR_VARIABLE);
    RefRecord* rr = (RefRecord*)malloc(sizeof(RefRecord));
    rr->lineno = (assign ? -1 : +1) * lineno;
    rr->next = var->var_refrec;
    var->var_refrec = rr;
}

void preprocess(){
    // code involving const
    // move the dec to the function
    // change all the duplicate label_no to the same (the first label_no)
    InterCode* func_head;
    for (InterCode* c = codes; c != NULL; c = c->next) {
         switch(c->type){
             case CODE_LABEL:
                 assert(c->prev != NULL);
                 if (c->prev->type == CODE_LABEL) {
                     c->label.label_name->label_no =
                         c->prev->label.label_name->label_no;
                    InterCode* tmp = c->prev;
                    c->prev->next = c->next;
                    c->next->prev = c->prev;
                    free(c);
                    c = tmp;
                 }
                 break;
            case CODE_FUNC:
            case CODE_PARAM:
                func_head = c;
                break;
            case CODE_ASSIGN_INTO:
                if(c->assign_into.right->type == OPR_CONST || c->assign_into.right->type == OPR_REF){
                    Operand t = getVarName(true);
                    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
                    tmp->type = CODE_ASSIGN;
                    tmp->assign.left = t;
                    tmp->assign.right = c->assign_into.right;
                    tmp->prev = c->prev;
                    tmp->next = c;
                    c->prev->next = tmp;
                    c->prev = tmp;
                    c->assign_into.right = t;
                }
                break;
            case CODE_MUL:
            case CODE_DIV:
                if(c->mul.op2->type == OPR_CONST || c->mul.op2->type == OPR_REF){
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
                if(c->plus.op1->type == OPR_CONST || c->plus.op1->type == OPR_REF){
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
    int lineno = 0;
    for (InterCode* c = codes; c != NULL;lineno++, c = c->next)
        c->lineno = lineno++;
}
InterCode *blockPreprocess(InterCode *tail, int *max_active){
    assert(isEOB(tail));
    int active_num = 0;
    if (tail->type != CODE_RET) {
        if(tail->type == CODE_COND_JMP){
            appendRefRec(tail->cond_jmp.op1, tail->lineno, false);
            appendRefRec(tail->cond_jmp.op2, tail->lineno, false);
            active_num = 2;
        }
        // for every assigned local variable (not temporary)
        // we consider it as it is used at the end of the block !
        // every assigned local variable should be counted for once.
        for (InterCode* c = tail; !isEOB(c);c = c->prev){
            switch(c->type){
                case CODE_ASSIGN:
                case CODE_ASSIGN_FROM:
                    if(notInitialized(c->assign.left, tail->lineno)){
                        appendRefRec(c->assign.left, tail->lineno, false);
                        active_num++;
                    }
                    break;
                case CODE_PLUS:
                case CODE_SUB:
                case CODE_MUL:
                case CODE_DIV:
                    if(notInitialized(c->plus.res, tail->lineno)){
                        appendRefRec(c->plus.res, tail->lineno, false);
                        active_num++;
                    }
                    break;
                case CODE_CALL:
                    if(notInitialized(c->call.left, tail->lineno)){
                        appendRefRec(c->call.left, tail->lineno, false);
                        active_num++;
                    }
                    break;
            }
        } 
    }else{
        appendRefRec(tail->ret.op, tail->lineno, false);
        active_num++;
    }
    *max_active = active_num;
    InterCode* c;
    for (c = tail->prev; !isEOB(c); c = c->prev){
        // assign prior than use 
        switch(c->type){
            case CODE_ASSIGN:
            case CODE_ASSIGN_FROM:
                if (isActive(c->assign.left)) active_num--;
                appendRefRec(c->assign.left, c->lineno, true);

                if(c->assign.right->type == OPR_VARIABLE){
                    if (!isActive(c->assign.right)) active_num++;
                    appendRefRec(c->assign.right, c->lineno, false);
                }
                break;
            case CODE_PLUS:
            case CODE_SUB:
            case CODE_MUL:
            case CODE_DIV:
                if (isActive(c->plus.res)) active_num--;
                appendRefRec(c->plus.res, c->lineno, true);

                if (!isActive(c->plus.op1)) active_num++;
                appendRefRec(c->plus.op1, c->lineno, false);

                if(c->plus.op2->type == OPR_VARIABLE){
                    if (!isActive(c->plus.op2)) active_num++;
                    appendRefRec(c->plus.op2, c->lineno, false);
                }
                break;
            case CODE_ASSIGN_INTO:
                break;
        }
    }
    return c;
    }

InterCode* funcProcess(InterCode *start) {          // return the code after this function
    sp_offset = 0;  
    // function preprocess
    InterCode* tail = start;
    for (; tail != NULL && tail->type != CODE_RET;tail = tail->next)
        assert(tail->type != CODE_RET);

    
    return tail->next;
}
// block ends with "GOTO", "IF ... GOTO", "LABEL", "RETRUN", among them "RETURN" is special.
InterCode* blockProcess(InterCode *start) {
    // do nothing when block is empty!
    // const and reference only appear at the right side of assignment !
}

void process(FILE* file) { f = file; }
