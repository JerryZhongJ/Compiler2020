#ifndef __SEMANTIC__
#define __SEMANTIC__

#include<stdbool.h>
#include<stdlib.h>
#include"InterCode.h"
#define MAX_ID_LENGHT 100
#define TypeExpr struct TypeOperator* //被这依赖关系搞烦了
struct TypeOperator;
typedef enum SymNodeType
{
    NODE_VAR,
    NODE_SPECI,
    NODE_FUNC,
    NODE_FAKE
} SymNodeType;
typedef struct SymbolNode
{
    char *name;     // independent from those in the tree
    enum SymNodeType symbol_type;
    TypeExpr type;  // when is var, it represent the type of the variable
                    // when is specifier
                    // independent from those in the tree
    struct SymbolNode* sym_table; //valid when symbol is a specifier
    Operand inter_name;
    int width;
    int offset;
    struct SymbolNode *next;
} SymbolNode, *SymbolTable;
/*
带伪表头

*/

enum TypeOperator_t
{ //算子类型
    SPECIFIER,
    ARRAY,
    FUNCTION,
    TUPLE,
    _STRUCT,
};


typedef struct TypeArray
{
    TypeExpr expr;       
    int num;
    //int element_width;
} TypeArray;
typedef struct TypeFunc{
    TypeExpr param;       //expected to be a tuple
    TypeExpr ret;        //expected to be specifier
} TypeFunc;
typedef struct TypeTuple{
    TypeExpr expr;      //expected to be a specifier
    TypeExpr next;     //expected to be tuple
} TypeTuple;
//Tuple本质上就是类型名的链表
typedef struct TypeStruct{
    TypeExpr varlist; //expected to be a tuple
} TypeStruct;

#undef TypeExpr     

typedef struct TypeOperator
{
    enum TypeOperator_t op_type;
    int width;
    union {
        SymbolNode *speci;
        TypeArray array;
        TypeFunc func;
        TypeTuple tuple;
        TypeStruct _struct;
    };
} TypeOperator, *TypeExpr;             
/*
所有表达式的类型, 符号表中的类型都用TypeExpr来包装, 即便一个变量是int或float型的.
符号表里的是类型名specifier, 是被TypeExpr引用的.

为了防止两个表达式包含同一个子表达式, 使用拷贝函数!

使父子之间不共享同一个表达式, 使符号表不使用分析树中的表达式


TypeExpr作为综合属性值type_syn时, 应该由父节点进行删除.
TypeExpr作为继承属性值type_inh时, 应该在此节点删除.
*/

SymbolTable symbols;      //变量表




SymbolNode *speci_int;  //"int"的符号表项
SymbolNode *speci_float; //"float"的符号表项
SymbolNode *func_read;
SymbolNode *func_write;

SymbolNode *delNode(SymbolNode* );
void delExpr(TypeExpr expr);

SymbolNode* appendVar(SymbolTable table, char *name, TypeExpr expr);
SymbolNode* appendFunc(SymbolTable table, char *name);
//成功返回1, 失败返回0
// 先检查, 再在伪表头后插入变量符号, 传入当前的符号表, id, 和 表达式

bool appendSpeci(SymbolTable table, SymbolNode *node);

bool type_equiv(TypeExpr expr1, TypeExpr expr2); 
//比较类型表达式是否相等.

SymbolTable newTable(SymbolTable old);
// 生成一个伪表头, 接在oldtable后面, 没有旧表就填NULL


SymbolTable pop(SymbolTable tab);


bool exist(SymbolTable tab, char *id);
//这个无需调用, 这已经包含在appendVar, applySpeci中
//只检查局部作用域


SymbolNode* lookup(SymbolTable tab, char *id);
// 查找变量, 查遍整张表. 表可能是全局-局部变量表, 可能是函数表
//使用时记得判断node是否是变量或者结构名

TypeExpr copyExpr(TypeExpr expr);
TypeExpr wrapSpeci(SymbolNode *speci);
//所有表达式的开始, 将一个结构体名或者int 或 float包装成类型表达式
// assert speci is a specifier node pointer

TypeExpr wrapArray(TypeExpr expr, int num);
//assert expr=spec or array

TypeExpr wrapTuple(TypeExpr expr, TypeExpr next); 
//tuple其实就是个链表, 因此expr2要么是元组(链表), 要么是末尾(NULL)
//assert expr1 = spec, assert expr2 = tuple or NULL
TypeExpr catTuple(TypeExpr tuple1, TypeExpr tuple2);
//用于包装结构体的成员.
TypeExpr wrapFunc(TypeExpr param, TypeExpr ret); 
//assert param = tuple or null
//当没有形式参数, param = NULL
TypeExpr wrapStruct(TypeExpr varlist);           //assert deflist = tuple
SymbolTable initSymbols();
//Program调用
bool isInt(TypeExpr);
bool isFloat(TypeExpr);
bool isStruct(TypeExpr);
bool isArray(TypeExpr expr);

#endif