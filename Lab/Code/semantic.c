#include"semantic.h"
#include<string.h>
#include<assert.h>

//内存泄漏! 最好不要让两个指针共享同一个空间!!!!
static bool isBasicSpeci(SpecifierNode *speci){
    return speci == speci_int || speci == speci_float;
}
static int countSize(TypeExpr expr){
    if(expr == NULL){
        return 0;
    }
    switch (expr->op_type){
        case SPECIFIER:
            return expr->speci->width;
        case ARRAY:
            return countSize(expr->array.expr) * expr->array.num;
        case FUNCTION:
            return 0;
        case TUPLE:
            return countSize(expr->tuple.speci) + countSize(expr->tuple.next);
        case _STRUCT:
            return countSize(expr->_struct.varlist);
        }
}
SymbolNode *delNode(SymbolNode *node){
    //释放成员的空间, 最后释放此节点的空间
    if(node == NULL)
        return NULL;
    free(node->name); //malloc when syntax analysis
    delExpr(node->type); //在插入符号表时已经对TypeExpr进行拷贝.
    if(node->sym_table != NULL)
        pop(node->sym_table, NULL);
    SymbolNode *next = node->next;
    free(node);
    return next;
}
TypeExpr copyExpr(TypeExpr expr){
    if(expr == NULL)
        return NULL;
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = expr->op_type;
    switch (expr->op_type){
    case SPECIFIER:
        tmp->speci = expr->speci;
    case ARRAY:
        tmp->array.expr = copyExpr(expr->array.expr);
        tmp->array.num = expr->array.num;
        break;
    case FUNCTION:
        tmp->func.param = copyExpr(expr->func.param);
        tmp->func.ret = copyExpr(expr->func.ret);
        break;
    case TUPLE:
        tmp->tuple.speci = copyExpr(expr->tuple.speci);
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
        delExpr(expr->tuple.speci);
        delExpr(expr->tuple.next);
        break;
    case _STRUCT:
        delExpr(expr->_struct.varlist);
        break;
    }
    free(expr);
}
bool appendVar(SymbolTable table, SymbolNode *stop, char *name, TypeExpr expr){
    //table point at fake node
    assert(table != NULL);
    assert(name != NULL);
    assert(expr != NULL);
    if (exist(table, name, stop))
        return false;
    
    SymbolNode *node = (SymbolNode *)malloc(sizeof(SymbolNode));
    node->name = (char *)malloc(strlen(name) + 1);
    strcpy(node->name, name);
    node->type = copyExpr(expr);
    node->var_speci = VAR;
    node->sym_table = NULL;
    node->width = countSize(expr);
    node->next = table->next;
    table->next = node;
    return 1;
}
SpecifierNode *applySpeci(SymbolTable table, SymbolNode *stop, char *name){
    assert(name != NULL);
    if(name[0] != 0&&exist(table, name, stop)){
        return NULL;
    } //allow name to be 0

    SymbolNode *node = (SymbolNode *)malloc(sizeof(SymbolNode));
    node->name = (char *)malloc(strlen(name) + 1);
    strcpy(node->name, name);
    node->var_speci = SPECI;
    node->next = table->next;
    table->next = node;
    
    return node;
}
void fillSpeci(SpecifierNode *node, TypeExpr expr, SymbolTable field){
    if(node == NULL)
        return;
    assert(expr != NULL);
    assert(field != NULL);
    assert(node->var_speci == SPECI);
    node->type = copyExpr(expr);
    node->width = countSize(expr);
    node->sym_table = field; //maybe dangerous
}
bool type_equiv(TypeExpr expr1, TypeExpr expr2){
    if(expr1 == NULL || expr2 == NULL){
        if(expr1 == NULL && expr2 == NULL)
            return true;
        else
            return false;
    }
    if(expr1->op_type == SPECIFIER){ //if expr1 is specifier
        if(isBasicSpeci(expr1->speci)){      //if expr1 is basic specifier
            if(expr2->op_type == SPECIFIER && expr2->speci == expr1->speci)
                return true;                    // true only when expr2 is the same basic specifier
            else
                return false;
        }else{
            TypeExpr realexpr = expr1->speci->type;
            return type_equiv(realexpr, expr2);
        }
    }else if(expr2->op_type == SPECIFIER){
        if(isBasicSpeci(expr2->speci))
            return false; //as expr1 definitely not basic.
        else{
            TypeExpr realexpr = expr1->speci->type;
            return type_equiv(realexpr, expr2);
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
             return type_equiv(expr1->tuple.speci, expr2->tuple.speci) && type_equiv(expr1->tuple.next, expr2->tuple.next);
        case _STRUCT:
            return type_equiv(expr1->_struct.varlist, expr2->_struct.varlist);
        default:
            assert(0);
        }
}

SymbolTable newTable(SymbolTable old){
    SymbolNode *node = (SymbolNode *)malloc(sizeof(SymbolNode));
    node->name = (char*)malloc(1);
    node->name[0] = 0;
    node->var_speci = VAR;
    node->type = NULL;
    node->sym_table = NULL;
    node->width = 0;
    node->next = old;
    return node;
}
void pop(SymbolTable tab, SymbolNode *stop){
    for (SymbolNode *node = tab->next; node != stop;){
        node = delNode(node);
    }
    delNode(tab);
}
bool exist(SymbolTable tab, char *id, SymbolNode *stop){
    assert(id != NULL);
    assert(tab != NULL);
    for (SymbolNode *node = tab->next; node != stop;node = node->next) { //fake node
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
    return tmp;
}
TypeExpr wrapTuple(TypeExpr expr1, TypeExpr expr2){
    assert(expr1->op_type == SPECIFIER);
    assert(expr2 == NULL || expr2->op_type == TUPLE);
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = TUPLE;
    tmp->tuple.speci = copyExpr(expr1);
    tmp->tuple.next = copyExpr(expr2);
    return tmp;
}
TypeExpr wrapArray(TypeExpr expr, int num){
    assert(expr->op_type == SPECIFIER || expr->op_type == ARRAY);
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = ARRAY;
    tmp->array.expr = copyExpr(expr);
    tmp->array.num = num;
    return tmp;
}
TypeExpr wrapFunc(TypeExpr param, TypeExpr ret){
    assert(param == NULL || param->op_type == TUPLE);
    assert(ret->op_type == SPECIFIER);
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = FUNCTION;
    tmp->func.param = copyExpr(param);
    tmp->func.ret = copyExpr(ret);
    return tmp;
}
TypeExpr wrapStruct(TypeExpr varlist){
    assert(varlist->op_type == TUPLE);
    TypeExpr tmp = (TypeExpr)malloc(sizeof(TypeOperator));
    tmp->op_type = _STRUCT;
    tmp->_struct.varlist = copyExpr(varlist);
    
}