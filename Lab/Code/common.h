#ifndef COMMON
#define COMMON
#include<stdbool.h>
#include"syntax.tab.h"
#define SYN false
#define LEX true
#define TYPE_INT false
#define TYPE_FLOAT true
/*typedef enum 
{
	INT,
	FLOAT,
	ID,
	SEMI,
	COMMA,
	ASSIGNOP,
	RELOP,
	PLUS,
	MUNUS,
	STAR,
	DIV,
	AND,
	OR,
	DOT,
	NOT,
	TYPE,
	LP,
	RP,
	LB,
	RB,
	LC,
	RC,
	STRUCT,
	RETURN,
	IF,
	ELSE,
	WHILE,
	FOR
} LexType;*/
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
	FucDec,
	ParamList,
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

typedef struct {							//three elements: type, prod, lineo
		SynType syn_type;
		int prod_num;					// should be <= 5
		bool prod_type[5];				// 0 for syn, 1 for lex
		union{								//prod can be SymUnit or LexUnit
			SynUnit* child;
			struct{							//if prod is LexUnit, it has two elements: lex_type and another attribute, depends on what type it is.
				LexType lex_type;
				union{
					int ival;
					float fval;
					char* id;
					bool iorf;		// 0 for int, 1 for float
				};
			};
		} prod[5];
		int lineno;
} SynUnit;

extern SynUnit *start;

#endif
