#include"common.h"
#include<stdlib.h>
typedef struct Type_ *Type;
typedef struct FieldList_ *FieldList;
//typedef int(*handle)(SynUnit*);

struct Type_
{
    enum
    {
        BASIC,
        ARRAY,
        STRUCTURE,
        FUNCTION
    } kind;
    union
    {
        int basic;
        struct
        {
            Type elem;
            int size;
        } array;
        FieldList list;//struct or function args
    } u;
    //handle handler;//callback,to process current type messages
};

struct FieldList_
{
    char *name;
    Type type;
    FieldList tail;
};


#define TABLE_LENTH 100

#define mmalloc(type, len) (type*)malloc(len*sizeof(type))

FieldList createDefFields(Type src,SynUnit*unit);//assign src.kind first;unit is the DecList
FieldList createExtDefFields(Type src, SynUnit*unit);////assign src.kind first;unit is the ExtDecList or structSpecifier