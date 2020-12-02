
#include"common.h"
#include<stdio.h>
#include"Node.h"
#define OFFSET 260
extern int yynerrs;
extern void yyrestart(FILE *);
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
	"VarDec",
	"FucDec",
	"VarList",					// i dont like the name "VarList", kind of misleading.
	"ParamDec",
	"CompSt",
	"StmtList",
	"Stmt",
	"DefList",
	"Def",
	"DecList",
	"Dec",
	"Exp",
	"Args"};
SynUnit *start;
void display(SynUnit *unit, int level)
{
	//printf("%d\n", unit->symbol_num);
	if (unit == NULL)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("%s (%d)\n", syn_t_name[unit->syn_type], unit->lineno);
	for (int i = 0; i < unit->symbol_num;i++){
		if(unit->symbol_type[i] == SYN){
			display(unit->symbol[i].syn_child, level + 1);
		}else if(unit->symbol_type[i] == LEX){
			LexUnit *token = unit->symbol[i].lex_child;
			for (int i2 = 0; i2 < level + 1; i2++)
				printf("  ");
			printf("%s", lex_t_name[token->lex_type - OFFSET]);
			switch (token->lex_type)
			{
			case INT:
				printf(": %d\n", token->ival);
				break;
			case FLOAT:
				printf(": %f\n", token->fval);
				break;
			case ID:
				printf(": %s\n", token->id);
				break;
			case TYPE:
				printf(": %s\n", token->iorf == TYPE_INT ? "int" : "float");
				break;
			default:
				printf("\n");
			}
		}
	}
}
int main(int argc, char** argv){
	if(argc <= 1) return 1;
	FILE *input = fopen(argv[1], "r");
	//FILE *output = fopen(argv[1], "r");
	if (!input)
	{
		perror(argv[1]);
		return 1;
	}
	yyrestart(input);
	yyparse();
	if(yynerrs == 0){
		MakeObj(program, n0, emptyPPT);
		n0.creator(&n0, start);
		//display(start, 0);
	}

		return 0;
}