#include "Node.h"
#include<stdio.h>
#include<assert.h>
#include<string.h>

#define makePPT(a) Property a = {0, 0, 0, 0, 0, 0} 
#define emptyPPT {0, 0, 0, 0, 0, 0}
#define thisppt _this->ppt

//remember to delete type_inh at the end of function
//remember to delete type_syn when father has use it
// check sym_type after lookup
// ckeck copyExpr
MakeFunction(program)
{
    initSymbols();
    
    MakeObj(extDefList, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[0].syn_child);
    return;
}
MakeFunction(extDefList)
{
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
        assert(unit->symbol[1].syn_child->syn_type == FunDec);
        assert(unit->symbol[2].syn_child->syn_type == CompSt);

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
    

    MakeObj(varDec, n0, emptyPPT); //syn_child varDec get the inherance property
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
    assert(0);
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
    //attr: speci
    //fix error at StructSpecifier
    assert(0);
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
        }
    }
    else
    {
        int num = unit->symbol[2].lex_child->ival;
        makePPT(p0);
        p0.type_inh = wrapArray(thisppt.type_inh, num);

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
    char *id = unit->symbol[0].lex_child->id;
    if(exist(symbols, id)){        //check func table
        thisppt.error = 1;
        printf("Error Type 4 at Line %d: Redefined function \"%s\".\n", unit->lineno, id);
    }

    if(unit->symbol_type[2] == ParamList){
        symbols = newTable(symbols);

        MakeObj(paramList, n2, emptyPPT);
        n2.creator(&n2, unit->symbol[2].syn_child);

        symbols = delNode(symbols); //delete the fake node, to make params part of CompSt
        //no matter if there is an error in paramlist
        if (!n2.ppt.error)
        {
            TypeExpr tmp = wrapFunc(n2.ppt.type_syn, thisppt.type_inh);
            bool ret = appendFunc(symbols, id, tmp);
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
 

    MakeObj(specifier, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[0].syn_child);

    if(!n0.ppt.error){
        makePPT(p1);
        p1.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(varDec, n1, p1); //inherant Specifier
        n1.creator(&n1, unit->symbol[1].syn_child);

        if(!n1.ppt.error){
            thisppt.type_syn = wrapTuple(n1.ppt.type_syn, NULL);
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
    }
    delExpr(thisppt.type_inh);
}
MakeFunction(stmt)
{
    //attr: type_inh
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
                thisppt.type_syn = wrapTuple(n0.ppt.type_syn, n1.ppt.type_syn);
        }else{
            thisppt.error = 1;
        }
        delExpr(n0.ppt.type_syn);
        delExpr(n1.ppt.type_syn);
    }
}
MakeFunction(def)
{
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
        makePPT(p1);
        p1.inStruct = thisppt.inStruct;
        p1.type_inh = copyExpr(thisppt.type_inh);

        MakeObj(decList, n1, p1);
        n1.creator(&n1,unit->symbol[1].syn_child);

        if(!n1.ppt.error && !n0.ppt.error){
            if(thisppt.inStruct)
                thisppt.type_syn = wrapTuple(n0.ppt.type_syn, n1.ppt.type_syn);
        }else{
            thisppt.error = 1;
        }
        delExpr(n1.ppt.type_syn);
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
    //attr: type_inh, type_syn, inStruct
    //delExpr at -declist-
    //fix error at -declist-
    //assert(0);
    makePPT(p0);
    p0.type_inh = copyExpr(thisppt.type_inh);

    MakeObj(varDec, n0, p0);
    n0.creator(&n0,unit->symbol[0].syn_child);

    if(unit->symbol_num>1)
    {
        if(thisppt.inStruct){
            printf("Error Type 16 al Line %d: Cannot initialize in struct.\n", unit->lineno);
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
MakeFunction(exp)
{
    //attr: type_inh, isLvalue;
    // delExpr at -stmt-, -exp-, -args-
    //checkout error at -stmt- -exp-
    //assert(0);
    if (unit->symbol_type[0] == LEX)
    {
        if(unit->symbol[0].lex_child->lex_type == INT)
        {
            thisppt.type_syn = wrapSpeci(speci_int);
            thisppt.isLvalue = false;
        }
        else if(unit->symbol[0].lex_child->lex_type == FLOAT)
        {
            thisppt.type_syn = wrapSpeci(speci_float);
            thisppt.isLvalue = false;
        }
        else if(unit->symbol[0].lex_child->lex_type == ID)
        {
            char *id = unit->symbol[0].lex_child->id;
            if(unit->symbol_num == 1)
            {
                
                VarNode *var = lookup(symbols, id);
                if(var == NULL || var->symbol_type != NODE_VAR){
                    printf("Error Type 1 at Line %d: Undefined variable \"%s\".\n", unit->lineno, id);
                    thisppt.error = 1;
                }else{
                    thisppt.type_syn = copyExpr(var->type);
                    thisppt.isLvalue = 1;
                }
            }
            else
            {
                //TODO: look up the table and get func def params
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
                        if(param != NULL){
                            printf("Error Type 9 at Line %d: Arguments do not match the parameters of function \"%s\".\n", unit->lineno, id);
                            thisppt.error = 1;
                        }else{
                            thisppt.type_syn = copyExpr(ret);
                            thisppt.isLvalue = false;
                        }
                    }
                }
                if(unit->symbol_num == 4)
                {

                    MakeObj(args, n2, emptyPPT);
                    n2.creator(&n2, unit->symbol[2].syn_child); //it will match paramList

                    if(func != NULL && !n2.ppt.error ){
                        if(type_equiv(n2.ppt.type_syn, param)){
                            thisppt.type_syn = copyExpr(ret);
                            thisppt.isLvalue = false;   
                        }else{
                            printf("Error Type 9 at Line %d: Arguments do not match the parameters of function \"%s\".\n", unit->lineno, id);
                            thisppt.error = 1;
                        }
                        
                    }else 
                        thisppt.error = 1;

                    delExpr(n2.ppt.type_syn);
                }
            }
        }
    }
    else if(unit->symbol[1].lex_child->lex_type == LB)//array
    {   
        //ID LB INT RB
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


        //TODO: now you get a sign_ptr in n0.inh which point to exp(id.id....id)
        //then ,check whether exp.(unit->symbol[2].id) in the table
        if(!n0.ppt.error){
            
            if(!isStruct(n0.ppt.type_syn)){
                thisppt.error = 1;
                printf("Error Type 13 at Line %d: Expression before \'.\' is not a struct type.\n", unit->lineno);
            }else{
                char *id = unit->symbol[2].lex_child->id;
                SpecifierNode *speci = n0.ppt.type_syn->speci;
                VarNode *var = lookup(speci->sym_table, id);
                if(var == NULL && var->symbol_type != NODE_VAR){
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
    else  if(unit->symbol_num == 3){
        if(unit->symbol_type[1] == SYN){
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
        }else if(unit->symbol[1].lex_child->lex_type == ASSIGNOP){
            // Exp ASSIGNOP Exp
            MakeObj(exp, n0, emptyPPT);
            n0.creator(&n0, unit->symbol[0].syn_child);

            MakeObj(exp, n2, emptyPPT);
            n2.creator(&n2, unit->symbol[2].syn_child);

            if (!n0.ppt.error && !n2.ppt.error)
            {
                if(n0.ppt.isLvalue == false){
                    printf("Error Type 6 at Line %d: Expression is not lvalue on the left side of \'=\'.\n", unit->lineno);
                }
                if(!type_equiv(n0.ppt.type_syn, n2.ppt.type_syn)){
                    printf("Error Type 5 at Line %d: Types do not match on the two side of \'=\'.\n", unit->lineno);
                    thisppt.error = 1;
                }else{
                    thisppt.type_syn = copyExpr(n0.ppt.type_syn);
                    thisppt.isLvalue = 1;
                }
            }
            else
            {
                thisppt.error = 1;
            }
            delExpr(n0.ppt.type_syn);
            delExpr(n2.ppt.type_syn);

        }else{
            // + - * / relop and or
            MakeObj(exp, n0, emptyPPT);
            n0.creator(&n0, unit->symbol[0].syn_child);

            MakeObj(exp, n2, emptyPPT);
            n2.creator(&n2, unit->symbol[2].syn_child);

            if (!n0.ppt.error && !n2.ppt.error)
            {
                if(!isInt(n0.ppt.type_syn) || !isFloat(n0.ppt.type_syn)
                    || !isInt(n2.ppt.type_syn) || !isFloat(n2.ppt.type_syn)){
                    printf("Error Type 7 at Line %d: Operands's type should be int or float.\n", unit->lineno);
                    thisppt.error = 1;
                }else if(!type_equiv(n0.ppt.type_syn, n2.ppt.type_syn)){
                    printf("Error Type 5 at Line %d: Types do not match on the two side of operator.\n", unit->lineno);
                    thisppt.error = 1;
                }else{
                    thisppt.type_syn = copyExpr(n0.ppt.type_syn);
                    thisppt.isLvalue = 0;
                }
            }
            else
            {
                thisppt.error = 1;
            }
            delExpr(n0.ppt.type_syn);
            delExpr(n2.ppt.type_syn);
        }
    }else{
        //NOT Expr
        //minus Expr
        MakeObj(exp, n1, emptyPPT);
        n1.creator(&n1, unit->symbol[1].syn_child);
        if(!n1.ppt.error){
             if(!isInt(n1.ppt.type_syn) || !isFloat(n1.ppt.type_syn)){
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
    }
}
MakeFunction(args)
{   //attr: type_syn
    //delExpr at -exp- -args-
    //fix error at -exp-
    //assert(0);
    MakeObj(exp, n0, emptyPPT);
    n0.creator(&n0,unit->symbol[0].syn_child);
    //TODO: here ,you should match function define args by _this->inh.depth/sign_ptr
    if(n0.ppt.error){
        thisppt.error = 1;
    }
    if(unit->symbol_num>1)
    {
        MakeObj(args,n2, emptyPPT);
        n2.creator(&n2,unit->symbol[2].syn_child);
        if(!n2.ppt.error && !n0.ppt.error){           //error happen in ParamDec
            thisppt.type_syn = wrapTuple(n0.ppt.type_syn, n2.ppt.type_syn);
        }
        else
        {
            thisppt.error = 1;
        }
        delExpr(n2.ppt.type_syn);

    }else{
        if(!n0.ppt.error){
            thisppt.type_syn = wrapTuple(n0.ppt.type_syn, NULL);
            delExpr(n0.ppt.type_syn);
        }
    }
    delExpr(n0.ppt.type_syn);
    return ;
}