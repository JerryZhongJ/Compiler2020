#include "Node.h"
#define NULL 0
MakeFunction(program)
{
    MakeObj(extDefList, n0, NULL);
    n0.creator(&n0, unit->symbol[0].child);
    return;
}
MakeFunction(extDefList)
{
    MakeObj(extDef, n0, NULL);
    n0.creator(&n0, unit->symbol[0].child);
    MakeObj(extDefList, n1, NULL);
    n1.creator(&n1, unit->symbol[1].child);
    return;
}
MakeFunction(extDef)
{
    MakeObj(specifier, n0, NULL);
    n0.creator(&n0, unit->symbol[0].child);
    if (unit->symbol_type[1] == LEX)
    {
        //SEMI
        return;
    }
    else if (unit->symbol[1].child->syn_type == ExtDefList)
    {
        MakeObj(extDecList, n1, n0.inh); //inherance Specifier Type
        n1.creator(&n1, unit->symbol[1].child);
        //SEMI
        return;
    }
    else
    {
        MakeObj(funDec, n1, n0.inh);
        n1.creator(&n1, unit->symbol[1].child);
        MakeObj(compSt, n2, n1.inh); //this inherance may not be neccessary
        n2.creator(&n2, unit->symbol[2].child);
        return;
    }
}
MakeFunction(extDecList)
{
    MakeObj(varDec, n0, _this->inh); //child varDec get the inherance property
    n0.creator(&n0, unit->symbol[0].child);
    if (unit->symbol_num > 1)
    {
        //COMMA
        MakeObj(extDecList, n1, _this->inh);
        return;
    }
}
MakeFunction(specifier)
{
    if (unit->symbol_type[0] == LEX)
    {
        _this->inh.property |= (unit->symbol[0].iorf) ? (P_INT) : (P_FLOAT); //synthesize to inherance property
        return;
    }
    else
    {
        MakeObj(structSpecifier, n0, NULL);
        n0.creator(&n0, unit->symbol[0].child);
        _this->inh = n0.inh;
        return;
    }
}
MakeFunction(structSpecifier)
{
    _this->inh.property |= P_STRUCT;
    if (unit->symbol[1].child->syn_type == OptTag)
    {
        MakeObj(optTag, n0, NULL);
        n0.creator(&n0, unit->symbol[1].child);
        MakeObj(defList, n1, n0.inh);
        return;
    }
    else
    {
        MakeObj(tag, n0, NULL);
        n0.creator(&n0, unit->symbol[1].child);
        return;
    }
}
MakeFunction(opTag)
{
    if (unit->symbol_num == 0) //for NULL
    {
        return;
    }
    else
    {
        //TODO:add opTag:ID to table
        return;
    }
}
MakeFunction(tag)
{
    //TODO:add tag:ID to table
    return;
}
MakeFunction(varDec)
{
    //decide the dimension
    if (_this->inh.property & P_ARRAY == P_ARRAY)
    {
        _this->inh.depth++;
    }
    else
    {
        _this->inh.property |= P_ARRAY;
        _this->inh.depth = 1;
    }

    if (unit->syn_type == LEX)
    {
        //TODO:add ID to table,you may need _this->inh to help
        //for array ,inh.depth also needed
        return;
    }
    else
    {
        MakeObj(varDec, n0, _this->inh);
        n0.creator(&n0, unit->symbol[0].child);
        //ignore array limit size
        return;
    }
}

MakeFunction(funDec)
{
    //TODO: add ID to table,attention! you should set this sign in a incomplete states, so more info(paramList) can be filled
    //LP
    _this->inh.property |= P_FUNC;
    MakeObj(paramList, n0, _this->inh);
    n0.creator(&n0, unit->symbol[2].child);
    //RP:
    //TODO:here you should stop filling info to ID
    return;
}
MakeFunction(paramList)
{
    MakeObj(paramDec, n0, _this->inh);
    n0.creator(&n0, unit->symbol[0].child);
    if (unit->symbol_num > 1)
    {
        //COMMA
        MakeObj(paramList, n1, _this->inh);
        n1.creator(&n1, unit->symbol[2].child);
    }
    return;
}
MakeFunction(paramDec)
{
    MakeObj(specifier, n0, _this->inh);
    n0.creator(&n0, unit->symbol[0].child);
    MakeObj(varDec, n1, n0.inh); //inherant Specifier
    n1.creator(&n1, unit->symbol[1].child);
    return;
}
MakeFunction(compSt)
{
    MakeObj(defList, n0, _this->inh);
    n0.creator(&n0, unit->symbol[1].child);
    MakeObj(stmtList, n1, _this->inh);
    n1.creator(&n1, unit->symbol[2].child);
    //here you need to destroy current stack
    return;
}
MakeFunction(stmtList)
{
    if (unit->symbol_num == 0)
    {
        return;
    }
    else
    {
        MakeObj(stmt, n0, _this->inh);
        n0.creator(&n0, unit->symbol[0].child);
    }
}
MakeFunction(stmt)
{
    if (unit->symbol_type[0] == LEX)
    {
        if (unit->symbol[0].lex_type == RETURN)
        {
            MakeObj(exp, n0, _this->inh);
            n0.creator(&n0, unit->symbol[1].child);
            //TODO: check function return type, you may need n0.inh for help
            return;
        }
        else //IF AND WHILE
        {
            MakeObj(exp, n0, _this->inh);
            n0.creator(&n0, unit->symbol[2].child);
            MakeObj(stmt, n1, _this->inh);
            n1.creator(&n1, unit->symbol[4].child);
            if (unit->symbol_num > 5) // IF ELSE
            {
                MakeObj(stmt, n2, _this->inh);
                n2.creator(&n2, unit->symbol[6].child);
            }
            return;
        }
    }
    else
    {
        if (unit->symbol[0].child->syn_type == Exp)
        {
            MakeObj(exp, n0, _this->inh);
            n0.creator(&n0, unit->symbol[0].child);
        }
        else
        {
            MakeObj(compSt,n0,_this->inh);
            n0.creator(&n0,unit->symbol[0].child);
        }
        return ;
    }
}
MakeFunction(defList)
{
    if(unit->symbol_num == 0)
    {
        return;
    }
    else
    {
        MakeObj(def,n0,_this->inh);
        n0.creator(&n0,unit->symbol[0].child);
        MakeObj(defList,n1,n0.inh);//inherance def
        n1.creator(&n1,unit->symbol[1].child);
        return;
    }
}
MakeFunction(def)
{
    MakeObj(specifier,n0,_this->inh);
    n0.creator(&n0,unit->symbol[0].child);
    _this->inh.property |= n0.inh.property;
    MakeObj(decList,n1,n0.inh);
    n1.creator(&n1,unit->symbol[1].child);
    return;
}
MakeFunction(decList)
{
    MakeObj(dec,n0,_this->inh);
    n0.creator(&n0,unit->symbol[0].child);
    if(unit->symbol_num>1)
    {
        MakeObj(decList,n1,_this->inh);
        n1.creator(&n1,unit->symbol[1].child);
    }
    return ;
}
MakeFunction(dec)
{
    MakeObj(varDec,n0,_this->inh);
    n0.creator(&n0,unit->symbol[0].child);
    if(unit->symbol_num>1)
    {
        MakeObj(exp,n1,_this->inh);
        //TODO: you should check exp type == varDec
        //you may need n1.inh to help
    }
    return;
}
MakeFunction(exp)
{
    //exp should fill its inh 
    if(unit->syn_type[0] == LEX)
    {
        if(unit->symbol[0].lex_type == INT)
        {
            _this->inh.property |= P_INT;
            return;
        }
        else if(unit->symbol[0].lex_type == FLOAT)
        {
            _this->inh.property |= P_FLOAT;
            return; 
        }
        else if(unit->symbol[0].lex_type == ID)
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
                    _this->inh.property |= P_FUNC;
                    //TODO:link this function id ptr in talbe to _this->inh.sign_ptr //args are part of function that id points to
                    MakeObj(args,n0,_this->inh);
                    n0.inh.depth = 0;//args idx = 0
                    n0.creator(&n0,unit->symbol[2].child);//it will match paramList
                    return;
                }
            }
        }
        else if(unit->symbol[1].lex_type == LB)//array
        {   
            //decide dimension
            if(_this->inh.property&P_ARRAY == P_ARRAY)
            {
                _this->inh.depth++;
            }
            else
            {
                _this->inh.property |=P_ARRAY;
                _this->inh.depth = 0;
            }
            Property p;//EMPTY property
            MakeObj(exp,n0,p);
            n0.creator(&n0,unit->symbol[2].child);
            //TODO: check -- n0 should be INT type
            MakeObj(exp,n1,_this->inh);
            n1.creator(&n1,unit->symbol[0].child);
            return;
        }
        else if(unit->symbol[1].lex_type == DOT)
        {
            Property p;
            p.property |= P_STRUCT;
            MakeObj(exp,n0,p);
            n0.creator(&n0,unit->symbol[0].child);
            //TODO: now you get a sign_ptr in n0.inh which point to exp(id.id....id)
            //then ,check whether exp.(unit->symbol[2].id) in the table
            return 0;
        }
        else
        {
            int count = 0;
            for(int i = 0;i<unit->symbol_num;++i)
            {
                if(unit->symbol[i].child->syn_type == EXP)
                {
                    Property p;
                    MakeObj(exp,n0,p);
                    n0.creator(&n0,unit->symbol[i].child);
                    if(count == 0)
                    {
                        _this->inh = n0.inh;
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
{   //_this->inh.property has P_FUNC
    MakeObj(exp,n0,_this->inh);
    n0.creator(&n0,unit->symbol[0].child);
    //TODO: here ,you should match function define args by _this->inh.depth/sign_ptr
    _this->inh.depth++;
    if(unit->symbol_num>1)
    {
        MakeObj(args,n1,_this->inh);
        n1.creator(&n1,unit->symbol[2].child);
    }
    return ;
}
