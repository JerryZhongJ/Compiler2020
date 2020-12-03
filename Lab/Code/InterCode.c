#include<stdlib.h>
#include"InterCode.h"
#include<stdio.h>
#include<assert.h>

InterCode* codes = NULL;
InterCode *tail = NULL;
Operand entry;
Operand getVarName() {
    static int no = 0;
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->kind = OPR_VARIABLE;
    opr->var_no = no++;
    return opr;
}
Operand getTmpVarName(){
    static int no = 0;
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->kind = OPR_TMP;
    opr->tmp_no = no++;
    opr->used = false;
    return opr;
}
Operand getConst(int value) { 
    Operand opr = (Operand)malloc(sizeof(struct Operand_)); 
    opr->kind = OPR_CONST;
    opr->const_value = value;
    return opr;
}
Operand getLabel(){
    static int no = 0;
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->kind = OPR_LABEL;
    opr->label_no = no++;
    opr->ref_num = 0;
    return opr;
}
Operand getRef(Operand refered){
    assert(refered->kind == OPR_VARIABLE || refered->kind ==  OPR_TMP);
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->kind = OPR_REF;
    opr->refered = refered;
    return opr;
}
void genCode1(int kind, Operand opr) {
    assert(opr != NULL);
    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
    tmp->kind = kind;
    switch(kind){
        case CODE_JMP:
            opr->ref_num++;
        case CODE_LABEL:
        case CODE_FUNC:
            assert(opr->kind == OPR_LABEL);
            tmp->func.label_name = opr;
            break;
        case CODE_RET:
        case CODE_ARG:
        case CODE_PARAM:
        case CODE_READ:
        case CODE_WRITE:
            assert(opr->kind == OPR_VARIABLE || opr->kind == OPR_TMP ||
                    opr->kind == OPR_CONST || opr->kind == OPR_REF);
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
void genCode2(int kind, Operand left, Operand right) {
    assert(right != NULL && left != NULL );
    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
    tmp->kind = kind;
    switch(kind){
        case CODE_CALL:
            assert(right->kind == OPR_LABEL);
            right->ref_num++;
            tmp->assign.left = left;
            tmp->assign.right = right;
            break;
        case CODE_ASSIGN_FROM:
            assert(right->kind == OPR_VARIABLE || right->kind == OPR_TMP);
        case CODE_ASSIGN_INTO:
        case CODE_ASSIGN:
            assert(left->kind == OPR_VARIABLE || left->kind == OPR_TMP);
            assert(right->kind == OPR_VARIABLE || right->kind == OPR_TMP ||
                right->kind == OPR_CONST || right->kind == OPR_REF);
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
void genCode3(int kind, Operand res, Operand opr1, Operand opr2){
    assert(res != NULL && opr1 != NULL && opr2 != NULL);
    InterCode *tmp = (InterCode *)malloc(sizeof(InterCode));
    tmp->kind = kind;
    assert(res->kind == OPR_VARIABLE || res->kind == OPR_TMP);
    assert(opr1->kind == OPR_VARIABLE || opr1->kind == OPR_TMP ||
           opr1->kind == OPR_CONST || opr1->kind == OPR_REF);
    assert(opr2->kind == OPR_VARIABLE || opr2->kind == OPR_TMP ||
           opr2->kind == OPR_CONST || opr2->kind == OPR_REF);
    switch (kind) {
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
void genCode4(int kind, Operand opr1, Operand opr2, int relop, Operand label_name){
    assert(kind == CODE_COND_JMP);
    assert(opr1 != NULL && opr2 != NULL && label_name != NULL);
    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
    tmp->kind = kind;
    assert(opr1->kind == OPR_VARIABLE || opr1->kind == OPR_TMP ||
           opr1->kind == OPR_CONST || opr1->kind == OPR_REF);
    assert(opr2->kind == OPR_VARIABLE || opr2->kind == OPR_TMP ||
           opr2->kind == OPR_CONST || opr2->kind == OPR_REF);
    tmp->cond_jmp.op1 = opr1;
    tmp->cond_jmp.op2 = opr2;
    tmp->cond_jmp.relop = relop;
    tmp->cond_jmp.label_name = label_name;
    label_name->ref_num++;
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
    tmp->kind = CODE_DEC;
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
    switch (opr->kind) {
        case OPR_VARIABLE:
            fprintf(f, "v%d", opr->var_no);
            break;
        case OPR_TMP:
            fprintf(f, "t%d", opr->tmp_no);
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
        default:
            assert(0);
    }
}

void printCode(FILE *f) { 
    for (InterCode *line = codes; line != NULL;line = line->next){
        switch(line->kind){
            case CODE_LABEL:
                fprintf(f, "LABEL ");
                printOperand(f, line->label.label_name);
                fprintf(f, " :\n");
                break;
            case CODE_FUNC:
                fprintf(f, "FUNCTION ");
                printOperand(f, line->label.label_name);
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