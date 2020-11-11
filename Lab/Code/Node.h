/*************************************************************************
	> File Name: Node.h
	> Author: 
	> Mail: 
	> Created Time: Tue 10 Nov 2020 06:02:54 PM CST
 ************************************************************************/

#ifndef _NODE_H
#define _NODE_H
struct Syntax{
    int a;
};
typedef void(*func)(struct Syntax*unit);

struct Property{
    int a;
};

struct Obj{
    struct Property* inh;
    func creator;
};


#define MakeObj(name,no,inh)\
    struct Obj no = {inh,FuncName(name)}

#define FuncName_(name) name##_creator
#define FuncName(name) FuncName_(name) 
#define MakeFunction(name) void FuncName(name)(struct Syntax*unit)

MakeFunction(Program);
MakeFunction(ExtDefList);
MakeFunction(ExtDef);
MakeFunction(ExtDecList);
MakeFunction(Specifier);
MakeFunction(StructSpecifier);
MakeFunction(OpTag);
MakeFunction(Tag);
MakeFunction(VarDec);
MakeFunction(FunDec);
MakeFunction(ParamList);
MakeFunction(ParamDec);
MakeFunction(CompSt);
MakeFunction(StmtList);
MakeFunction(Stmt);
MakeFunction(DefList);
MakeFunction(Def);
MakeFunction(DecList);
MakeFunction(Dec);
MakeFunction(Exp);
MakeFunction(Args);
#endif
