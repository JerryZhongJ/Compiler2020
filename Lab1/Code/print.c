#include"common.h"

char lex_t_name[][10] = {
	"INT",
	"FLOAT",
	"ID",
	"SEMI",
	"COMMA",
	"ASSIGNOP",
	"RELOP",
	"PLUS",
	"MINUS",
	"STAR",
	"DIV",
	"AND",
	"OR",
	"DOT",
	"NOT",
	"TYPE",
	"LP",
	"RP",
	"LB",
	"RB",
	"LC",
	"RC",
	"STRUCT",
	"RETURN",
	"IF",
	"ELSE",
	"WHILE",
	"FOR"};

char syn_t_name[][20] = {
	"Program",
	"ExtDefList",
	"ExtDef",
	"ExtDecList",
	"Specifier",
	"StructSpecifier",
	"OptTag",
	"Tag",
	"FucDec",
	"VarDec",
	"VarList", // i dont like the name "VarList", kind of misleading.
	"ParamDec",
	"CompSt",
	"StmtList",
	"Stmt",
	"DefList"
	"Def",
	"DecList",
	"Dec",
	"Exp",
	"Args"};

SynUnit *start;
char buffer [ERROR_BUFFER_SIZE];
int errorNum = 0;
int errorOutput;
void display(SynUnit *unit, int level)
{
	if (unit == NULL)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("%s (%d)\n", syn_t_name[unit->syn_type], unit->lineno);
	for (int i = 0; i < unit->symbol_num; i++)
	{
		if (unit->symbol_type[i] == SYN)
		{
			display(unit->symbol[i].child, level + 1);
		}
		else if (unit->symbol_type[i] == LEX)
		{
			for (int i2 = 0; i2 < level + 1; i2++)
			{
				printf("  ");
			}
			printf("%s", lex_t_name[unit->symbol[i].lex_type]);
			switch (unit->symbol[i].lex_type)
			{
			case INT:
				printf(": %d\n", unit->symbol[i].ival);
				break;
			case FLOAT:
				printf(": %f\n", unit->symbol[i].fval);
				break;
			case ID:
				printf(": %s\n", unit->symbol[i].id);
				break;
			case TYPE:
				printf(": %s\n", unit->symbol[i].iorf == TYPE_INT ? "int" : "float");
				break;
			default:
				printf("\n");
			}
		}
	}
}
char* errorf(ErrorType ety,int lineno,const char* msg)
{
    errorNum++;
    errorOutput = 1;
    const char* etyStr = (ety == SYN_ERROR?"syntax error":"token error");
    snprintf(buffer,ERROR_BUFFER_SIZE,"Error type %s at Line %d: %s",etyStr,lineno,msg);
    return buffer;
}