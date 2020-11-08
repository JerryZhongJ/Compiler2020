#include "common.h"
#include "treeAnalyze.h"

FieldList tables[TABLE_LENTH];
int top = 0;

void treeAnalyze(SynUnit *unit)
{
    if (unit == NULL)
    {
        return;
    }
    if (unit->syn_type == Def) //Def->Specifier DecList SEMI
    {
        SynUnit *specifier = unit->symbol[0].child;
        SynUnit *decList = unit->symbol[1].child;
        FieldList cur = tables[top];
        while (cur->tail != NULL)
        {
            cur = cur->tail;
        }
        Type type = mmalloc(struct Type_, 1);
        type->kind = BASIC;
        cur->tail = createDefFields(type, decList);
    }
    else if (unit->syn_type == ExtDef)
    {
        SynUnit *specifier = unit->symbol[0].child;
        Type type = mmalloc(struct Type_, 1);
        FieldList cur = tables[top];
        while (cur->tail != NULL)
        {
            cur = cur->tail;
        }
        if (unit->symbol_type[1] == LEX) //ExtDef->Specifier SEMI
        {
            if (specifier->symbol_type[0] == LEX)
            {
                free(type);
                return;
            }
            else
            {
                type->kind = STRUCT;
                cur->tail = createExtDefFields(type,unit);
            }
        }
        else if(unit->symbol_type[2] == LEX)
        {
            
        }
    }
    else if (unit->syn_type == Exp)
    {
    }
    else
    {
        for (int i = 0; i < unit->symbol_num; ++i)
        {
            treeAnalyze(unit->symbol[i].child);
        }
    }
}