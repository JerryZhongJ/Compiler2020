#include"InterCode.h"
#include<stdlib.h>
#include"assert.h"
#include<stdio.h>
// Caller 2-3, 8-15, 24-25
// Callee 4-7, 16-23, 
Operand REGS[32];
int sp_offset;
int reserved_area;
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
    
    for (int i = 2; i <= 25; i++) {
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
static inline void popRefRec(Operand var, int lineno){
    assert(var->type == OPR_VARIABLE && var->var_refrec != NULL);
    if(var->var_refrec->lineno < 0){
        assert(var->var_refrec->lineno == -lineno);
        RefRecord* tmp = var->var_refrec;
        var->var_refrec = var->var_refrec->next;
        free(tmp);
    }else{
        for (; var->var_refrec->lineno < lineno;){
            RefRecord* tmp = var->var_refrec;
            var->var_refrec = var->var_refrec->next;
            free(tmp);
        }
        assert(var->var_refrec->lineno == lineno);
        RefRecord* tmp = var->var_refrec;
        var->var_refrec = var->var_refrec->next;
        free(tmp);
    }
}
void preprocess(){
    // code involving const
    // move the dec to the function
    // change all the duplicate label_no to the same (the first label_no)
    InterCode* func_head;
    InterCode* tail;
    for (InterCode* c = codes; c != NULL; c = c->next) {
        tail = c;
        switch (c->type) {
            case CODE_LABEL:
                assert(c->prev != NULL);
                if (c->prev->type == CODE_LABEL) {
                    c->label.label_name->label_no =
                        c->prev->label.label_name->label_no;
                    InterCode* tmp = c->prev;
                    c->prev->next = c->next;
                    c->next->prev = c->prev;
                    free(c);
                    tail = c = tmp;
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
                    func_head = c;

                    tail = c = tmp;
                }else
                    func_head = c;
                break;
        }
    }
    // make all the args close to CALL
    // in case of ARG is an expression
    InterCode* args_top;
    for (InterCode* c = tail; c != NULL; c = c->prev){
        if (c->type == CODE_CALL) args_top = c;
        else if(c->type == CODE_ARG){
            if(c->next != args_top){
                InterCode* tmp = c->next;
                c->prev->next = c->next;
                c->next->prev = c->prev;

                c->prev = args_top->prev;
                c->next = args_top;

                args_top->prev->next = c;
                args_top->prev = c;
                args_top = c;

                tail = c = tmp;
            }
            else
                args_top = c;
        }
    }
    int lineno = 0;
    for (InterCode* c = codes; c != NULL;lineno++, c = c->next)
        c->lineno = lineno++;
}


InterCode* callProcess(InterCode *head){    // return the "CALL" line
    assert(head->type == CODE_ARG || head->type == CODE_CALL);

}

InterCode* blockPreprocess(InterCode *tail, int *max_active){
    assert(isEOB(tail));
    int active_num = 0;
    if (tail->type != CODE_RET) {
        if(tail->type == CODE_COND_JMP){
            appendRefRec(tail->cond_jmp.op1, tail->lineno, false);
            appendRefRec(tail->cond_jmp.op2, tail->lineno, false);
            active_num += 2;
        }
        // for every assigned local variable (not temporary)
        // we consider it as it is used at the end of the block !
        // every assigned local variable should be counted for once.
        for (InterCode* c = tail; !isEOB(c) && c->type != CODE_FUNC;c = c->prev){
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
    if (active_num > *max_active) *max_active = active_num;
    InterCode* c;
    for (c = tail->prev; !isEOB(c) && c->type != CODE_FUNC; c = c->prev){
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
            case CODE_ASSIGN_INTO:
                if (!isActive(c->assign_into.left)) active_num++;
                appendRefRec(c->assign_into.left, c->lineno, false);
                if (!isActive(c->assign_into.right)) active_num++;
                appendRefRec(c->assign_into.right, c->lineno, false);
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
                if (!isActive(c->assign_into.right)) active_num++;
                appendRefRec(c->assign_into.right, c->lineno, false);
                break;
            case CODE_ARG:
                if (!isActive(c->arg.op)) active_num++;
                appendRefRec(c->arg.op, c->lineno, false);
                break;
            case CODE_CALL:
                if (isActive(c->call.left)) active_num--;
                appendRefRec(c->call.left, c->lineno, true);
                break;
            
        }
        if (active_num > *max_active) *max_active = active_num;
    }
    return c;
}

// block ends with "GOTO", "IF ... GOTO", "LABEL", "RETRUN".
InterCode* blockProcess(InterCode *head) {      
    // do nothing when block is empty!
    // reference only appear at the right side of assignment !
    // when processing return, do not jmp!
    // when processing assign, right side is const 0
        // allocate $0
    if (isEOB(head->next)) return head->next; // empty block
    for (int i = 0; i < 32; i++) REGS[i] = NULL;
    // reset stack pointer
    fprintf(f, "la $sp, %d($fp)\n", -reserved_area);
    InterCode* c;
    for (c = head; !isEOB(c); c = c->next) {
        switch(c->type){
            case CODE_ASSIGN:
                switch(c->assign.right->type){
                    case OPR_VARIABLE:
                        int right = c->assign.right->var_reg;
                        popRefRec(c->assign.right, c->lineno);
                        int left = allocate(c->lineno, c->assign.left, false);
                        popRefRec(c->assign.left, c->lineno);

                        if(right == -1)
                            fprintf(f, "lw $%d, %d($fp)\n", left,
                                    -c->assign.right->var_mem);
                        else if(left != right){
                            fprintf(f, "move $%d, $%d\n", left, right);
                        }
                        // else do nothing
                        break;
                    case OPR_CONST:
                        if(c->assign.right->const_value == 0){
                            c->assign.left->var_reg = 0;
                        }else{
                            int left = allocate(c->lineno, c->assign.left, false);
                            popRefRec(c->assign.left, c->lineno);
                            fprintf(f, "li $%d, %d\n", left,
                                    c->assign.right->const_value);
                        }
                        break;
                    case OPR_REF:
                        Operand ref = c->assign.right->refered;
                        assert(ref->type == OPR_VARIABLE && ref->var_mem != 0);
                        int left = allocate(c->lineno, c->assign.left, false);
                        popRefRec(c->assign.left, c->lineno);

                        fprintf(f, "la $%d, %d($fp)\n", left, ref->var_mem);
                        break;
                    default:
                        assert(0);
                }
            case CODE_PLUS:
                if(c->plus.op2->type == OPR_VARIABLE){
                    int op1 = allocate(c->lineno, c->plus.op1, true);
                    int op2 = allocate(c->lineno, c->plus.op2, true);
                    popRefRec(c->plus.op1, c->lineno);
                    popRefRec(c->plus.op2, c->lineno);
                    int res = allocate(c->lineno, c->plus.res, false);
                    popRefRec(c->plus.res, c->lineno);
                    fprintf(f, "add $%d, $%d, $%d\n", res, op1, op2);
                }else if(c->plus.op2->type == OPR_CONST){
                    int op1 = allocate(c->lineno, c->plus.op1, true);
                    popRefRec(c->plus.op1, c->lineno);
                    int res = allocate(c->lineno, c->plus.res, false);
                    popRefRec(c->plus.res, c->lineno);
                    fprintf(f, "addi $%d, $%d, %d\n", res, op1, c->plus.op2->const_value);
                }else
                    assert(0);
                break;
            case CODE_SUB:
                if(c->sub.op2->type == OPR_VARIABLE){
                    int op1 = allocate(c->lineno, c->sub.op1, true);
                    int op2 = allocate(c->lineno, c->sub.op2, true);
                    popRefRec(c->sub.op1, c->lineno);
                    popRefRec(c->sub.op2, c->lineno);
                    int res = allocate(c->lineno, c->sub.res, false);
                    popRefRec(c->sub.res, c->lineno);
                    fprintf(f, "sub $%d, $%d, $%d\n", res, op1, op2);
                }else if(c->sub.op2->type == OPR_CONST){
                    int op1 = allocate(c->lineno, c->sub.op1, true);
                    popRefRec(c->sub.op1, c->lineno);
                    int res = allocate(c->lineno, c->sub.res, false);
                    popRefRec(c->sub.res, c->lineno);
                    fprintf(f, "addi $%d, $%d, %d\n", res, op1, - c->sub.op2->const_value);
                }else
                    assert(0);
                break;
            case CODE_MUL:
                int op1 = allocate(c->lineno, c->mul.op1, true);
                int op2 = allocate(c->lineno, c->mul.op2, true);
                popRefRec(c->mul.op1, c->lineno);
                popRefRec(c->mul.op2, c->lineno);
                int res = allocate(c->lineno, c->mul.res, false);
                popRefRec(c->mul.res, c->lineno);
                fprintf(f, "mul $%d, $%d, $%d\n", res, op1, op2);
                break;
            case CODE_DIV:
                int op1 = allocate(c->lineno, c->div.op1, true);
                int op2 = allocate(c->lineno, c->div.op2, true);
                popRefRec(c->div.op1, c->lineno);
                popRefRec(c->div.op2, c->lineno);
                int res = allocate(c->lineno, c->div.res, false);
                popRefRec(c->div.res, c->lineno);
                fprintf(f, "div $%d, $%d\n", op1, op2);
                fprintf(f, "mflo $%d\n", res);
                break;
            case CODE_ASSIGN_FROM:
                int right = allocate(c->lineno, c->assign.right, true);
                popRefRec(c->assign.right, c->lineno);
                int left = allocate(c->lineno, c->assign.left, false);
                popRefRec(c->assign.left, c->lineno);

                fprintf(f, "lw $%d, 0($%d)\n", left, right);
                break;
            case CODE_ASSIGN_INTO:
                int right = allocate(c->lineno, c->assign.right, true);
                int left = allocate(c->lineno, c->assign.left, true);
                popRefRec(c->assign.right, c->lineno);
                popRefRec(c->assign.left, c->lineno);

                fprintf(f, "sw $%d, 0($%d)", right, left);
                break;
            case CODE_ARG:
            case CODE_CALL:
                c = callProcess(c);
                break;
            default:
                assert(0);
        }
    }

    
    if(c->type != CODE_RET){
        // overflow all the regs
        for (int i = 2; i <= 25;i ++){
            if(REGS[i]->var_refrec != NULL &&
                REGS[i]->var_refrec->lineno > 0){
                    overflow(i);
                    popRefRec(REGS[i], c->lineno);
            }
        } 
    }
    // process EOB
    switch(c->type){
        case CODE_LABEL:
            fprintf(f, "L%d:\n", c->label.label_name->label_no);
            break;
        case CODE_JMP:
            fprintf(f, "j L%d\n", c->jmp.label_name->label_no);
            break;
        case CODE_COND_JMP:
            int op1 = allocate(c->lineno, c->cond_jmp.op1, true);
            int op2 = allocate(c->lineno, c->cond_jmp.op2, true);
            char* cond;
            switch(c->cond_jmp.relop){
                case EQ:
                    cond = "eq";
                    break;
                case NOT_EQ:
                    cond = "ne";
                    break;
                case GRT_EQ:
                    cond = "ge";
                    break;
                case LES_EQ:
                    cond = "le";
                    break;
                case GRT:
                    cond = "gt";
                    break;
                case LES:
                    cond = "lt";
                    break;
            }
            fprintf(f, "b%s $%d, $%d L%d\n", cond, op1, op2,
                    c->cond_jmp.label_name->label_no);
            break;
        case CODE_RET:
            if(c->ret.op->var_reg == -1)
                fprintf(f, "lw $v0, %d($fp)\n", -c->ret.op->var_mem);
            else
                fprintf(f, "move $v0, $%d\n", c->ret.op->var_reg);
            break;
        default:
            assert(0);
    }
    return c->next;
}
InterCode* funcProcess(InterCode *head) {          // return the code after this function
    
    // function preprocess
    InterCode* tail = head;
    for (; tail != NULL && tail->type != CODE_RET;tail = tail->next)
        assert(tail->type != CODE_FUNC);

    int max_active = 0;
    for (InterCode* c = tail;c != head; c = blockPreprocess(c, &max_active))
        ;
    
    // save context
    sp_offset = 0;  
    reserved_area = 0;
    fprintf(f, "subu $sp, $sp, 4\n");
    fprintf(f, "sw $fp, ($sp)\n");
    fprintf(f, "move $fp, $sp\n");
    // $a0 - $a3 [4, 7]
    for (int i = 0; i < max_active - 2 && i < 4;i++){
        reserved_area += 4;
        fprintf(f, "sw $%d, %d($fp)\n", 4 + i, -reserved_area);
    }
    // $s0 - $s7 [16, 23]
    for (int i = 0; i < max_active - 14 && i < 8;i++){
        reserved_area += 4;
        fprintf(f, "sw $%d, %d($fp)\n", 16 + i, -reserved_area);
    }

    InterCode* c = head;

    int param_num = 0;
    for (c = head; c->type == CODE_PARAM; c = c->next) {
        param_num++;
        c->param.op->var_mem = -param_num * 4;
    }
    // reserve space for local variables (non temporary)
    for (c = head; c->type == CODE_DEC; c = c->next) {
        reserved_area += c->dec.size;
        c->param.op->var_mem = reserved_area;
    }
    fprintf(f, "subu $sp, $sp, %d\n", reserved_area);

    // process main text
    for (; c != tail->next;c = blockProcess(c))
        ;
    
    //  restore context
    int tmp = 0;
    for (int i = 0; i < max_active - 2 && i < 4;i++){
        tmp += 4;
        fprintf(f, "lw $%d, %d($fp)\n", 4 + i, -tmp);
    }
    for (int i = 0; i < max_active - 14 && i < 8; i++) {
        tmp += 4;
        fprintf(f, "lw $%d, %d($fp)\n", 16 + i, -tmp);
    }
    fprintf(f, "move $sp, $fp\n");
    fprintf(f, "lw $fp, ($sp)");
    fprintf(f, "addi $sp, $sp, 4");
    // jmp
    return tail->next;
}



void process(FILE* file) { f = file; }
