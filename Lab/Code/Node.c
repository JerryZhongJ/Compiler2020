#include "Node.h"
#define NULL 0
#define _thisppt _this->ppt
MakeFunction(program)
{
    Property p0 = newPpt();
    p0.cur = initSymbols(NULL);
    p0.prev = NULL;
    MakeObj(extDefList, n0, p0);
    n0.creator(&n0, unit->symbol[0].syn_child);
    return;
}
MakeFunction(extDefList)
{
    //attr: cur, prev
    if(unit == NULL)
        return;
    Property p0 = newPpt();
    p0.cur = _thisppt.cur;
    p0.prev = _thisppt.prev;

    MakeObj(extDef, n0, p0);
    n0.creator(&n0, unit->symbol[0].syn_child);
    MakeObj(extDefList, n1, p0);
    n1.creator(&n1, unit->symbol[1].syn_child);
    return;
}
MakeFunction(extDef)
{
    //cur, prev
    Property p0 = newPpt();
    p0.cur = _thisppt.cur;
    p0.prev = _thisppt.prev;

    MakeObj(specifier, n0, p0);
    n0.creator(&n0, unit->symbol[0].syn_child);

    if (unit->symbol_type[1] == LEX)
    {
        // do nothing
    }
    else if (unit->symbol[1].syn_child->syn_type == ExtDecList)
    {
        Property p1 = newPpt();
        p1.cur  = _thisppt.cur;
        p1.prev = _thisppt.prev;
        p1.type_inh = wrapSpeci(n0.ppt.speci);
        MakeObj(extDecList, n1, p1); //inherance Specifier Type
        n1.creator(&n1, unit->symbol[1].syn_child);
        //SEMI
    }
    else
    {
        assert(unit->symbol[1].syn_child->syn_type == FunDec);
        assert(unit->symbol[2].syn_child->syn_type == CompSt);

        Property p1 = newPpt();
        p1.cur = _thisppt.cur;
        p1.prev = _thisppt.prev;
        p1.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(funDec, n1, p1);
        n1.creator(&n1, unit->symbol[1].syn_child);

        Property p2 = newPpt();
        p2.cur = symbols;           // including param 
        p2.prev = _thisppt.prev;
        p2.type_inh = p1.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(compSt, n2, p2); //this inherance may not be neccessary
        n2.creator(&n2, unit->symbol[2].syn_child);

        pop(symbols, _thisppt.cur); //pop paramlist
    }
}
MakeFunction(extDecList)
{
    //attr: cur, prev, type_inh
    Property p0 = newPpt();
    p0.cur = _thisppt.cur;
    p0.prev = _thisppt.prev;

    MakeObj(varDec, n0, p0); //syn_child varDec get the inherance property
    n0.creator(&n0, unit->symbol[0].syn_child);
    if (unit->symbol_num > 1)
    {
        //COMMA
        Property p2 = newPpt();
        p2.cur = _thisppt.cur;
        p2.prev = _thisppt.prev;
        p2.type_inh = copyExpr(_thisppt.type_inh);
        MakeObj(extDecList, n2, p2);
    }
    delExpr(_thisppt.type_inh);
}
MakeFunction(specifier)
{
    //attr: speci cur, prev
    if (unit->symbol_type[0] == LEX)
    {
        LexUnit *lexunit = unit->symbol[0].lex_child;
        if(lexunit->iorf == TYPE_INT){
            _thisppt.speci = speci_int;
        }else if(lexunit->iorf == TYPE_FLOAT){
            _thisppt.speci = speci_float;
        }
    }
    else
    {
        assert(unit->symbol[0].syn_child->syn_type == StructSpecifier);
        Property p0 = newPpt();
        p0.cur = _thisppt.cur;
        p0.prev = _thisppt.prev;

        MakeObj(structSpecifier, n0, p0);
        n0.creator(&n0, unit->symbol[0].syn_child);

        _thisppt.speci = n0.ppt.speci;
    }
}
MakeFunction(structSpecifier)
{
    
    //attr: cur, prev, speci
    //fix error at Specifier
    assert(0);
    if (unit->symbol[1].syn_child->syn_type == OptTag)
    {
        Property p1 = newPpt();
        p1.cur = _thisppt.cur;
        p1.prev = _thisppt.prev;

        MakeObj(optTag, n1, p1);
        n1.creator(&n1, unit->symbol[1].syn_child);

        if(!n1.ppt.error){
            Property p3 = newPpt();
            SymbolTable field = p3.cur = newTable(NULL);
            p3.prev = NULL;
            MakeObj(defList, n3, p3);
            n3.creator(&n3, unit->symbol[3].syn_child);

            if(n3.ppt.error){               // if error in deflist
                pop(field, NULL);
                delExpr(n3.ppt.type_syn);
                withDraw(_thisppt.cur);
                _thisppt.error = 1;
            }else{
                TypeExpr type = wrapStruct(n3.ppt.type_syn);
                fillSpeci(n1.ppt.speci, type, field);
                _thisppt.speci = n1.ppt.speci;
                delExpr(n3.ppt.type_syn);
                delExpr(type);
            }
        }
       
    }
    else
    {
        Property p1 = newPpt();
        p1.cur = _thisppt.cur;
        p1.prev = _thisppt.prev;

        MakeObj(tag, n1, p1);
        n1.creator(&n1, unit->symbol[1].syn_child);
        if(n1.ppt.error){
            _thisppt.speci = NULL;
            _thisppt.error = 1;
        }
        else
        {

            _thisppt.speci = n1.ppt.speci;
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
        _thisppt.speci = applySpeci(_thisppt.cur, _thisppt.prev, "");
    }
    char *id = unit->symbol[0].lex_child->id;
    _thisppt.speci = applySpeci(_thisppt.cur, _thisppt.prev, id);
    if(_thisppt.speci == NULL){
        _thisppt.error = 1;
        printf("Error Type 16 at line %d: Redefined name \"%s\".\n", unit->lineno, id);
    }
}
MakeFunction(tag)
{
    //attr: cur, prev, speci
    //fix error at StructSpecifier
    assert(0);
    char *id = unit->symbol[0].lex_child->id;
    _thisppt.speci = lookup(_thisppt.cur, id);
    if(_thisppt.speci == NULL ||
        _thisppt.speci->var_speci == SPECI){
        _thisppt.error = 1;
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
        bool ret = appendVar(_thisppt.cur, _thisppt.prev, id, _thisppt.type_inh);
        if(ret == 0){
            print("Error Type 3 at Line %d: Redefined name \"%s\".\n", unit->lineno, id);
            _thisppt.error = 1;
        }
    }
    else
    {
        int num = unit->symbol[2].lex_child->ival;
        Property p0 = newPpt();
        p0.cur = _thisppt.cur;
        p0.prev = _thisppt.prev;
        p0.type_inh = wrapArray(_thisppt.type_inh, num);

        MakeObj(varDec, n0, p0);
        n0.creator(&n0, unit->symbol[0].syn_child);
        if(!n0.ppt.error){
            _thisppt.type_syn = copyExpr(n0.ppt.type_syn);
            delExpr(n0.ppt.type_syn);
        }
        else
        {
            _thisppt.error = 1;
        }
    }
    delExpr(_thisppt.type_inh);
}

MakeFunction(funDec)
{
    //attr: cur, prev, type_inh
    //fix error at ExtDef
    char *id = unit->symbol[0].lex_child->id;
    if(exist(global_func, NULL, id)){        //check func table
        _thisppt.error = 1;
        printf("Error Type 4 at Line %d: Refined function \"%s\".\n", unit->lineno, id);
        delExpr(_thisppt.type_inh);
        return;
    }

    if(unit->symbol_type[2] == ParamList){
        Property p2 = newPpt();
        p2.cur = newTable(_thisppt.cur);
        p2.prev = _thisppt.cur;


        MakeObj(paramList, n2, p2);
        n2.creator(&n2, unit->symbol[2].syn_child);

        if(!n2.ppt.error){
            TypeExpr tmp = wrapFun(n2.ppt.type_syn, _thisppt.type_inh);
            delExpr(n2.ppt.type_syn);
            bool ret = appendVar(global_func, NULL, id, tmp);
            delExpr(tmp);
        }else{
            _thisppt.error = 1;
        }
    }else{
        TypeExpr tmp = wrapFun(NULL, _thisppt.type_inh);
        bool ret = appendVar(global_func, NULL, id, tmp);
        delExpr(tmp);
    }

    delExpr(_thisppt.type_inh);
    return;
}
MakeFunction(paramList)
{
    //attr: type_syn, cur, prev
    //delExpr at paramList, FunDec
    //fix error at paramList FunDec
    assert(0);
    Property p0 = newPpt();
    p0.cur = _thisppt.cur;
    p0.prev = _thisppt.prev;
    p0.type_inh = _thisppt.type_inh;

    MakeObj(paramDec, n0, p0);
    n0.creator(&n0, unit->symbol[0].syn_child);

    if(n0.ppt.error){
        _thisppt.error = 1;
    }

    if (unit->symbol_num > 1)
    {
        //COMMA
        Property p2 = newPpt();
        p2.cur = _thisppt.cur;
        p2.prev = _thisppt.prev;

        MakeObj(paramList, n2, p2);
        n2.creator(&n2, unit->symbol[2].syn_child);

        if(!n2.ppt.error && !n0.ppt.error){           //error happen in ParamDec
            _thisppt.type_syn = wrapTuple(n0.ppt.type_syn, n2.ppt.type_syn);
            delExpr(n0.ppt.type_syn);
            delExpr(n2.ppt.type_syn);
        }
        else
        {
            _thisppt.error = 1;
        }
    }else {
        if(!n0.ppt.error){
            _thisppt.type_syn = wrapTuple(n0.ppt.type_syn, NULL);
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
    Property p0 = newPpt();
    p0.cur = _thisppt.cur;
    p0.prev = _thisppt.prev;

    MakeObj(specifier, n0, p0);
    n0.creator(&n0, unit->symbol[0].syn_child);

    if(!n0.ppt.error){
        Property p1 = newPpt();
        p1.cur = _thisppt.cur;
        p1.prev = _thisppt.prev;
        p1.type_inh = wrapSpeci(n0.ppt.speci);

        MakeObj(varDec, n1, p1); //inherant Specifier
        n1.creator(&n1, unit->symbol[1].syn_child);

        if(!n1.ppt.error){
            _thisppt.type_syn = wrapTuple(n1.ppt.type_syn, NULL);
            delExpr(n1.ppt.type_syn);
        }
        else
        {
            _thisppt.error = 1;
        }
    }else{
        _thisppt.error = 1;
        // do not return the type
    }

    return;
}
MakeFunction(compSt)
{
    //attr: type_inh, cur, prev
    SymbolTable local = newTable(_thisppt.cur);
    Property p0 = newPpt();
    p0.cur = local;
    p0.
    MakeObj(defList, n0, );
    n0.creator(&n0, unit->symbol[1].syn_child);
    MakeObj(stmtList, n1, );
    n1.creator(&n1, unit->symbol[2].syn_child);
    //here you need to destroy current stack
    delExpr(_thisppt.type_inh);
    return;
}
MakeFunction(stmtList)
{
    //type_inh, cur, prev
    if (unit->symbol_num == 0)
    {
       
    }
    else
    {
        MakeObj(stmt, n0, );
        n0.creator(&n0, unit->symbol[0].syn_child);
    }
    delExpr(_thisppt.type_inh);
}
MakeFunction(stmt)
{
    //type_inh, cur, prev
    if (unit->symbol_type[0] == LEX)
    {
        if (unit->symbol[0].lex_child->lex_type == RETURN)
        {
            MakeObj(exp, n0, );
            n0.creator(&n0, unit->symbol[1].syn_child);
            //TODO: check function return type, you may need n0.inh for help
        }
        else //IF AND WHILE
        {
            MakeObj(exp, n0, );
            n0.creator(&n0, unit->symbol[2].syn_child);
            MakeObj(stmt, n1, );
            n1.creator(&n1, unit->symbol[4].syn_child);
            if (unit->symbol_num > 5) // IF ELSE
            {
                MakeObj(stmt, n2, );
                n2.creator(&n2, unit->symbol[6].syn_child);
            }
        }
    }
    else
    {
        if (unit->symbol[0].syn_child->syn_type == Exp)
        {
            MakeObj(exp, n0, );
            n0.creator(&n0, unit->symbol[0].syn_child);
        }
        else
        {
            MakeObj(compSt,n0,);
            n0.creator(&n0,unit->symbol[0].syn_child);
        }
    }
    delExpr(_thisppt.type_inh);
}
MakeFunction(defList)
{
    //attr: cur, prev
    if(unit->symbol_num == 0)
    {
        return;
    }
    else
    {
        MakeObj(def,n0,);
        n0.creator(&n0,unit->symbol[0].syn_child);
        MakeObj(defList,n1,);//inherance def
        n1.creator(&n1,unit->symbol[1].syn_child);
        return;
    }
}
MakeFunction(def)
{
    //attr:  cur, prev, type_syn
    //delExpr at defList
    assert(0);
    MakeObj(specifier, n0, );
    n0.creator(&n0,unit->symbol[0].syn_child);
    _thisppt.property |= n0.ppt.property;
    MakeObj(decList,n1,);
    n1.creator(&n1,unit->symbol[1].syn_child);
    
    return;
}
MakeFunction(decList)
{
    // attr: type_inh, cur, prev, type_syn
    // delExpr at Def
    MakeObj(dec,n0,);
    n0.creator(&n0,unit->symbol[0].syn_child);
    if(unit->symbol_num>1)
    {
        MakeObj(decList,n1,);
        n1.creator(&n1,unit->symbol[1].syn_child);
    }
    delExpr(_thisppt.type_inh);
    return;
}
MakeFunction(dec)
{
    //attr: type_inh, cur, prev, type_syn
    //delExpr at declist
    assert(0);

    MakeObj(varDec, n0, );
    n0.creator(&n0,unit->symbol[0].syn_child);
    if(unit->symbol_num>1)
    {
        MakeObj(exp,n1,);
        //TODO: you should check exp type == varDec
        //you may need n1.inh to help
    }
    delExpr(_thisppt.type_inh);
    return;
}
MakeFunction(exp)
{
    //attr: type_inh, isLvalue;
    // delExpr at stmt, exp
    assert(0);
    if (unit->symbol_type[0] == LEX)
    {
        if(unit->symbol[0].lex_child->lex_type == INT)
        {
            _thisppt.property |= P_INT;
            return;
        }
        else if(unit->symbol[0].lex_child->lex_type == FLOAT)
        {
            _thisppt.property |= P_FLOAT;
            return; 
        }
        else if(unit->symbol[0].lex_child->lex_type == ID)
        {
            if(unit->symbol_num == 1)
            {
                //TODO : look up the table and get property to fill _this->inh.property
                //NOTE that you should check _this->inh ,to decide the id is a function or struct or normal id
                return;
            }
            else
            {
                //TODO: look up the table and get func def params
                if(unit->symbol_num == 3)
                {
                    //TODO:make sure that func def has empty deflist
                    return;
                }
                else
                {
                    _thisppt.property |= P_FUNC;
                    //TODO:link this function id ptr in talbe to _this->inh.sign_ptr //args are part of function that id points to
                    MakeObj(args,n0,);
                    n0.ppt.depth = 0;//args idx = 0
                    n0.creator(&n0,unit->symbol[2].syn_child);//it will match paramList
                    return;
                }
            }
        }
        else if(unit->symbol[1].lex_child->lex_type == LB)//array
        {   
            //decide dimension
            if(_thisppt.property&P_ARRAY == P_ARRAY)
            {
                _thisppt.depth++;
            }
            else
            {
                _thisppt.property |=P_ARRAY;
                _thisppt.depth = 0;
            }
            Property p;//EMPTY property
            MakeObj(exp,n0,p);
            n0.creator(&n0,unit->symbol[2].syn_child);
            //TODO: check -- n0 should be INT type
            MakeObj(exp,n1,);
            n1.creator(&n1,unit->symbol[0].syn_child);
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
                        _thisppt = n0.ppt;
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
    _thisppt.depth++;
    if(unit->symbol_num>1)
    {
        MakeObj(args,n1,);
        n1.creator(&n1,unit->symbol[2].syn_child);
    }
    return ;
}