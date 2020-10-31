/*************************************************************************
        > File Name: Node.h
        > Author:
        > Mail:
        > Created Time: Tue 10 Nov 2020 06:02:54 PM CST
 ************************************************************************/

#ifndef _NODE_H
#define _NODE_H
#include"common.h"
#include"semantic.h"
#include<stdlib.h>
//struct Obj_;
//typedef void (*func)(struct Obj_ *obj, SynUnit *unit);

#define P_FLOAT 0x1
#define P_INT 0x2
#define P_STRUCT 0x4
#define P_ARRAY 0x8
#define P_FUNC 0x10, 0

typedef unsigned uint32_t;

typedef struct Property_{
    TypeExpr type_inh;
    TypeExpr type_syn;
    SpecifierNode *speci;
    bool inStruct;
    bool isLvalue;
    bool error;
} Property;

typedef struct Obj_{
    Property ppt;
    void (*creator)(struct Obj_*, SynUnit* );
}Obj;


#define MakeObj(name,no,inh)\
    Obj no = {inh,concat(name,_creator)}

#define concat(a,b) a##b
#define MakeFunction(name) void concat(name,_creator)(Obj*_this,SynUnit*unit)

#define mmalloc(type,len) (type*)malloc(sizeof(type)*len)

MakeFunction(program);
MakeFunction(extDefList);
MakeFunction(extDef);
MakeFunction(extDecList);
MakeFunction(specifier);
MakeFunction(structSpecifier);
MakeFunction(optTag);
MakeFunction(tag);
MakeFunction(varDec);
MakeFunction(funDec);
MakeFunction(paramList);
MakeFunction(paramDec);
MakeFunction(compSt);
MakeFunction(stmtList);
MakeFunction(stmt);
MakeFunction(defList);
MakeFunction(def);
MakeFunction(decList);
MakeFunction(dec);
MakeFunction(exp);
MakeFunction(args);
#endif