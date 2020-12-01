#include "Node.h"
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"InterCode.h"

#define thisppt _this->ppt

//remember to delete type_inh at the end of function
//remember to delete type_syn when father has use it
// check sym_type after lookup
// ckeck copyExpr

static Operand getVarName(){
    static int no = 0;
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->kind = OPR_VARIABLE;
    opr->var_no = no++;
    return opr;
}
static Operand getTmpVarName(){
    static int no = 0;
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->kind = OPR_TMP;
    opr->tmp_no = no++;
    opr->used = false;
    return opr;
}
static Operand getConst(int value) { 
    Operand opr = (Operand)malloc(sizeof(struct Operand_)); 
    opr->kind = OPR_CONST;
    opr->const_value = value;
    return opr;
}
static Operand getLabel(){
    static int no = 0;
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->kind = OPR_LABEL;
    opr->label_no = no++;
    opr->ref_num = 0;
    return opr;
}
static Operand getRef(Operand refered){
    assert(refered->kind == OPR_VARIABLE || refered->kind ==  OPR_TMP);
    Operand opr = (Operand)malloc(sizeof(struct Operand_));
    opr->refered = refered;
    return opr;
}
InterCode *codes = NULL;
static InterCode *tail = NULL;
static void genCode1(int kind, Operand opr) {
    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
    tmp->kind = kind;
    switch(kind){
        case CODE_LABEL:
        case CODE_JMP:
        case CODE_FUNC:
            assert(opr->kind == OPR_LABEL);
            tmp->func.label_name = opr;
            break;
        case CODE_RET:
        case CODE_ARG:
        case CODE_PARAM:
        case CODE_READ:
        case CODE_WRITE:
            tmp->write.op = opr;
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
static void genCode2(int kind, Operand left, Operand right) {
    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
    tmp->kind = kind;
    switch(kind){
        case CODE_ASSIGN:
        case CODE_ASSIGN_FROM:
        case CODE_ASSIGN_INTO:
        case CODE_CALL:
            tmp->call.left = left;
            tmp->call.right = right;
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
    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
    tmp->kind = kind;
    switch(kind){
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
    InterCode *tmp = (InterCode*)malloc(sizeof(InterCode));
    tmp->kind = kind;
    tmp->cond_jmp.op1 = opr1;
    tmp->cond_jmp.op2 = opr2;
    tmp->cond_jmp.relop = relop;
    tmp->cond_jmp.label_name = label_name;
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
MakeFunction(program) {
    assert(unit->syn_type == Program);
    initSymbols();

    MakeObj(extDefList, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[0].syn_child);
    return;
}
MakeFunction(extDefList)
{
    assert(unit == NULL || unit->syn_type == ExtDefList);
    if(unit == NULL)
        return;
    

    MakeObj(extDef, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[0].syn_child);
    MakeObj(extDefList, n1, emptyPPT);
    n1.creator(&n1, unit->symbol[1].syn_child);
    return;
}
MakeFunction(extDef)
{
    assert(unit->syn_type == ExtDef);
    MakeObj(specifier, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[0].syn_child);
    if(n0.ppt.error){
        thisppt.error = 1;
        return;
    }

    // suppose there is no error in specifier
    if (unit->symbol_type[1] == LEX)
    {
        // do nothing
    }
    else if (unit->symbol[1].syn_child->syn_type == ExtDecList)
    {
        makePPT(p1);
        p1.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(extDecList, n1, p1); //inherance Specifier Type
        n1.creator(&n1, unit->symbol[1].syn_child);
        //SEMI
    }
    else
    {
        makePPT(p1);
        p1.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(funDec, n1, p1);
        n1.creator(&n1, unit->symbol[1].syn_child);
        //continue to analyse CompSt even there is some error in FunDec

        makePPT(p2);
        p2.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(compSt, n2, p2); //this inherance may not be neccessary
        n2.creator(&n2, unit->symbol[2].syn_child);
    }
}
MakeFunction(extDecList)
{
    //attr: type_inh
    assert(unit->syn_type == ExtDecList);
    makePPT(p0);
    p0.type_inh = copyExpr(thisppt.type_inh);

    MakeObj(varDec, n0, p0); //syn_child varDec get the inherance property
    n0.creator(&n0, unit->symbol[0].syn_child);
    // n0 response to error in VarDec
    if (unit->symbol_num > 1)
    {
        //COMMA
        makePPT(p2);
        p2.type_inh = copyExpr(thisppt.type_inh);

        MakeObj(extDecList, n2, p2);
        n2.creator(&n2, unit->symbol[2].syn_child);
    }
    delExpr(n0.ppt.type_syn);
    delExpr(thisppt.type_inh);
}
MakeFunction(specifier)
{
    //attr: speci 
    assert(unit->syn_type == Specifier);
    if (unit->symbol_type[0] == LEX)
    {
        LexUnit *lexunit = unit->symbol[0].lex_child;
        if(lexunit->iorf == TYPE_INT){
            thisppt.speci = speci_int;
        }else if(lexunit->iorf == TYPE_FLOAT){
            thisppt.speci = speci_float;
        }
    }
    else
    {
        assert(unit->symbol[0].syn_child->syn_type == StructSpecifier);
        makePPT(p0);
        p0.inStruct = thisppt.inStruct;

        MakeObj(structSpecifier, n0, p0);
        n0.creator(&n0, unit->symbol[0].syn_child);

        if(!n0.ppt.error)
            thisppt.speci = n0.ppt.speci;
        else
            thisppt.error = 1;
    }
}
MakeFunction(structSpecifier)
{
    //attr:  speci
    //fix error at Specifier
    //assert(0);
    assert(unit->syn_type == StructSpecifier);
    if (unit->symbol[1].syn_child->syn_type == OptTag)
    {

        MakeObj(optTag, n1, emptyPPT);
        n1.creator(&n1, unit->symbol[1].syn_child);

        SpecifierNode *speci = n1.ppt.speci;
        makePPT(p3);
        p3.inStruct = 1;
        symbols = newTable(symbols); 

        MakeObj(defList, n3, p3);
        n3.creator(&n3, unit->symbol[3].syn_child);

        if(n3.ppt.error){               // if error in deflist
            symbols = pop(symbols);
            //delExpr(n3.ppt.type_syn);
            thisppt.error = 1;
        }else{
            speci->sym_table = symbols;

            //split the struct field from upper stack
            SpecifierNode *node = symbols;
            for (; node->next != NULL && node->next->symbol_type != NODE_FAKE;node = node->next)
                ;
            symbols = node->next;
            node->next = NULL;

            speci->type = wrapStruct(n3.ppt.type_syn);
            bool ret = appendSpeci(symbols, speci);
            if(ret == 0){
                printf("Error Type 16 at Line %d: Redefined struct name \"%s\".\n", unit->lineno, speci->name);
                delNode(speci);
                thisppt.error = 1;
            }
            else
            {
                thisppt.speci = n1.ppt.speci;
            }
            delExpr(n3.ppt.type_syn);
        }
    }
    else
    {
        MakeObj(tag, n1, emptyPPT);
        n1.creator(&n1, unit->symbol[1].syn_child);
        if(n1.ppt.error){
            thisppt.speci = NULL;
            thisppt.error = 1;
        }
        else
        {
            thisppt.speci = n1.ppt.speci;
        }
    }
}
MakeFunction(optTag)
{
    // speci
    //fix error at structSpecifier
    //assert(0);
    assert(unit == NULL || unit->syn_type == OptTag);
    if (unit == NULL)
    {
        thisppt.speci = (SpecifierNode*)malloc(sizeof(SpecifierNode));
        thisppt.speci->name = (char*)malloc(1);
        thisppt.speci->name[0] = 0;
    }
    char *id = unit->symbol[0].lex_child->id;
    thisppt.speci = (SpecifierNode*)malloc(sizeof(SpecifierNode));
    thisppt.speci->name = (char*)malloc(strlen(id) + 1);
    strcpy(thisppt.speci->name, id);
}
MakeFunction(tag)
{
    assert(unit->syn_type == Tag);
    //attr: speci
    //fix error at StructSpecifier
    //assert(0);
    char *id = unit->symbol[0].lex_child->id;
    thisppt.speci = lookup(symbols, id);
    if(thisppt.speci == NULL ||
        thisppt.speci->symbol_type != NODE_SPECI){
        printf("Error Type 17 at Line %d: Undefined struct name \"%s\".\n", unit->lineno, id);
        thisppt.error = 1;
    }
    return;
}
MakeFunction(varDec)
{
    //type_inh, type_syn, inStruct
    //remember delExpr at -ExtDecList ParamDec Dec VarDec-
    //fix error at ExtDecList ParamDec Dec VarDec
    //assert(0);
    assert(unit->syn_type == VarDec);
    if (unit->symbol_type[0] == LEX)
    {
        char *id = unit->symbol[0].lex_child->id;
        bool ret = appendVar(symbols, id, thisppt.type_inh);
        if(ret == 0){
            if(thisppt.inStruct)
                printf("Error Type 15 at Line %d: Redefined field name \"%s\" in a struct.\n", unit->lineno, id);
            else
                printf("Error Type 3 at Line %d: Redefined variable \"%s\".\n", unit->lineno, id);
            thisppt.error = 1;
        }else
            thisppt.type_syn = copyExpr(thisppt.type_inh);
    }
    else
    {
        int num = unit->symbol[2].lex_child->ival;
        makePPT(p0);
        p0.type_inh = wrapArray(thisppt.type_inh, num);
        p0.inStruct = thisppt.inStruct;

        MakeObj(varDec, n0, p0);
        n0.creator(&n0, unit->symbol[0].syn_child);
        if(!n0.ppt.error)
            thisppt.type_syn = copyExpr(n0.ppt.type_syn);
        else
            thisppt.error = 1;
        
        delExpr(n0.ppt.type_syn);
    }
    delExpr(thisppt.type_inh);
}

MakeFunction(funDec)
{
    //attr:  type_inh
    //fix error at ExtDef
   // assert(0);
   assert(unit->syn_type == FunDec);
    char *id = unit->symbol[0].lex_child->id;
    if(exist(symbols, id)){        //check func table
        thisppt.error = 1;
        printf("Error Type 4 at Line %d: Redefined function \"%s\".\n", unit->lineno, id);
    }

    if(unit->symbol_type[2] == SYN){
        SymbolTable cur_table = symbols;
        symbols = newTable(symbols);

        MakeObj(paramList, n2, emptyPPT);
        n2.creator(&n2, unit->symbol[2].syn_child);

        symbols = delNode(symbols); //delete the fake node, to make params part of CompSt
        //no matter if there is an error in paramlist
        if (!n2.ppt.error)
        {
            TypeExpr tmp = wrapFunc(n2.ppt.type_syn, thisppt.type_inh);
            bool ret = appendFunc(cur_table, id, tmp);  // dont append to symbols
            delExpr(tmp);
        }
        else
        {
            thisppt.error = 1;
        }
        delExpr(n2.ppt.type_syn);
    }
    else
    {
        TypeExpr tmp = wrapFunc(NULL, thisppt.type_inh);
        bool ret = appendFunc(symbols, id, tmp);
        delExpr(tmp);
    }

    delExpr(thisppt.type_inh);
    return;
}
MakeFunction(paramList)
{
    //attr: type_syn
    //delExpr at -paramList-, -FunDec-
    //fix error at paramList FunDec
    //assert(0);
    assert(unit->syn_type == ParamList);
    MakeObj(paramDec, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[0].syn_child);

    if(n0.ppt.error){
        thisppt.error = 1;
    }

    if (unit->symbol_num > 1)
    {
        //COMMA

        MakeObj(paramList, n2, emptyPPT);
        n2.creator(&n2, unit->symbol[2].syn_child);

        if(!n2.ppt.error && !n0.ppt.error){           //error happen in ParamDec
            thisppt.type_syn = wrapTuple(n0.ppt.type_syn, n2.ppt.type_syn);
        }
        else
        {
            thisppt.error = 1;
        }
        delExpr(n2.ppt.type_syn);
    }else if(!n0.ppt.error){
        thisppt.type_syn = wrapTuple(n0.ppt.type_syn, NULL);
    }
    delExpr(n0.ppt.type_syn);
    return;
}
MakeFunction(paramDec)
{
    //attr: type_syn
    //delExpr at -paramList-
    //assert(0);
    assert(unit->syn_type == ParamDec);
    MakeObj(specifier, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[0].syn_child);

    if(!n0.ppt.error){
        makePPT(p1);
        p1.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(varDec, n1, p1); //inherant Specifier
        n1.creator(&n1, unit->symbol[1].syn_child);

        if(!n1.ppt.error){
            thisppt.type_syn = copyExpr(n1.ppt.type_syn);
        }
        else
        {
            thisppt.error = 1;
        }
        delExpr(n1.ppt.type_syn);
    }
    else
    {
        thisppt.error = 1;
        // do not return the type
    }

    return;
}
MakeFunction(compSt)
{
    //attr: type_inh
    assert(unit->syn_type == CompSt);
    symbols = newTable(symbols);

    MakeObj(defList, n1, emptyPPT);
    n1.creator(&n1, unit->symbol[1].syn_child);
    // no response to delList error

    makePPT(p2);
    p2.type_inh = copyExpr(thisppt.type_inh);

    MakeObj(stmtList, n2, p2);
    n2.creator(&n2, unit->symbol[2].syn_child);

    symbols = pop(symbols); //maybe including params
    delExpr(thisppt.type_inh);
    return;
}
MakeFunction(stmtList)
{
    //attr: type_inh
    assert(unit == NULL || unit->syn_type == StmtList);
    if (unit == NULL)
    {
        //do nothing
    }
    else
    {
        makePPT(p0);
        p0.type_inh = copyExpr(thisppt.type_inh);

        MakeObj(stmt, n0, p0);
        n0.creator(&n0, unit->symbol[0].syn_child);
        //no response to stmt error

        makePPT(p1);
        p1.type_inh = copyExpr(thisppt.type_inh);

        MakeObj(stmtList, n1, p1);
        n1.creator(&n1, unit->symbol[1].syn_child);
    }
    delExpr(thisppt.type_inh);
}
MakeFunction(stmt)
{
    //attr: type_inh'
    assert(unit->syn_type == Stmt);
    if (unit->symbol_type[0] == LEX)
    {
        if (unit->symbol[0].lex_child->lex_type == RETURN)
        {
            // RETURN 
            MakeObj(exp, n1, emptyPPT);
            n1.creator(&n1, unit->symbol[1].syn_child);
            if(!n1.ppt.error && !type_equiv(n1.ppt.type_syn, thisppt.type_inh)){
                printf("Error Type 8 at Line %d: Wrong return type.\n", unit->lineno);
                thisppt.error = 1;
            }
            delExpr(n1.ppt.type_syn);
        }
        else //IF AND WHILE
        {
            MakeObj(exp, n2, emptyPPT);
            n2.creator(&n2, unit->symbol[2].syn_child);

            makePPT(p4);
            p4.type_inh = copyExpr(thisppt.type_inh);

            MakeObj(stmt, n4, p4);
            n4.creator(&n4, unit->symbol[4].syn_child);
            // no response to stmt error

            if (unit->symbol_num > 5) // IF ELSE
            {
                makePPT(p6);
                p6.type_inh = copyExpr(thisppt.type_inh);
                MakeObj(stmt, n6, p6);
                n6.creator(&n6, unit->symbol[6].syn_child);
                delExpr(n6.ppt.type_syn);
            }
            delExpr(n2.ppt.type_syn);
        }
    }
    else
    {
        
        if (unit->symbol[0].syn_child->syn_type == Exp)
        {
            // Exp SEMI
            MakeObj(exp, n0, emptyPPT);
            n0.creator(&n0, unit->symbol[0].syn_child);
            delExpr(n0.ppt.type_syn);
        }
        else
        {
            //CompSt
            makePPT(p0);
            p0.type_inh = copyExpr(thisppt.type_inh);

            MakeObj(compSt, n0, p0);
            n0.creator(&n0,unit->symbol[0].syn_child);
        }
    }
    delExpr(thisppt.type_inh);
}
MakeFunction(defList)
{
    assert(unit == NULL || unit->syn_type == DefList);
    //attr: inStruct
    //delete expr at struct deflist compstmt
    //fix error at struct deflist compstmt
    //assert(0);
    if (unit == NULL)
    {
        thisppt.type_syn = NULL;
    }
    else
    {
        makePPT(p0);
        p0.inStruct = thisppt.inStruct;

        MakeObj(def, n0, p0);
        n0.creator(&n0,unit->symbol[0].syn_child);

        
        makePPT(p1);
        p1.inStruct = thisppt.inStruct;

        MakeObj(defList, n1, p1); //inherance def
        n1.creator(&n1,unit->symbol[1].syn_child);

        if(!n0.ppt.error && !n1.ppt.error){
            if(thisppt.inStruct)
                thisppt.type_syn = catTuple(n0.ppt.type_syn, n1.ppt.type_syn);
            
                
        }else{
            thisppt.error = 1;
        }
        delExpr(n0.ppt.type_syn);
        delExpr(n1.ppt.type_syn);
    }
}
MakeFunction(def)
{
    assert(unit->syn_type == Def);
    //attr: type_syn, inStruct
    //delExpr at -defList-
    //fix error at -deflist-
    //assert(0);
    MakeObj(specifier, n0, emptyPPT);
    n0.creator(&n0,unit->symbol[0].syn_child);
    if(!n0.ppt.error){
        makePPT(p1);
        p1.inStruct = thisppt.inStruct;
        p1.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(decList, n1, p1);
        n1.creator(&n1,unit->symbol[1].syn_child);

        if(!n1.ppt.error){
            if(thisppt.inStruct)
                thisppt.type_syn = copyExpr(n1.ppt.type_syn);
        }else{
            thisppt.error = 1;
        }
        delExpr(n1.ppt.type_syn);
    }
    else
    {
        thisppt.error = 1;
    }

     return;
}
MakeFunction(decList)
{
    assert(unit->syn_type == DecList);
    // attr: type_inh, type_syn, inStruct
    // delExpr at -Def-
    //fix error -declist-, -def-
    //assert(0);
    makePPT(p0);
    p0.inStruct = thisppt.inStruct;
    p0.type_inh = copyExpr(thisppt.type_inh);

    MakeObj(dec, n0, p0);
    n0.creator(&n0,unit->symbol[0].syn_child);

    if(unit->symbol_num>1)
    {
        makePPT(p2);
        p2.inStruct = thisppt.inStruct;
        p2.type_inh = copyExpr(thisppt.type_inh);

        MakeObj(decList, n2, p2);
        n2.creator(&n2,unit->symbol[2].syn_child);

        if(!n2.ppt.error && !n0.ppt.error){
            if(thisppt.inStruct)
                thisppt.type_syn = wrapTuple(n0.ppt.type_syn, n2.ppt.type_syn);
        }else{
            thisppt.error = 1;
        }
        delExpr(n2.ppt.type_syn);
    }
    else
    {
        if(!n0.ppt.error){
            if(thisppt.inStruct)
                thisppt.type_syn = wrapTuple(n0.ppt.type_syn, NULL);
        }else{
            thisppt.error = 1;
        }
    }
    delExpr(n0.ppt.type_syn);
    delExpr(thisppt.type_inh);
    return;
}
MakeFunction(dec)
{
    assert(unit->syn_type == Dec);
    //attr: type_inh, type_syn, inStruct
    //delExpr at -declist-
    //fix error at -declist-
    //assert(0);
    makePPT(p0);
    p0.type_inh = copyExpr(thisppt.type_inh);
    p0.inStruct = thisppt.inStruct;

    MakeObj(varDec, n0, p0);
    n0.creator(&n0,unit->symbol[0].syn_child);

    if(unit->symbol_num>1)
    {
        if(thisppt.inStruct){
            printf("Error Type 15 at Line %d: Cannot initialize in struct.\n", unit->lineno);
            thisppt.error = 1;
        }else{
            MakeObj(exp,n2,emptyPPT);
            n2.creator(&n2, unit->symbol[2].syn_child);

            if (!n0.ppt.error && !n2.ppt.error && !type_equiv(n2.ppt.type_syn, n0.ppt.type_syn))
                printf("Error Type 5 at Line %d: Types do not match around \"=\".\n", unit->lineno);
            delExpr(n2.ppt.type_syn);
        }
    }else if(!n0.ppt.error ){
        if(thisppt.inStruct)
            thisppt.type_syn = copyExpr(n0.ppt.type_syn);
    }else
        thisppt.error = 1;

    delExpr(n0.ppt.type_syn);
    delExpr(thisppt.type_inh);
    return;
}
/*MakeFunction(exp_bk)
{
    assert(unit->syn_type == Exp);
    //attr: type_inh, isLvalue;
    // delExpr at -stmt-, -exp-, -args-
    //checkout error at -stmt- -exp-
    if (unit->symbol_type[0] == LEX)
    {
        if(unit->symbol[0].lex_child->lex_type == INT)
        {
            // INT
            thisppt.type_syn = wrapSpeci(speci_int);
            thisppt.isLvalue = false;

            thisppt.place = getConst(unit->symbol[0].lex_child->ival);
        } else if (unit->symbol[0].lex_child->lex_type == FLOAT) {
            // FLAOT is out of discussion
            thisppt.type_syn = wrapSpeci(speci_float);
            thisppt.isLvalue = false;
        } else if (unit->symbol[0].lex_child->lex_type == ID) {
            char *id = unit->symbol[0].lex_child->id;
            if(unit->symbol_num == 1)
            {
                // ID
                VarNode *var = lookup(symbols, id);
                if(var == NULL || var->symbol_type != NODE_VAR){
                    printf("Error Type 1 at Line %d: Undefined variable \"%s\".\n", unit->lineno, id);
                    thisppt.error = 1;
                }else{
                    thisppt.type_syn = copyExpr(var->type);
                    thisppt.isLvalue = 1;

                    thisppt.place = var->inter_name;
                    if(isArray(var->type) || isStruct(var->type)){
                        thisppt.isAddr = true;
                    } else {
                        thisppt.isAddr = false;
                    }
                }
            }
            else
            {
                //ID() or ID(Args)
                VarNode *func = lookup(symbols, id);
                TypeExpr param = NULL;
                TypeExpr ret = NULL;
                
                if(func == NULL){
                    printf("Error Type 2 at Line %d: Undefined function \"%s\".\n", unit->lineno, id);
                    thisppt.error = 1;
                } else if(func->symbol_type != NODE_FUNC){
                    printf("Error Type 11 at Line %d: \"%s\" is not a function.\n", unit->lineno, id);
                    thisppt.error = 1;
                }else{
                    param = func->type->func.param;
                    ret = func->type->func.ret;
                    if (unit->symbol_num == 3)
                    {
                        // with no Args
                        if(param != NULL){
                            printf("Error Type 9 at Line %d: Arguments do not match the parameters of function \"%s\".\n", unit->lineno, id);
                            thisppt.error = 1;
                        }else{
                            thisppt.type_syn = copyExpr(ret);
                            thisppt.isLvalue = false;

                            Operand t = getTmpVarName();
                            genCode2(CODE_CALL, t1, func->inter_name);
                            thisppt.place = t;
                        }
                    }
                }
                if(unit->symbol_num == 4)
                {
                    // with args
                    MakeObj(args, n2, emptyPPT);
                    n2.creator(&n2, unit->symbol[2].syn_child); //it will match paramList

                    if(!thisppt.error && !n2.ppt.error ){
                        if(type_equiv(n2.ppt.type_syn, param)){
                            thisppt.type_syn = copyExpr(ret);
                            thisppt.isLvalue = false;  

                            // after parsing the args
                            Operand t = getTmpVarName();
                            genCode2(CODE_CALL, t1, func->inter_name);
                            thisppt.place = t;
                        }else{
                            printf("Error Type 9 at Line %d: Arguments do not match the parameters of function \"%s\".\n", unit->lineno, id);
                            thisppt.error = 1;
                        }
                        
                    }else 
                        thisppt.error = 1;

                    delExpr(n2.ppt.type_syn);
                }
            }
        } else if (unit->symbol[0].lex_child->lex_type == NOT ||
                   unit->symbol[0].lex_child->lex_type == MINUS) {
            //NOT Expr
            //minus Expr
            MakeObj(exp, n1, emptyPPT);
            n1.creator(&n1, unit->symbol[1].syn_child);
            if(!n1.ppt.error){
                if(!isInt(n1.ppt.type_syn) && !isFloat(n1.ppt.type_syn)){
                    printf("Error Type 7 at Line %d: Operands's type should be int or float.\n", unit->lineno);
                    thisppt.error = 1;
                }else{
                    thisppt.type_syn = copyExpr(n1.ppt.type_syn);
                    thisppt.isLvalue = 0;
                }
            }else{
                thisppt.error = 1;
            }
            delExpr(n1.ppt.type_syn);
        } else if (unit->symbol[0].lex_child->lex_type == LP) {
            // LP Exp RP
            MakeObj(exp, n1, emptyPPT);
            n1.creator(&n1, unit->symbol[1].syn_child);
            if (!n1.ppt.error)
            {
                thisppt.type_syn = copyExpr(n1.ppt.type_syn);
                thisppt.isLvalue = n1.ppt.isLvalue;
            }
            else
            {
                thisppt.error = 1;
            }
            delExpr(n1.ppt.type_syn);
        }
    } 
    // start with Exp
    else if(unit->symbol[1].lex_child->lex_type == LB)//array
    {   
        //Exp LB INT RB
        MakeObj(exp,n0,emptyPPT);
        n0.creator(&n0,unit->symbol[0].syn_child);

        MakeObj(exp,n2,emptyPPT);
        n2.creator(&n2,unit->symbol[2].syn_child);

        if(!n0.ppt.error && !n2.ppt.error){
            if (!isArray(n0.ppt.type_syn)){
                thisppt.error = 1;
                printf("Error Type 10 at Line %d: Expression before \'[\', \']\' is not an array type.\n", unit->lineno);
            }else if (!isInt(n2.ppt.type_syn))
            {
                thisppt.error = 1;
                printf("Error Type 12 at Line %d: Expression in \'[\', \']\' is not an int type.\n", unit->lineno);
            }else{
                thisppt.type_syn = copyExpr(n0.ppt.type_syn->array.expr); //retrive the element
                thisppt.isLvalue = 1;
            }    
        }else{
            thisppt.error = 1;
        }
        delExpr(n0.ppt.type_syn);
        delExpr(n2.ppt.type_syn);
        return;
    }
    else if(unit->symbol[1].lex_child->lex_type == DOT)
    {
        // Exp DOT ID
        MakeObj(exp,n0,emptyPPT);
        n0.creator(&n0,unit->symbol[0].syn_child);
    
        if(!n0.ppt.error){
            
            if(!isStruct(n0.ppt.type_syn)){
                thisppt.error = 1;
                printf("Error Type 13 at Line %d: Expression before \'.\' is not a struct type.\n", unit->lineno);
            }else{
                char *id = unit->symbol[2].lex_child->id;
                SpecifierNode *speci = n0.ppt.type_syn->speci;
                VarNode *var = lookup(speci->sym_table, id);
                if(var == NULL || var->symbol_type != NODE_VAR){
                    thisppt.error = 1;
                    printf("Error Type 14 at Line %d: Undefined field name after \'.\'.\n", unit->lineno);
                }else{
                    thisppt.type_syn = copyExpr(var->type);
                    thisppt.isLvalue = 1;
                }
            }
        
        }else{
            thisppt.error = 1;
        }
        delExpr(n0.ppt.type_syn);
    }
    else  if(unit->symbol[1].lex_child->lex_type == ASSIGNOP){
        //printf("hit\n");
        // Exp ASSIGNOP Exp
        MakeObj(exp, n0, emptyPPT);
        n0.creator(&n0, unit->symbol[0].syn_child);

        MakeObj(exp, n2, emptyPPT);
        n2.creator(&n2, unit->symbol[2].syn_child);

        if (!n0.ppt.error && !n2.ppt.error)
        {
            if(n0.ppt.isLvalue == false){
                printf("Error Type 6 at Line %d: Expression is not lvalue on the left side of \'=\'.\n", unit->lineno);
                thisppt.error = 1;
            }else{
                thisppt.isLvalue = 1;
            }

            if(!type_equiv(n0.ppt.type_syn, n2.ppt.type_syn)){
                printf("Error Type 5 at Line %d: Type do not match on the two side of \'=\'.\n", unit->lineno);
                thisppt.error = 1;
            }else{
                thisppt.type_syn = copyExpr(n0.ppt.type_syn);
                
            }
            //printf("\n");
        }
        else
        {
            thisppt.error = 1;
        }
        delExpr(n0.ppt.type_syn);
        delExpr(n2.ppt.type_syn);

    }
    else{
        // + - * / relop and or
        MakeObj(exp, n0, emptyPPT);
        n0.creator(&n0, unit->symbol[0].syn_child);

        MakeObj(exp, n2, emptyPPT);
        n2.creator(&n2, unit->symbol[2].syn_child);

        if (!n0.ppt.error && !n2.ppt.error)
        {
            if((!isInt(n0.ppt.type_syn) && !isFloat(n0.ppt.type_syn))
                || (!isInt(n2.ppt.type_syn) && !isFloat(n2.ppt.type_syn))){
                printf("Error Type 7 at Line %d: Operands's type should be int or float.\n", unit->lineno);
                thisppt.error = 1;
            }else if(!type_equiv(n0.ppt.type_syn, n2.ppt.type_syn)){
                printf("Error Type 7 at Line %d: Types do not match on the two side of operator.\n", unit->lineno);
                thisppt.error = 1;
            }else{
                thisppt.type_syn = copyExpr(n0.ppt.type_syn);
                thisppt.isLvalue = 0;
            }
            //printf("\n");
        }
        else
        {
            thisppt.error = 1;
        }
        delExpr(n0.ppt.type_syn);
        delExpr(n2.ppt.type_syn);
    }
}*/
MakeFunction(exp) { 
    // isadress judge
    assert(0);
    assert(unit->syn_type == Exp);
    if(unit->symbol_num == 1 && 
       unit->symbol_type[0] == LEX && 
       unit->symbol[0].lex_child->lex_type == INT){
        //INT
        thisppt.type_syn = wrapSpeci(speci_int);
        thisppt.isLvalue = false;
        // genCode
        thisppt.place = getConst(unit->symbol[0].lex_child->ival);
    }else if(unit->symbol_num == 1 && 
        unit->symbol[0].lex_child->lex_type == INT && 
        unit->symbol[0].lex_child->lex_type == FLOAT){
        //FLOAT
        thisppt.type_syn = wrapSpeci(speci_float);
        thisppt.isLvalue = false;
    }else if(unit->symbol_num == 1 && 
        unit->symbol_type[0] == LEX && 
        unit->symbol[0].lex_child->lex_type == ID){
        // ID
        char *id = unit->symbol[0].lex_child->id;
        VarNode *var = lookup(symbols, id);
        if(var == NULL || var->symbol_type != NODE_VAR){
            printf("Error Type 1 at Line %d: Undefined variable \"%s\".\n", unit->lineno, id);
            thisppt.error = 1;
        }else{
            thisppt.type_syn = copyExpr(var->type);
            thisppt.isLvalue = 1;
            // genCode
            thisppt.place = var->inter_name;
            thisppt.isRef = false;
            
        }
    }else if(unit->symbol_num == 3 && 
             unit->symbol_type[0] == LEX && 
             unit->symbol[0].lex_child->lex_type == ID){
        // ID LP RP
        char *id = unit->symbol[0].lex_child->id;
        VarNode *func = lookup(symbols, id);
        TypeExpr param;
        TypeExpr ret;
        if (func == NULL) {
            printf("Error Type 2 at Line %d: Undefined function \"%s\".\n", unit->lineno, id);
            thisppt.error = 1;
        } else if (func->symbol_type != NODE_FUNC) {
            printf("Error Type 11 at Line %d: \"%s\" is not a function.\n", unit->lineno, id);
            thisppt.error = 1;
        } else {
            param = func->type->func.param;
            ret = func->type->func.ret;
            if(param != NULL){
                printf("Error Type 9 at Line %d: Arguments do not match the parameters of function \"%s\".\n", unit->lineno, id);
                thisppt.error = 1;
            }else{
                thisppt.type_syn = copyExpr(ret);
                thisppt.isLvalue = false;
                // genCode
                Operand t = getTmpVarName();
                if(func == func_read){
                    genCode1(CODE_READ, t);
                }else{
                    genCode2(CODE_CALL, t, func->inter_name);
                }
                thisppt.place = t;
            }
        }
    }else if(unit->symbol_num == 4 && 
             unit->symbol_type[0] == LEX && 
             unit->symbol[0].lex_child->lex_type == ID){
        // ID LP Args RP
        char *id = unit->symbol[0].lex_child->id;
        VarNode *func = lookup(symbols, id);
        TypeExpr param;
        TypeExpr ret;
        if(func == NULL){
            printf("Error Type 2 at Line %d: Undefined function \"%s\".\n", unit->lineno, id);
            thisppt.error = 1;
        } else if(func->symbol_type != NODE_FUNC){
            printf("Error Type 11 at Line %d: \"%s\" is not a function.\n", unit->lineno, id);
            thisppt.error = 1;
        }else{
            param = func->type->func.param;
            ret = func->type->func.ret;
        }
        MakeObj(args, n2, emptyPPT);
        n2.creator(&n2, unit->symbol[2].syn_child); //it will match paramList

        if(!thisppt.error && !n2.ppt.error ){
            if(type_equiv(n2.ppt.type_syn, param)){
                thisppt.type_syn = copyExpr(ret);
                thisppt.isLvalue = false;  
                // genCode
                // after parsing the args
                Operand t = getTmpVarName();
                if(func == func_write){
                    Operand zero = getConst(0);
                    assert(tail->kind == CODE_ARG);
                    Operand arg = tail->arg.op;
                    tail = tail->prev;
                    free(tail->next);
                    tail->next = NULL;
                    genCode1(CODE_WRITE, arg);
                    genCode2(CODE_ASSIGN, t, zero);
                } else {
                    genCode2(CODE_CALL, t, func->inter_name);
                }
                thisppt.place = t;
            }else{
                printf("Error Type 9 at Line %d: Arguments do not match the parameters of function \"%s\".\n", unit->lineno, id);
                thisppt.error = 1;
            }
            
        }else 
            thisppt.error = 1;

        delExpr(n2.ppt.type_syn);
    }else if(unit->symbol_num == 2 && 
             unit->symbol_type[0] == LEX && 
             unit->symbol[0].lex_child->lex_type == MINUS){
        // MINUS Exp
        MakeObj(exp, n1, emptyPPT);
        n1.creator(&n1, unit->symbol[1].syn_child);
        if(!n1.ppt.error){
            if(!isInt(n1.ppt.type_syn) && !isFloat(n1.ppt.type_syn)){
                printf("Error Type 7 at Line %d: Operands's type should be int or float.\n", unit->lineno);
                thisppt.error = 1;
            }else{
                thisppt.type_syn = copyExpr(n1.ppt.type_syn);
                thisppt.isLvalue = 0;
                // genCode
                Operand t = getTmpVarName();
                Operand zero = getConst(0);
                genCode3(CODE_SUB, t, zero, n1.ppt.place);
                thisppt.place = t;
            }
        }else{
            thisppt.error = 1;
        }
        delExpr(n1.ppt.type_syn);
    }else if(unit->symbol_num == 2 && 
             unit->symbol_type[0] == LEX && 
             unit->symbol[0].lex_child->lex_type == NOT){
        // NOT Exp
        //genCode
        Operand zero = getConst(0);
        Operand t = getTmpVarName();
        genCode2(CODE_ASSIGN, t, zero);

        makePPT(p);
        p.label_true = getLabel();
        p.label_false = getLabel();
        MakeObj(cond, n, p);
        n.creator(&n, unit);

        if(!n.ppt.error){
            thisppt.type_syn = wrapSpeci(speci_int);
            thisppt.isLvalue = 0;
            //genCode
            Operand one = getConst(1);
            genCode1(CODE_LABEL, p.label_true);
            genCode2(CODE_ASSIGN, t, one);
            genCode1(CODE_LABEL, p.label_false);
            thisppt.place = t;
        }else{
            thisppt.error = 1;
        }
        delExpr(n.ppt.type_syn);
    }else if(unit->symbol_num == 3 && 
             unit->symbol_type[0] == LEX && 
             unit->symbol[0].lex_child->lex_type == LP){
        // LP Exp RP
        MakeObj(exp, n1, emptyPPT);
        n1.creator(&n1, unit->symbol[1].syn_child);
        if (!n1.ppt.error)
        {
            thisppt.type_syn = copyExpr(n1.ppt.type_syn);
            thisppt.isLvalue = n1.ppt.isLvalue;
            //genCode
            thisppt.place = n1.ppt.place;
            thisppt.isRef = n1.ppt.isRef;
        } else {
            thisppt.error = 1;
        }
        delExpr(n1.ppt.type_syn);
    }else if(unit->symbol_num == 4 && 
             unit->symbol_type[1] == LEX && 
             unit->symbol[1].lex_child->lex_type == LB){
        //Exp LB INT RB
        MakeObj(exp,n0,emptyPPT);
        n0.creator(&n0,unit->symbol[0].syn_child);

        MakeObj(exp,n2,emptyPPT);
        n2.creator(&n2,unit->symbol[2].syn_child);

        if(!n0.ppt.error && !n2.ppt.error){
            if (!isArray(n0.ppt.type_syn)){
                thisppt.error = 1;
                printf("Error Type 10 at Line %d: Expression before \'[\', \']\' is not an array type.\n", unit->lineno);
            }else if (!isInt(n2.ppt.type_syn))
            {
                thisppt.error = 1;
                printf("Error Type 12 at Line %d: Expression in \'[\', \']\' is not an int type.\n", unit->lineno);
            }else{
                thisppt.type_syn = copyExpr(n0.ppt.type_syn->array.expr); //retrive the element
                thisppt.isLvalue = 1;
                //genCode
                Operand offset = getTmpVarName();
                Operand t = getTmpVarName();
                Operand num;
                if(n2.ppt.isRef){
                    num = getTmpVarName();
                    genCode2(CODE_ASSIGN_FROM, num, n2.ppt.place);
                }else{
                    num = n2.ppt.place;
                }
                Operand width = getConst(n0.ppt.type_syn->array.element_width);
                genCode3(CODE_MUL, offset, num, width);
                genCode3(CODE_PLUS, t, n0.ppt.place, offset);
                thisppt.place = t;
                if(isInt(thisppt.type_syn) || isFloat(thisppt.type_syn)){
                    thisppt.isRef = true;
                } else
                    thisppt.isRef = false;
            }
        }else{
            thisppt.error = 1;
        }
        delExpr(n0.ppt.type_syn);
        delExpr(n2.ppt.type_syn);
        return;
    }else if(unit->symbol_num == 3 && 
             unit->symbol_type[1] == LEX && 
             unit->symbol[1].lex_child->lex_type == DOT){
         // Exp DOT ID
        MakeObj(exp,n0,emptyPPT);
        n0.creator(&n0,unit->symbol[0].syn_child);
    
        if(!n0.ppt.error){
            
            if(!isStruct(n0.ppt.type_syn)){
                thisppt.error = 1;
                printf("Error Type 13 at Line %d: Expression before \'.\' is not a struct type.\n", unit->lineno);
            }else{
                char *id = unit->symbol[2].lex_child->id;
                SpecifierNode *speci = n0.ppt.type_syn->speci;
                VarNode *var = lookup(speci->sym_table, id);
                if(var == NULL || var->symbol_type != NODE_VAR){
                    thisppt.error = 1;
                    printf("Error Type 14 at Line %d: Undefined field name after \'.\'.\n", unit->lineno);
                }else{
                    thisppt.type_syn = copyExpr(var->type);
                    thisppt.isLvalue = 1;
                    //genCode
                    Operand offset = getConst(var->offset);
                    Operand t = getTmpVarName();
                    genCode3(CODE_PLUS, t, n0.ppt.place, offset);
                    thisppt.place = t;
                    if(isInt(thisppt.type_syn) || isFloat(thisppt.type_syn)){
                        thisppt.isRef = true;
                    } else
                        thisppt.isRef = false;
                    }
            }
        
        }else{
            thisppt.error = 1;
        }
        delExpr(n0.ppt.type_syn);
    }else if(unit->symbol_num == 3 && 
             unit->symbol_type[1] == LEX &&
             unit->symbol_type[0] == SYN && unit->symbol[0].syn_child->syn_type == Exp &&
             unit->symbol_type[2] == SYN && unit->symbol[2].syn_child->syn_type == Exp){
        // Exp ... Exp
            
        if(unit->symbol_type[1] == ASSIGNOP){
            // Exp ASSIGNOP Exp
            MakeObj(exp, n0, emptyPPT);
            n0.creator(&n0, unit->symbol[0].syn_child);

            MakeObj(exp, n2, emptyPPT);
            n2.creator(&n2, unit->symbol[2].syn_child);
            if (!n0.ppt.error && !n2.ppt.error) {
                if(n0.ppt.isLvalue == false){
                    printf("Error Type 6 at Line %d: Expression is not lvalue on the left side of \'=\'.\n", unit->lineno);
                    thisppt.error = 1;
                }else{
                    thisppt.isLvalue = 1;
                }

                if(!type_equiv(n0.ppt.type_syn, n2.ppt.type_syn)){
                    printf("Error Type 5 at Line %d: Type do not match on the two side of \'=\'.\n", unit->lineno);
                    thisppt.error = 1;
                }else{
                    thisppt.type_syn = copyExpr(n0.ppt.type_syn);
                    //genCode
                    Operand right;
                    if (n2.ppt.isRef) {
                        right = getTmpVarName();
                        genCode2(CODE_ASSIGN_FROM, right, n2.ppt.place);
                    } else {
                        right = n2.ppt.place;
                    }
                    if(n0.ppt.isRef){
                        genCode2(CODE_ASSIGN_INTO, n0.ppt.place, right);
                    }else{
                        genCode2(CODE_ASSIGN, n0.ppt.place, right);
                    }
                    thisppt.place = n0.ppt.place;
                    thisppt.isRef = n0.ppt.isRef;
                }
            }else
                thisppt.error = 1;

            delExpr(n0.ppt.type_syn);
            delExpr(n2.ppt.type_syn);
            
        }
        else if(unit->symbol_type[1] == PLUS || 
                unit->symbol_type[1] == MINUS ||
                unit->symbol_type[1] == STAR ||
                unit->symbol_type[1] == DIV){

            MakeObj(exp, n0, emptyPPT);
            n0.creator(&n0, unit->symbol[0].syn_child);

            MakeObj(exp, n2, emptyPPT);
            n2.creator(&n2, unit->symbol[2].syn_child);
            if (!n0.ppt.error && !n2.ppt.error) {
                if((!isInt(n0.ppt.type_syn) && !isFloat(n0.ppt.type_syn))
                    || (!isInt(n2.ppt.type_syn) && !isFloat(n2.ppt.type_syn))){
                    printf("Error Type 7 at Line %d: Operands's type should be int or float.\n", unit->lineno);
                    thisppt.error = 1;
                }else if(!type_equiv(n0.ppt.type_syn, n2.ppt.type_syn)){
                    printf("Error Type 7 at Line %d: Types do not match on the two side of operator.\n", unit->lineno);
                    thisppt.error = 1;
                }else{
                    thisppt.type_syn = copyExpr(n0.ppt.type_syn);
                    thisppt.isLvalue = 0;
                    //genCode
                    Operand t = getTmpVarName();
                    Operand op1, op2;
                    if(n0.ppt.isRef){
                        op1 = getTmpVarName();
                        genCode2(CODE_ASSIGN_FROM, op1, n0.ppt.place);
                    }else{
                        op1 = n0.ppt.place;
                    }
                    if(n2.ppt.isRef){
                        op2 = getTmpVarName();
                        genCode2(CODE_ASSIGN_FROM, op2, n2.ppt.place);
                    }else{
                        op2 = n2.ppt.place;
                    }
                    switch (unit->symbol[1].lex_child->lex_type) {
                        case PLUS:
                            genCode3(CODE_PLUS, t, op1, op2);
                            break;
                        case MINUS:
                            genCode3(CODE_SUB, t, op1, op2);
                            break;
                        case STAR:
                            genCode3(CODE_MUL, t, op1, op2);
                            break;
                        case DIV:
                            genCode3(CODE_DIV, t, op1, op2);
                            break;
                    }
                    thisppt.place = t;
                }
            }else
                thisppt.error = 1;
            delExpr(n0.ppt.type_syn);
            delExpr(n2.ppt.type_syn);
        }else if(unit->symbol_type[1] == RELOP || 
                unit->symbol_type[1] == AND ||
                unit->symbol_type[1] == OR){
            Operand zero = getConst(0);
            Operand t = getTmpVarName();
            genCode2(CODE_ASSIGN, t, zero);

            makePPT(p);
            p.label_true = getLabel();
            p.label_false = getLabel();
            MakeObj(cond, n, p);
            n.creator(&n, unit);

            if(!n.ppt.error){
                thisppt.type_syn = wrapSpeci(speci_int);
                thisppt.isLvalue = 0;
                //genCode
                Operand one = getConst(1);
                genCode1(CODE_LABEL, p.label_true);
                genCode2(CODE_ASSIGN, t, one);
                genCode1(CODE_LABEL, p.label_false);
                thisppt.place = t;
            }else{
                thisppt.error = 1;
            }
           //delExpr(n.ppt.type_syn);
        }
    }
    else assert(0); // should be completed

}
MakeFunction(cond){
    //label_true, label_false
    assert(unit->syn_type == Exp);
    if (unit->symbol_num == 2 && unit->symbol_type[0] == LEX &&
        unit->symbol[0].lex_child->lex_type == NOT) {
        makePPT(p1);
        p1.label_true = thisppt.label_false;
        p1.label_false = thisppt.label_true;
        MakeObj(cond, n1, p1);
        n1.creator(&n1, unit->symbol[1].syn_child);
        if (n1.ppt.error = 1){
            thisppt.error = 1;
        }
    } else if (unit->symbol_num == 3 && unit->symbol_type[1] == LEX &&
               unit->symbol[1].lex_child->lex_type == RELOP) {
        MakeObj(exp, n0, emptyPPT);
        n0.creator(&n0, unit->symbol[0].syn_child);

        MakeObj(exp, n2, emptyPPT);
        n2.creator(&n2, unit->symbol[2].syn_child);
        if (!n0.ppt.error && !n2.ppt.error) {
            if((!isInt(n0.ppt.type_syn) && !isFloat(n0.ppt.type_syn))
                || (!isInt(n2.ppt.type_syn) && !isFloat(n2.ppt.type_syn))){
                printf("Error Type 7 at Line %d: Operands's type should be int or float.\n", unit->lineno);
                thisppt.error = 1;
            }else if(!type_equiv(n0.ppt.type_syn, n2.ppt.type_syn)){
                printf("Error Type 7 at Line %d: Types do not match on the two side of operator.\n", unit->lineno);
                thisppt.error = 1;
            }else{
                thisppt.type_syn = copyExpr(n0.ppt.type_syn);
                thisppt.isLvalue = 0;
                //genCode
                Operand t = getTmpVarName();
                Operand op1, op2;
                if(n0.ppt.isRef){
                    op1 = getTmpVarName();
                    genCode2(CODE_ASSIGN_FROM, op1, n0.ppt.place);
                }else{
                    op1 = n0.ppt.place;
                }
                if(n2.ppt.isRef){
                    op2 = getTmpVarName();
                    genCode2(CODE_ASSIGN_FROM, op2, n2.ppt.place);
                }else{
                    op2 = n2.ppt.place;
                }
                genCode4(CODE_COND_JMP, op1, op2,
                         unit->symbol[1].lex_child->relop, thisppt.label_true);
                thisppt.label_true->ref_num++;
                genCode1(CODE_JMP, thisppt.label_false);
                thisppt.label_false->ref_num++;
            }
        }else
            thisppt.error = 1;
        delExpr(n0.ppt.type_syn);
        delExpr(n2.ppt.type_syn);

    } else if (unit->symbol_num == 3 && unit->symbol_type[1] == LEX &&
               unit->symbol[1].lex_child->lex_type == AND) {
        makePPT(p0);
        p0.label_true = getLabel();
        p0.label_false = thisppt.label_false;
        MakeObj(cond, n0, p0);
        n0.creator(&n0, unit->symbol[0].syn_child);

        genCode1(CODE_LABEL, p0.label_true);

        makePPT(p2);
        p2.label_true = thisppt.label_true;
        p2.label_false = thisppt.label_false;
        MakeObj(cond, n2, p2);
        n2.creator(&n2, unit->symbol[2].syn_child);
        if (n0.ppt.error || n2.ppt.error) {
            thisppt.error = 1;
        }
    } else if (unit->symbol_num == 3 && unit->symbol_type[1] == LEX &&
               unit->symbol[1].lex_child->lex_type == OR) {
        makePPT(p0);
        p0.label_true = thisppt.label_true;
        p0.label_false = getLabel();
        MakeObj(cond, n0, p0);
        n0.creator(&n0, unit->symbol[0].syn_child);

        genCode1(CODE_LABEL, p0.label_false);

        makePPT(p2);
        p2.label_true = thisppt.label_true;
        p2.label_false = thisppt.label_false;
        MakeObj(cond, n2, p2);
        n2.creator(&n2, unit->symbol[2].syn_child);
        if (n0.ppt.error || n2.ppt.error) {
            thisppt.error = 1;
        }
    } else {
        MakeObj(exp, n, emptyPPT);
        n.creator(&n, unit);
        if(!n.ppt.error){
            Operand zero = getConst(0);
            Operand op;
            if (n.ppt.isRef) {
                op = getTmpVarName();
                genCode2(CODE_ASSIGN_FROM, op, n.ppt.place);
            }else{
                op = n.ppt.place;
            }
            genCode4(CODE_COND_JMP, op, zero, NOT_EQ, thisppt.label_true);
            thisppt.label_true->ref_num++;
            genCode1(CODE_JMP, thisppt.label_false);
        } else
            thisppt.error = 1;
        delExpr(n.ppt.type_syn);
    }
}
MakeFunction(args)
{   //attr: type_syn
    //delExpr at -exp- -args-
    //fix error at -exp-
    //assert(0);
    assert(unit->syn_type == Args);
    MakeObj(exp, n0, emptyPPT);
    n0.creator(&n0,unit->symbol[0].syn_child);
    Operand arg;
    if(n0.ppt.isRef){
        arg = getTmpVarName();
        genCode2(CODE_ASSIGN_FROM, arg, n0.ppt.place);
    }else{
        arg = n0.ppt.place;
    }
    if(n0.ppt.error){
        thisppt.error = 1;
    }
    if(unit->symbol_num>1)
    {
        MakeObj(args,n2, emptyPPT);
        n2.creator(&n2,unit->symbol[2].syn_child);
        if(!n2.ppt.error && !n0.ppt.error){           //error happen in ParamDec
            thisppt.type_syn = wrapTuple(n0.ppt.type_syn, n2.ppt.type_syn);
            // follow the args behind
            // exp.place could be a variable or address
            genCode1(CODE_ARG, arg);
        } else {
            thisppt.error = 1;
        }
        delExpr(n2.ppt.type_syn);

    }else{
        if(!n0.ppt.error){
            thisppt.type_syn = wrapTuple(n0.ppt.type_syn, NULL);
            genCode1(CODE_ARG, arg);
        }
    }
    delExpr(n0.ppt.type_syn);
    return ;
}