#include<stdlib.h>
#include"InterCode.h"
#include<stdio.h>
#include<assert.h>
#include<string.h>

InterCode* codes = NULL;
InterCode *tail = NULL;
Operand entry;
Operand getVarName(bool tmp) {
    static int no = 0;
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->type = OPR_VARIABLE;
    opr->var_no = no++;
    opr->var_tmp = tmp;
    opr->var_reg = -1;
    opr->var_mem = 0;
    opr->var_refrec = NULL;
    return opr;
}

Operand getConst(int value) { 
    Operand opr = (Operand)malloc(sizeof(struct Operand_)); 
    opr->type = OPR_CONST;
    opr->const_value = value;
    return opr;
}
Operand getLabel(){
    static int no = 0;
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->type = OPR_LABEL;
    opr->label_no = no++;
    return opr;
}
Operand getRef(Operand refered){
    assert(refered->type == OPR_VARIABLE);
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->type = OPR_REF;
    opr->refered = refered;
    return opr;
}
Operand getFuncName(char *name){
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->type = OPR_FUNCNAME;
    opr->func_name = (char *)malloc(sizeof(strlen(name) + 1));
    strcpy(opr->func_name, name);
    return opr;
}

void genCode1(int type, Operand opr) {
    assert(opr != NULL);
    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
    tmp->type = type;
    switch(type){
        case CODE_JMP:
        case CODE_LABEL:
            assert(opr->type == OPR_LABEL);
            tmp->label.label_name = opr;
            break;
        case CODE_FUNC:
            assert(opr->type == OPR_FUNCNAME);
            tmp->func.funcname = opr;
            break;
        case CODE_RET:
        case CODE_ARG:
        case CODE_PARAM:
        case CODE_READ:
        case CODE_WRITE:
            assert(opr->type == OPR_VARIABLE || opr->type == OPR_CONST || opr->type == OPR_REF);
            tmp->write.op = opr;
            break;
        default:
            assert(0);
    }
    if(tail== NULL){
        tmp->prev = NULL;
        tmp->next = NULL;
        codes = tail = tmp;
    } else {
        tmp->next = NULL;
        tmp->prev = tail;
        tail = tail->next = tmp;
    }
}
void genCode2(int type, Operand left, Operand right) {
    assert(right != NULL && left != NULL );
    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
    tmp->type = type;
    switch(type){
        case CODE_CALL:
            assert(right->type == OPR_FUNCNAME);
            tmp->assign.left = left;
            tmp->assign.right = right;
            tmp->call.arg_list = NULL;
            break;
        case CODE_ASSIGN_FROM:
            assert(right->type == OPR_VARIABLE);
        case CODE_ASSIGN_INTO:
        case CODE_ASSIGN:
            assert(left->type == OPR_VARIABLE);
            assert(right->type == OPR_VARIABLE ||
                right->type == OPR_CONST || right->type == OPR_REF);
            tmp->assign.left = left;
            tmp->assign.right = right;
            break;
        default:
            assert(0);
    }
    if(tail== NULL){
        tmp->prev = NULL;
        tmp->next = NULL;
        codes = tail = tmp;
    } else {
        tmp->next = NULL;
        tmp->prev = tail;
        tail = tail->next = tmp;
    }
}
void genCode3(int type, Operand res, Operand opr1, Operand opr2){
    assert(res != NULL && opr1 != NULL && opr2 != NULL);
    InterCode *tmp = (InterCode *)malloc(sizeof(InterCode));
    tmp->type = type;
    assert(res->type == OPR_VARIABLE);
    assert(opr1->type == OPR_VARIABLE ||
           opr1->type == OPR_CONST || opr1->type == OPR_REF);
    assert(opr2->type == OPR_VARIABLE ||
           opr2->type == OPR_CONST || opr2->type == OPR_REF);
    switch (type) {
        case CODE_PLUS:
        case CODE_SUB:
        case CODE_MUL:
        case CODE_DIV:
            tmp->div.res = res;
            tmp->div.op1 = opr1;
            tmp->div.op2 = opr2;
            break;
        default:
            assert(0);
    }
    if(tail== NULL){
        tmp->prev = NULL;
        tmp->next = NULL;
        codes = tail = tmp;
    } else {
        tmp->next = NULL;
        tmp->prev = tail;
        tail = tail->next = tmp;
    }
}
void genCode4(int type, Operand opr1, Operand opr2, int relop, Operand label_name){
    assert(type == CODE_COND_JMP);
    assert(opr1 != NULL && opr2 != NULL && label_name != NULL);
    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
    tmp->type = type;
    assert(opr1->type == OPR_VARIABLE ||
           opr1->type == OPR_CONST || opr1->type == OPR_REF);
    assert(opr2->type == OPR_VARIABLE ||
           opr2->type == OPR_CONST || opr2->type == OPR_REF);
    tmp->cond_jmp.op1 = opr1;
    tmp->cond_jmp.op2 = opr2;
    tmp->cond_jmp.relop = relop;
    tmp->cond_jmp.label_name = label_name;
    if (tail == NULL) {
        tmp->prev = NULL;
        tmp->next = NULL;
        codes = tail = tmp;
    } else {
        tmp->next = NULL;
        tmp->prev = tail;
        tail = tail->next = tmp;
    }
}
void genCodeDec(Operand op, int size){
    InterCode *tmp = (InterCode *)malloc(sizeof(InterCode));
    tmp->type = CODE_DEC;
    tmp->dec.op = op;
    tmp->dec.size = size;
    if(tail== NULL){
        tmp->prev = NULL;
        tmp->next = NULL;
        codes = tail = tmp;
    } else {
        tmp->next = NULL;
        tmp->prev = tail;
        tail = tail->next = tmp;
    }
}

void printOperand(FILE* f, Operand opr){
    assert(opr != NULL);
    switch (opr->type) {
        case OPR_VARIABLE:
            fprintf(f, "v%d", opr->var_no);
            break;
        case OPR_CONST:
            fprintf(f, "#%d", opr->const_value);
            break;
        case OPR_LABEL:
            if (entry == opr) fprintf(f, "main");
            else fprintf(f, "label%d", opr->label_no);
            break;
        case OPR_REF:
            fprintf(f, "&");
            printOperand(f, opr->refered);
            break;
        case OPR_FUNCNAME:
            fprintf(f, "%s", opr->func_name);
            break;
        default:
            assert(0);
    }
}

void printCode(FILE *f) {
    fprintf(f, "FUNCTION read :\nREAD r\nRETURN r\n");
    fprintf(f, "FUNCTION write :\nPARAM w\nWRITE w\nRETURN #0\n");
    for (InterCode *line = codes; line != NULL; line = line->next) {
        switch(line->type){
            case CODE_LABEL:
                fprintf(f, "LABEL ");
                printOperand(f, line->label.label_name);
                fprintf(f, " :\n");
                break;
            case CODE_FUNC:
                fprintf(f, "FUNCTION ");
                printOperand(f, line->func.funcname);
                fprintf(f, " :\n");
                break;
            case CODE_ASSIGN:
                printOperand(f, line->assign.left);
                fprintf(f, " := ");
                printOperand(f, line->assign.right);
                fprintf(f, "\n");
                break;
            case CODE_PLUS:
                printOperand(f, line->plus.res);
                fprintf(f, " := ");
                printOperand(f, line->plus.op1);
                fprintf(f, " + ");
                printOperand(f, line->plus.op2);
                fprintf(f, "\n");
                break;
            case CODE_SUB:
                printOperand(f, line->sub.res);
                fprintf(f, " := ");
                printOperand(f, line->sub.op1);
                fprintf(f, " - ");
                printOperand(f, line->sub.op2);
                fprintf(f, "\n");
                break;
            case CODE_MUL:
                 printOperand(f, line->mul.res);
                fprintf(f, " := ");
                printOperand(f, line->mul.op1);
                fprintf(f, " * ");
                printOperand(f, line->mul.op2);
                fprintf(f, "\n");
                break;
            case CODE_DIV:
                printOperand(f, line->div.res);
                fprintf(f, " := ");
                printOperand(f, line->div.op1);
                fprintf(f, " / ");
                printOperand(f, line->div.op2);
                fprintf(f, "\n");
                break;
            case CODE_ASSIGN_FROM:
                printOperand(f, line->assign_from.left);
                fprintf(f, " := ");
                fprintf(f, "*");
                printOperand(f, line->assign_from.right);
                fprintf(f, "\n");
                break;
            case CODE_ASSIGN_INTO:
                fprintf(f, "*");
                printOperand(f, line->assign_from.left);
                fprintf(f, " := ");
                printOperand(f, line->assign_from.right);
                fprintf(f, "\n");
                break;
            case CODE_JMP:
                fprintf(f, "GOTO ");
                printOperand(f, line->jmp.label_name);
                fprintf(f, "\n");
                break;
            case CODE_COND_JMP:
                fprintf(f, "IF ");
                printOperand(f, line->cond_jmp.op1);
                switch(line->cond_jmp.relop){
                    case EQ:
                        fprintf(f, " == ");
                        break;
                    case LES_EQ:
                        fprintf(f, " <= ");
                        break;
                    case GRT_EQ:
                        fprintf(f, " >= ");
                        break;
                    case LES:
                        fprintf(f, " < ");
                        break;
                    case GRT:
                        fprintf(f, " > ");
                        break;
                    case NOT_EQ:
                        fprintf(f, " != ");
                        break;
                    default:
                        assert(0);
                }
                printOperand(f, line->cond_jmp.op2);
                fprintf(f, " GOTO ");
                printOperand(f, line->cond_jmp.label_name);
                fprintf(f, "\n");
                break;
            case CODE_RET:
                fprintf(f, "RETURN ");
                printOperand(f, line->ret.op);
                fprintf(f, "\n");
                break;
            case CODE_DEC:
                fprintf(f, "DEC ");
                printOperand(f, line->dec.op);
                fprintf(f, " %d\n", line->dec.size);
                break;
            case CODE_ARG:
                fprintf(f, "ARG ");
                printOperand(f, line->arg.op);
                fprintf(f, "\n");
                break;
            case CODE_CALL:
                printOperand(f, line->call.left);
                fprintf(f, " := CALL ");
                printOperand(f, line->call.right);
                fprintf(f, "\n");
                break;
            case CODE_PARAM:
                fprintf(f, "PARAM ");
                printOperand(f, line->param.op);
                fprintf(f, "\n");
                break;
            case CODE_READ:
                fprintf(f, "READ ");
                printOperand(f, line->read.op);
                fprintf(f, "\n");
                break;
            case CODE_WRITE:
                fprintf(f, "WRITE ");
                printOperand(f, line->write.op);
                fprintf(f, "\n");
                break;
            default:
                assert(0);
        }
    }
}