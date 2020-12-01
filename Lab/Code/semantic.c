#include"semantic.h"
#include<string.h>
#include<assert.h>
#include<stdio.h>
//悬空指针! 最好不要让两个指针共享同一个空间!!!!
static bool isBasicSpeci(SpecifierNode *speci){
    return speci == speci_int || speci == speci_float;
}
static void printTable(SymbolTable tab){
    for (SymbolNode *node = tab; node != NULL;node = node->next){
        if(node->symbol_type == NODE_FAKE)
            printf("----\n");
        else{
            printf("%s %s\n", node->name, node->symbol_type == NODE_VAR?(isInt(node->type)?"INT":(isFloat(node->type)?"FLOAT":(isArray(node->type)?"ARRAY":"STRUCT"))):"SPECIFIER");
        }
            
    }
    printf("\n\n");
}
// static int countSize(TypeExpr expr){
//     if(expr == NULL){
//         return 0;
//     }
//     switch (expr->op_type){
//         case SPECIFIER:
//             return expr->speci->width;
//         case ARRAY:
//             return expr->array.num * expr->array.element_width;
//         case FUNCTION:
//             return 0;
//         case TUPLE:
//             return countSize(expr->tuple.expr) + countSize(expr->tuple.next);
//         case _STRUCT:
//             return expr->_struct.width;
//         }
// }
SymbolNode *delNode(SymbolNode *node){
    //释放成员的空间, 最后释放此节点的空间
    if(node == NULL)
        return NULL;
    //printf("del %s\n", node->name);
    free(node->name);    //malloc when syntax analysis
    delExpr(node->type); //在插入符号表时已经对TypeExpr进行拷贝.
    if(node->sym_table != NULL)
        pop(node->sym_table);
    SymbolNode *next = node->next;
    free(node);
    return next;
}
TypeExpr copyExpr(TypeExpr expr){
    if(expr == NULL)
        return NULL;
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = expr->op_type;
    tmp->width = expr->width;
    switch (expr->op_type) {
        case SPECIFIER:
            tmp->speci = expr->speci;
            break;
        case ARRAY:
            tmp->array.expr = copyExpr(expr->array.expr);
            tmp->array.num = expr->array.num;
            break;
        case FUNCTION:
            tmp->func.param = copyExpr(expr->func.param);
            tmp->func.ret = copyExpr(expr->func.ret);
            break;
        case TUPLE:
            tmp->tuple.expr = copyExpr(expr->tuple.expr);
            tmp->tuple.next = copyExpr(expr->tuple.next);
            break;
        case _STRUCT:
            tmp->_struct.varlist = copyExpr(expr->_struct.varlist);
            break;
    }
    return tmp;
}
void delExpr(TypeExpr expr){
    if(expr == NULL)
        return;
    switch (expr->op_type){
    case SPECIFIER:
        break;
    case ARRAY:
        delExpr(expr->array.expr);
        break;
    case FUNCTION:
        delExpr(expr->func.param);
        delExpr(expr->func.ret);
        break;
    case TUPLE:
        delExpr(expr->tuple.expr);
        delExpr(expr->tuple.next);
        break;
    case _STRUCT:
        delExpr(expr->_struct.varlist);
        break;
    }
    free(expr);
}
bool appendVar(SymbolTable table, char *name, TypeExpr expr){
    //table point at fake node
    assert(table != NULL);
    assert(name != NULL);
    assert(expr != NULL);
    if (exist(table, name))
        return false;
    
    SymbolNode *node = (SymbolNode *)malloc(sizeof(SymbolNode));
    node->name = (char *)malloc(strlen(name) + 1);
    strcpy(node->name, name);
    node->type = copyExpr(expr);
    node->symbol_type = NODE_VAR;
    node->sym_table = NULL;
    node->width = expr->width;
    node->offset = table->next->offset + table->next->width;
    node->next = table->next;
    table->next = node;
    //printf("appending %s\n", name);
    //printTable(table);
    return 1;
}

bool appendFunc(SymbolTable tab, char *name, TypeExpr expr){
    appendVar(tab, name, expr);
    tab->next->symbol_type = NODE_FUNC;
}
bool appendSpeci(SymbolTable tab, SpecifierNode *node){
    assert(tab != NULL && node != NULL);
    
    if (exist(tab, node->name))
        return 0;
    node->symbol_type = NODE_SPECI;
    //node->width = countSize(node->type);
    node->width = 0;
    node->offset = tab->next->offset;
    node->next = tab->next;
    tab->next = node;
    return 1;
}
bool type_equiv(TypeExpr expr1, TypeExpr expr2){
    if(expr1 == NULL || expr2 == NULL){
        if(expr1 == NULL && expr2 == NULL)
            return true;
        else
            return false;
    }
    if (expr1->op_type == SPECIFIER)
    {                                        //if expr1 is specifier
        if(isBasicSpeci(expr1->speci)){      //if expr1 is basic specifier
            if(expr2->op_type == SPECIFIER && expr2->speci == expr1->speci)
                return true;                    // true only when expr2 is the same basic specifier
            else
                return false;
        }else{
            TypeExpr realexpr = expr1->speci->type;
            return type_equiv(realexpr, expr2);
        }
    }
    else if (expr2->op_type == SPECIFIER)
    {
        if(isBasicSpeci(expr2->speci))
            return false; //as expr1 definitely not basic.
        else{
            TypeExpr realexpr = expr2->speci->type;
            return type_equiv(expr1, realexpr);
        }
    }

    if(expr1->op_type != expr2->op_type)
        return false;

    switch(expr1->op_type){
        case ARRAY:
            return type_equiv(expr1->array.expr, expr2->array.expr);
            break;
        case FUNCTION:
            return type_equiv(expr1->func.param, expr2->func.param) && type_equiv(expr1->func.ret, expr2->func.ret);
        case TUPLE:
             return type_equiv(expr1->tuple.expr, expr2->tuple.expr) && type_equiv(expr1->tuple.next, expr2->tuple.next);
        case _STRUCT:
            return type_equiv(expr1->_struct.varlist, expr2->_struct.varlist);
        default:
            assert(0);
        }
}

SymbolTable newTable(SymbolTable old){
    
    SymbolNode *node = (SymbolNode *)malloc(sizeof(SymbolNode));
    node->name = (char*)malloc(1);      //cannot be const string
    node->name[0] = 0;
    node->symbol_type = NODE_FAKE;
    node->type = NULL;
    node->sym_table = NULL;
    node->width = 0;
    node->offset = 0;
    node->next = old;
    return node;
}
SymbolTable pop(SymbolTable tab){
    for (; tab->next != NULL && tab->next->symbol_type != NODE_FAKE;){
        tab->next = delNode(tab->next);
    }
    //printf("after poping.\n");
    //printTable(tab);
    return delNode(tab);
    
}
bool exist(SymbolTable tab, char *id){
    assert(id != NULL);
    assert(tab != NULL);
    for (SymbolNode *node = tab->next; node != NULL && node->symbol_type != NODE_FAKE;node = node->next) { //fake node
        if(strcmp(id, node->name) == 0)
            return true;
    }
    return false;
}
SymbolNode *lookup(SymbolTable tab, char *id){
    assert(id != NULL);
    assert(tab != NULL);
    for (SymbolNode *node = tab->next; node != NULL;node = node->next) { //fake node
        if(strcmp(id, node->name) == 0)
            return node;
    }
    return NULL;
}
TypeExpr wrapSpeci(SpecifierNode *speci){
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = SPECIFIER;
    tmp->speci = speci;
    if(speci == speci_int || speci_float){
        tmp->width = 4;
    }else{
        tmp->width = speci->type->width;
    }
    return tmp;
}
TypeExpr wrapTuple(TypeExpr expr, TypeExpr next){
    assert(expr->op_type == SPECIFIER || expr->op_type == ARRAY);
    assert(next == NULL || next->op_type == TUPLE);
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = TUPLE;
    tmp->tuple.expr = copyExpr(expr);
    tmp->tuple.next = copyExpr(next);
    tmp->width = expr->width + next->width;
    return tmp;
}
TypeExpr wrapArray(TypeExpr expr, int num){
    assert(expr->op_type == SPECIFIER || expr->op_type == ARRAY);
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = ARRAY;
    tmp->array.expr = copyExpr(expr);
    tmp->array.num = num;
    tmp->array.element_width = expr->width;
    tmp->width = num * expr->width;
    return tmp;
}
TypeExpr wrapFunc(TypeExpr param, TypeExpr ret){
    assert(param == NULL || param->op_type == TUPLE);
    assert(ret->op_type == SPECIFIER );
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = FUNCTION;
    tmp->func.param = copyExpr(param);
    tmp->func.ret = copyExpr(ret);
    tmp->width = 0;
    return tmp;
}
TypeExpr wrapStruct(TypeExpr varlist){
    assert(varlist->op_type == TUPLE);
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = _STRUCT;
    tmp->_struct.varlist = copyExpr(varlist);
    tmp->width = varlist->width;
    return tmp;
}

SymbolTable initSymbols(){
    assert(0);
    symbols = newTable(NULL);

    speci_int = (SymbolNode *)malloc(sizeof(SymbolNode));
    speci_int->name = (char*)malloc(4);
    strcpy(speci_int->name, "int");
    speci_int->symbol_type = NODE_SPECI;
    speci_int->type = NULL;
    speci_int->sym_table = NULL;
    speci_int->width = 0;
    speci_int->next = symbols->next;
    symbols->next = speci_int;

    speci_float = (SymbolNode *)malloc(sizeof(SymbolNode));
    speci_float->name = (char*)malloc(6);
    strcpy(speci_float->name, "float");
    speci_float->symbol_type = NODE_SPECI;
    speci_float->type = NULL;
    speci_float->sym_table = NULL;
    speci_float->width = 0;
    speci_float->next = symbols->next;
    symbols->next = speci_float;

    TypeExpr wrap_int = wrapSpeci(speci_int);
    TypeExpr read = wrapFunc(NULL, wrap_int);
    TypeExpr write = wrapFunc(wrap_int, wrap_int);

    func_read = (SymbolNode *)malloc(sizeof(SymbolNode));
    func_read->name = (char*)malloc(5);
    strcpy(func_read->name, "read");
    func_read->symbol_type = NODE_FUNC;
    func_read->type = read;
    func_read->sym_table = NULL;
    func_read->width = 0;
    func_read->next = symbols->next;
    symbols->next = func_read;

    func_write = (SymbolNode *)malloc(sizeof(SymbolNode));
    func_write->name = (char*)malloc(6);
    strcpy(func_write->name, "write");
    func_write->symbol_type = NODE_FUNC;
    func_write->type = write;
    func_write->sym_table = NULL;
    func_write->width = 0;
    func_write->next = symbols->next;
    symbols->next = func_write;

    delExpr(wrap_int);
    delExpr(read);
    delExpr(write);
    return symbols;
}

bool isInt(TypeExpr expr){
    if (expr == NULL)
        return 0;
    if(expr->op_type != SPECIFIER)
        return 0;
    return expr->speci == speci_int;
}

bool isFloat(TypeExpr expr){
    if(expr == NULL)
        return 0;
    if(expr->op_type != SPECIFIER)
        return 0;
    return expr->speci == speci_float;
}
bool isStruct(TypeExpr expr){
    if(expr == NULL)
        return 0;
    if(expr->op_type != SPECIFIER)
        return 0;
    return expr->speci != speci_int && expr->speci != speci_float;
}

bool isArray(TypeExpr expr){
    if(expr == NULL)
        return 0;
    return expr->op_type == ARRAY;
}
TypeExpr catTuple(TypeExpr tuple1, TypeExpr tuple2){
    assert(tuple1 != NULL);
    if(tuple2 == NULL)
        return copyExpr(tuple1);
    assert(tuple1->op_type == TUPLE && tuple2->op_type == TUPLE);
    TypeExpr tmp1 = copyExpr(tuple1);
    TypeExpr tmp2 = copyExpr(tuple2);
    TypeExpr p = tmp1;
    for (; p->tuple.next != NULL;p = p->tuple.next)
        assert(p->tuple.next->op_type == TUPLE);
    p->tuple.next = tmp2;
    return tmp1;
}