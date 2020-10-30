#ifndef COMMON
#define COMMON
#include<stdbool.h>
#include"syntax.tab.h"
#define NULL 0
#define SYN false
#define LEX true
#define TYPE_INT false
#define TYPE_FLOAT true
#define MAX_SYMBOL_NUM 7
#include "semantic.h"
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
typedef struct LexUnit{							
	LexType lex_type;
	union{
		int ival;
		float fval;
		char* id;
		bool iorf;		// 0 for int, 1 for float
	};
} LexUnit;
typedef struct SynUnit{							//three elements: type, symbol, lineo
		SynType syn_type;
		int symbol_num;					// should be <= MAX_SYMBOL_NUM
		struct {
			SymbolTable cur_sym_table;
			TypeExpr type_syn;
			TypeExpr type_inh;
			bool isLvalue;
			SymbolTable prevStackTop;
			SpecifierNode *speci;
		};
		bool symbol_type[MAX_SYMBOL_NUM];	// 0 for syn, 1 for lex
		union{								//symbols in one production can be SymUnit or LexUnit
			struct SynUnit* syn_child;
			struct LexUnit *lex_child;
		} symbol[MAX_SYMBOL_NUM]; // symbols in one production
		int lineno;
} SynUnit;

extern SynUnit *start;

#endif
