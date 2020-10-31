#include "Node.h"
#define NULL 0
#define makePPT(a) Property a = {0, 0, 0, 0, 0, 0} 
#define emptyPPT {0, 0, 0, 0, 0, 0}
#define thisppt _this->ppt

//remember to delete type_inh at the end of function
//remember to delete type_syn when father has use it
MakeFunction(program)
{
    initSymbols();
    
    MakeObj(extDefList, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[0].syn_child);
    return;
}
MakeFunction(extDefList)
{
    //attr: cur, prev
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
    //cur, prev
    

    MakeObj(specifier, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[0].syn_child);

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

        makePPT(p2);
        p2.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(compSt, n2, p2); //this inherance may not be neccessary
        n2.creator(&n2, unit->symbol[2].syn_child);
    }
}
MakeFunction(extDecList)
{
    //attr: cur, prev, type_inh
    

    MakeObj(varDec, n0, emptyPPT); //syn_child varDec get the inherance property
    n0.creator(&n0, unit->symbol[0].syn_child);
    if (unit->symbol_num > 1)
    {
        //COMMA
        makePPT(p2);
        p2.type_inh = copyExpr(thisppt.type_inh);
        MakeObj(extDecList, n2, p2);
    }
    delExpr(thisppt.type_inh);
}
MakeFunction(specifier)
{
    //attr: speci cur, prev
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

        thisppt.speci = n0.ppt.speci;
    }
}
MakeFunction(structSpecifier)
{
    
    //attr: cur, prev, speci
    //fix error at Specifier
    assert(0);
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
            for (; node->next != NULL && node->next->symbol_type != FAKE;node = node->next)
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
    //cur, prev, speci
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
    //attr: cur, prev, speci
    //fix error at StructSpecifier
    assert(0);
    char *id = unit->symbol[0].lex_child->id;
    thisppt.speci = lookup(symbols, id);
    if(thisppt.speci == NULL ||
        thisppt.speci->symbol_type != SYM_SPECI){
        thisppt.error = 1;
    }
    return;
}
MakeFunction(varDec)
{
    //cur, prev, type_inh, type_syn
    //remember delExpr at ExtDecList ParamDec Dec VarDec
    //fix error at ExtDecList ParamDec Dec VarDec
    assert(0);
    if (unit->symbol_type[0] == LEX)
    {
        char *id = unit->symbol[0].lex_child->id;
        bool ret = appendVar(symbols, id, thisppt.type_inh);
        if(ret == 0){
            if(thisppt.inStruct)
                print("Error Type 15 at Line %d: Redefined field name \"%s\" in a struct.\n", unit->lineno, id);
            else
                print("Error Type 3 at Line %d: Redefined variable \"%s\".\n", unit->lineno, id);
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
        if(!n0.ppt.error){
            thisppt.type_syn = copyExpr(n0.ppt.type_syn);
            delExpr(n0.ppt.type_syn);
        }
        else
        {
            thisppt.error = 1;
        }
    }
    delExpr(thisppt.type_inh);
}

MakeFunction(funDec)
{
    //attr: cur, prev, type_inh
    //fix error at ExtDef
    assert(0);
    char *id = unit->symbol[0].lex_child->id;
    if(exist(global_func, id)){        //check func table
        thisppt.error = 1;
        printf("Error Type 4 at Line %d: Refined function \"%s\".\n", unit->lineno, id);
    }

    if(unit->symbol_type[2] == ParamList){
        symbols = newTable(symbols);

        MakeObj(paramList, n2, emptyPPT);
        n2.creator(&n2, unit->symbol[2].syn_child);

        symbols = delNode(symbols); //delete the fake node, to make params part of CompSt
        //no matter if there is an error in paramlist
        if (!n2.ppt.error)
        {
            TypeExpr tmp = wrapFun(n2.ppt.type_syn, thisppt.type_inh);
            delExpr(n2.ppt.type_syn);
            bool ret = appendVar(global_func, id, tmp);
            delExpr(tmp);
        }
        else
        {
            thisppt.error = 1;
        }
    }else{
        TypeExpr tmp = wrapFun(NULL, thisppt.type_inh);
        bool ret = appendVar(global_func, NULL, id, tmp);
        delExpr(tmp);
    }

    delExpr(thisppt.type_inh);
    return;
}
MakeFunction(paramList)
{
    //attr: type_syn, cur, prev
    //delExpr at paramList, FunDec
    //fix error at paramList FunDec
    assert(0);
    

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
            delExpr(n0.ppt.type_syn);
            delExpr(n2.ppt.type_syn);
        }
        else
        {
            thisppt.error = 1;
        }
    }else {
        if(!n0.ppt.error){
            thisppt.type_syn = wrapTuple(n0.ppt.type_syn, NULL);
            delExpr(n0.ppt.type_syn);
        }
    }
    return;
}
MakeFunction(paramDec)
{
    //attr: type_syn, cur, prev
    //delExpr at paramList
    assert(0);
 

    MakeObj(specifier, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[0].syn_child);

    if(!n0.ppt.error){
        makePPT(p1);
        p1.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(varDec, n1, p1); //inherant Specifier
        n1.creator(&n1, unit->symbol[1].syn_child);

        if(!n1.ppt.error){
            thisppt.type_syn = wrapTuple(n1.ppt.type_syn, NULL);
            delExpr(n1.ppt.type_syn);
        }
        else
        {
            thisppt.error = 1;
        }
    }else{
        thisppt.error = 1;
        // do not return the type
    }

    return;
}
MakeFunction(compSt)
{
    //attr: type_inh, cur, prev
    symbols = newTable(symbols);

    MakeObj(defList, n0, emptyPPT);
    n0.creator(&n0, unit->symbol[1].syn_child);

    makePPT(p1);
    p1.type_inh = copyExpr(thisppt.type_inh);

    MakeObj(stmtList, n1, p1);
    n1.creator(&n1, unit->symbol[2].syn_child);
    //here you need to destroy current stack
    symbols = pop(symbols); //maybe including param
    delExpr(thisppt.type_inh);
    return;
}
MakeFunction(stmtList)
{
    //type_inh, cur, prev
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

        makePPT(p1);
        p1.type_inh = copyExpr(thisppt.type_inh);
    }
    delExpr(thisppt.type_inh);
}
MakeFunction(stmt)
{
    //type_inh, cur, prev
    if (unit->symbol_type[0] == LEX)
    {
        if (unit->symbol[0].lex_child->lex_type == RETURN)
        {
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
            MakeObj(exp, n0, emptyPPT);
            n0.creator(&n0, unit->symbol[0].syn_child);
            delExpr(n0.ppt.type_syn);
        }
        else
        {
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
    //attr: cur, prev
    //delete expr at struct deflist compstmt
    //fix error at struct deflist compstmt
    assert(0);
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
            this.ppt.error = 1;
        }
        delExpr(n0.ppt.type_syn);
        delExpr(n1.ppt.type_syn);
    }
}
MakeFunction(def)
{
    //attr:  cur, prev, type_syn
    //delExpr at defList
    //fix error at deflist
    assert(0);
    MakeObj(specifier, n0, emptyPPT);
    n0.creator(&n0,unit->symbol[0].syn_child);
    if(!n0.ppt.error){
        makePPT(p1);
        p1.inStruct = thisppt.inStruct;
        p1.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(decList, n1, p1);
        n1.creator(&n1,unit->symbol[1].syn_child);

        if(!n1.ppt.error){
            if(thisppt.inStruct){
                thisppt.type_syn = copyExpr(n1.ppt.type_syn);
                delExpr(n1.ppt.type_syn);
            }
        }else{
            thisppt.error = 1;
        }
    }else{
        thisppt.error = 1;
    }

     return;
}
MakeFunction(decList)
{
    // attr: type_inh, cur, prev, type_syn
    // delExpr at Def
    //fix error declist, def
    assert(0);
    makePPT(p0);
    p0.inStruct = thisppt.inStruct;
    p0.ppt.type_inh = copyExpr(thisppt.type_inh);

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
            if(thisppt.inStruct){
                thisppt.type_syn = wrapTuple(n0.ppt.type_syn, n1.ppt.type_syn);
            }
        }else{
            thisppt.error = 1;
        }
    }else{
        if(!n0.ppt.error){
            if(thisppt.inStruct)
                thisppt.type_syn = wrapTuple(n0.ppt.type_syn, NULL);
        }else{
            thisppt.error = 1;
        }
    }
    delExpr(thisppt.type_inh);
    return;
}
MakeFunction(dec)
{
    //attr: type_inh, cur, prev, type_syn
    //delExpr at declist
    assert(0);
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
            MakeObj(exp,n1,emptyPPT);
            if(!n1.ppt.error && !type_equiv(n1.ppt.type_syn, n0.ppt.type_syn))
                printf("Error Type 5 at Line %d: Types do not match around \"=\".\n", unit->lineno);
            delExpr(n1.ppt.type_syn);
        }
    }
    delExpr(n0.ppt.type_syn);
    delExpr(thisppt.type_inh);
    return;
}
MakeFunction(exp)
{
    //attr: type_inh, isLvalue;
    // delExpr at stmt, exp
    //checkout error at stmt exp
    assert(0);
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
                if(var == NULL){
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
                VarNode *func = lookup(global_func, id);
                TypeExpr param = func->type->func.param;
                TypeExpr ret = func->type->func.ret;
                if(func == NULL){
                    printf("Error Type 2 at Line %d: Undefined function \"%s\".\n", unit->lineno, id);
                    thisppt.error = 1;
                }
                else if (unit->symbol_num == 3)
                {
                    
                    if(param != NULL){
                        printf("Error Type 9 at Line %d: Arguments do not match the parameters of function \"%s\".\n", unit->lineno, id);
                        thisppt.error = 1;
                    }else{
                        thisppt.type_syn = copyExpr(ret);
                        thisppt.isLvalue = false;
                    }
                }
                else
                {

                    MakeObj(args, n0, emptyPPT);
                    n0.creator(&n0, unit->symbol[2].syn_child); //it will match paramList
                    if(!n0.ppt.error && !type_equiv(n0.ppt.type_syn, param)){
                        printf("Error Type 9 at Line %d: Arguments do not match the parameters of function \"%s\".\n", unit->lineno, id);
                        thisppt.error = 1;
                    }else{
                        thisppt.type_syn = copyExpr(ret);
                        thisppt.isLvalue = false;
                    }
                }
            }
        }
        else if(unit->symbol[1].lex_child->lex_type == LB)//array
        {   
            //TODO: check -- n0 should be INT type
            MakeObj(exp,n0,emptyPPT);
            n0.creator(&n0,unit->symbol[0].syn_child);
            if(!n0.ppt.error == 1){

            }else{
                thisppt.error = 1;
            }

            MakeObj(exp,n2,emptyPPT);
            n2.creator(&n2,unit->symbol[2].syn_child);
            return;
        }
        else if(unit->symbol[1].lex_child->lex_type == DOT)
        {
            Property p;
            p.property |= P_STRUCT;
            MakeObj(exp,n0,p);
            n0.creator(&n0,unit->symbol[0].syn_child);
            //TODO: now you get a sign_ptr in n0.inh which point to exp(id.id....id)
            //then ,check whether exp.(unit->symbol[2].id) in the table
            return 0;
        }
        else
        {
            int count = 0;
            for(int i = 0;i<unit->symbol_num;++i)
            {
                if(unit->symbol[i].syn_child->syn_type == Exp)
                {
                    Property p;
                    MakeObj(exp,n0,p);
                    n0.creator(&n0,unit->symbol[i].syn_child);
                    if(count == 0)
                    {
                        thisppt = n0.ppt;
                        count++;
                    }
                    else
                    {
                        //TODO : check n0.inh and _this->inh
                    }
                }
            }
            return;
        }
    }
}
MakeFunction(args)
{   //attr: type_syn
    //delExpr at exp
    MakeObj(exp,n0,);
    n0.creator(&n0,unit->symbol[0].syn_child);
    //TODO: here ,you should match function define args by _this->inh.depth/sign_ptr
    thisppt.depth++;
    if(unit->symbol_num>1)
    {
        MakeObj(args,n1,);
        n1.creator(&n1,unit->symbol[2].syn_child);
    }
    return ;
}