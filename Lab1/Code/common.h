#ifndef COMMON
#define COMMON
#include<stdbool.h>
#include"syntax.tab.h"
#include <stdio.h>
#include<string.h>

#define SYN false
#define LEX true
#define TYPE_INT false
#define TYPE_FLOAT true
#define MAX_SYMBOL_NUM 7

#define TOKEN_ERROR 1
#define SYN_ERROR 2
#define STR_TOKEN_ERROR "A"
#define STR_SYN_ERROR "B"
#define ERROR_BUFFER_SIZE 256

typedef enum yytokentype LexType;
typedef enum 
{
	Program,
	ExtDefList,
	ExtDef,
	ExtDecList,
	Specifier,
	StructSpecifier,
	OptTag,
	Tag,
	VarDec,
	FunDec,
	ParamList,					// i dont like the name "VarList", so i change it to "ParamList", but will be printed "VarList" at last.
	ParamDec,
	CompSt,
	StmtList,
	Stmt,
	DefList,
	Def,
	DecList,
	Dec,
	Exp,
	Args
} SynType;

typedef struct SynUnit{							//three elements: type, symbol, lineo
		SynType syn_type;
		int symbol_num;					// should be <= MAX_SYMBOL_NUM
		bool symbol_type[MAX_SYMBOL_NUM];				// 0 for syn, 1 for lex
		union{								//symbols in one production can be SymUnit or LexUnit
			struct SynUnit* child;
			struct{							
				LexType lex_type;
				union{
					int ival;
					float fval;
					char* id;
					bool iorf;		// 0 for int, 1 for float
				};
			};
		} symbol[MAX_SYMBOL_NUM];				// symbols in one production
		int lineno;
} SynUnit;

typedef int ErrorType;
extern SynUnit *start;
extern int errorNum;
extern int errorOutput;
extern int lineErrorNum;
extern char* bufferPtr;

void display(SynUnit *unit, int level);
char* errorf(ErrorType ety,int lineno,const char* msg);
#endif
