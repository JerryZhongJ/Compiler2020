#ifndef __SEMANTIC__
#define __SEMANTIC__


#define MAX_ID_LENGHT 100
#define VAR true
#define SPECI false
#define TypeExpr struct TypeOperator* //被这依赖关系搞烦了
struct TypeOperator;

typedef struct SymbolNode{
    char *name;
    bool var_speci;
    
    TypeExpr type;   //when is var, it represent the type of the variable
                    // when is specifier
    struct SymbolNode* sym_table; //valid when speci

    int width;
    struct SymbolNode *next;
} SymbolNode, *SymbolTable, VarNode, SpecifierNode;
/*
带伪表头
我把变量表和类型表合在一起了, 因为检查时要同时检查变量名和类型名.

我把栈变成了非终结符的属性, 因为对于一个DefList来说, 它并不知道自己在一个StructSpecifier中, 还是一个语句块中.
那我在判断符号是否exist的时候应该用什么为界, 在语句块的话是上一个栈顶, 在struct中是NULL.
因此, 因此我添加了prevStackTop属性, 
CompSt在一开始,CompSt.preStackTop = father.cur_sym_table. 就像内存的%ebp和%esp
StructSpecifier.preStackTop = NULL;
这样无论CompSt中的DefList还是StructSpecifier都可以正确判断符号是否exist.

另外, 在CompSt结束时用pop(preStackTop),

*/
//SymbolNode[0] = "int", SymbolNode[1] = 
// typedef struct SymbolStack{
//     SymbolTable sym_table;
//     struct SymbolStack *upper;
// } SymbolStack;


enum TypeOperator_t
{ //算子类型
    SPECIFIER,
    ARRAY,
    FUNCTION,
    TUPLE,
    _STRUCT,
};
//以下的struct相当于树节点, 算子是一个节点的包装, 表达式是一个树
//为了结构统一, 我使每一个节点指向另一个节点的**包装**

typedef struct TypeArray
{
    TypeExpr expr;       //相当于树的下一个节点
    int size;
} TypeArray;
typedef struct TypeFunc{
    TypeExpr param;       //expected to be a tuple
    TypeExpr ret;        //expected to be specifier
} TypeFunc;
typedef struct TypeTuple{
    TypeExpr speci;      //expected to be a specifier
    TypeExpr tuple;     //expected to be tuple
} TypeTuple;
//Tuple本质上就是类型名的链表
typedef struct TypeStruct{
    TypeExpr tuple; //expected to be a tuple
} TypeStruct;

#undef TypeExpr     //憋删咯

typedef struct TypeOperator
{
    enum TypeOperator_t op_type;
    union Wrapper
    {
        SpecifierNode *speci;
        TypeArray array;
        TypeFunc func;
        TypeTuple tuple;
        TypeStruct _struct; 
    } as;
} TypeOperator, *TypeExpr;             //类型表达式本质上是个树
/*
所有表达式的类型, 符号表中的类型都用TypeExpr来包装, 即便一个变量是int或float型的.
符号表里的是类型名specifier, 是被TypeExpr引用的.
*/

//访问时, 先看op_type, 在根据类型选择相应结构体, 结构体内含有类型表达式(一棵树).
//检查时, 无需要求哪种结构体一定指向哪种结构体(如tuple一定指向tuple的包装), 只需比较op_type和递归检查其子节点, 但构造表达式时要这样构造

SymbolTable global_func; //全局函数表
//错误类型3, 4表明: 函数名和变量名结构体名是分开的.
SymbolTable cur_param; //当前形参表
TypeExpr cur_ret; //当前函数返回值



SymbolNode *delNode(SymbolNode* );
void delExpr(TypeExpr expr); 
//在delNode中被调用, 在statement结束后被调用.
//Expr有两种归宿, 一是在声明变量时被存进了符号表, 而是作为表达式的类型, 表达式结束它的生命就该结束.


bool appendVar(SymbolTable table, SymbolNode *stop, char *name, TypeExpr expr);
// 先检查, 再在伪表头后插入变量符号, 传入当前的符号表的**指针**(&cur_sym_table), id, 和 表达式
// 在函数表, 当前形参表插入用这个.

bool applySpeci(SymbolTable table, SymbolNode *stop, char *name, SpecifierNode **speci); //返回一个新的符号表
// 在考虑到具体的语法树, 这里只需在OptTag处填上名字(可以是空串). 后面再填上符号表和类型表达式
//会先检查是否同名
//最后是传入(&specifier), 作为返回值来返回.

void fillSpeci(SpecifierNode *node, TypeExpr expr, TypeExpr field);

bool type_equiv(TypeExpr expr1, TypeExpr expr2); 
//比较类型表达式是否相等, 注意:对于int float 或者结构体名, 也要包装成表达式.

SymbolTable *newTable(SymbolTable *old);
// 生成一个伪表头, 接在oldtable后面, 没有旧表就填NULL
//有了伪表头, cur_sym_table在父子节点之间能保持一致, 否则子节点添加了表项, 父节点停留在原地.

void pop(SymbolTable *stop);

bool exist(SymbolTable tab, SymbolNode* stop);
//这个无需调用, 这已经包含在appendVar, applySpeci中
//是否存在同名的变量或者结构名, 或函数名.


bool lookup(SymbolTable tab, char *id,  SymbolNode **node_ptr);
// 查找变量, 查遍整张表. 表可能是全局-局部变量表, 可能是结构体的符号表
//通过node_ptr返回对表项的指针. 如SymbolNode *node; lookup(..., &node);
//使用时记得判断node是否是变量或者结构名

TypeExpr wrapSpeci(SpecifierNode *speci); 
//所有表达式的开始, 将一个结构体名或者int 或 float包装成类型表达式
// assert speci is a specifier node pointer

TypeExpr wrapArray(TypeExpr expr, int size);
//assert expr=spec or array

TypeExpr wrapTuple(TypeExpr expr1, TypeExpr expr2); 
//tuple其实就是个链表, 因此expr2要么是元组(链表), 要么是末尾(NULL)
//assert expr1 = spec, assert expr2 = tuple or NULL
TypeExpr catTuple(TypeExpr tuple1, TypeExpr tuple2);
//用于包装结构体的成员.
TypeExpr wrapFunc(TypeExpr param, TypeExpr ret); //assert param = tuple
TypeExpr wrapStruct(TypeExpr deflist);           //assert deflist = tuple

bool isInt(char *id);
bool isSpeci(char *id);
bool isStruct(char *id);
bool isArray(char *id);

//看TODO.md
#endif