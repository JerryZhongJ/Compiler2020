#include"common.h"

typedef Type_ *Type;
typedef FieldList_ *FieldList;
typedef FieldList_ Table;
typedef int(*handle)(SynUnit*);

typedef struct
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
    handle handler;//callback,to process current type messages
} Type_;

typedef struct
{
    char *name;
    Type type;
    FieldList tail;
} FieldList_;


