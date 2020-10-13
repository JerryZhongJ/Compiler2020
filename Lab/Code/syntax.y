%{
	#include"SynUnit.c"	
	#include<stdlib.h>
	#include<assert.h>
	
%}
%code requires{
	#include"common.h"
}
%union {
	int type_int;
	float type_float;
	char *type_str;
	bool type_bool;
	SynUnit* type_syn;
}
%token <type_int> INT
%token <type_float> FLOAT
%token <type_str> ID
%token <type_bool> TYPE
%token SEMI COMMA LC RC STRUCT RETURN IF ELSE WHILE
%type <type_syn> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec FunDec ParamList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args 
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right UMINUS NOT
%left LP RP LB RB DOT

%%
/*High level*/
Program : ExtDefList {
		$$ = init(Program);
		appendSyn($$, $1);
}
	;

ExtDefList : ExtDef ExtDefList {
		$$ = init(ExtDef);
		appendSyn($$, $1);
		appendSyn($$, $2);
	}
	| {$$ = NULL;}
	;

ExtDef : Specifier ExtDecList SEMI {
		$$ = init(ExtDef);
		appendSyn($$, $1);
		appendSyn($$, $2);
		appendLex($$, SEMI);
	}
	| Specifier SEMI {
		$$ = init(ExtDef);
		appendSyn($$, $1);
		appendLex($$, SEMI);
	}
	| Specifier FunDec CompSt {
		$$ = init(ExtDef);
		appendSyn($$, $1);
		appendSyn($$, $2);
	}
	;
ExtDecList : VarDec {
		$$ = init(ExtDecList);
		appendSyn($$, $1);
	}
	| VarDec COMMA ExtDecList {
		$$ = init(ExtDecList);
		appendSyn($$, $1);
		appendLex($$, COMMA);
		appendSyn($$, $3);
	}
	;

/* Specifiers*/
Specifier : TYPE {
		$$ = init(Specifier);
		appendLexType($$, TYPE, $1);
	}
	| StructSpecifier {
		$$ = init(Specifier);
		appendSyn($$, $1);
	}
	;
StructSpecifier : STRUCT OptTag LC DefList RC {
		$$ = init(StructSpecifier);
		appendLex($$, STRUCT);
		appendSyn($$, $2);
		appendLex($$, LC);
		appendSyn($$, $4);
		appendLex($$, RC);
}
	| STRUCT Tag {
		$$ = init(StructSpecifier);
		appendLex($$, STRUCT);
		appendSyn($$, $2);
	}
	;
OptTag : ID {
		$$ = init(OptTag);
		appendLex($$, ID, $1);
	}
	| {$$ = NULL;}
	;
Tag : ID {
		$$ = init(Tag);
		appendLexID($$, ID, $1);
	}
	;

/* Declarators*/
VarDec : ID {
		$$ = init(VarDec);
		appendLexID($$, ID, $1);
	}
	| VarDec LB INT RB {
		$$ = init(VarDec);
		appendSyn($$, $1);
		appendLex($$, LB);
		appendSyn($$, $3);
		appendLex($$, RB);
	}
	;
FunDec : ID LP ParamList RP {
		$$ = init(FunDec);
		appendLexID($$, ID, $1);
		appendLex($$, LP);
		appendSyn($$, $3);
		appendLex($$, RP);
	}
	| ID LP RP {
		$$ = init(FunDec);
		appendLexID($$, ID, $1);
		appendLex($$, LP);
		appendLex($$, RP);
	}
	;
ParamList : ParamDec COMMA ParamList {
		$$ = init(ParamList);
		appendSyn($$, $1);
		appendLex($$, COMMA);
		appendSyn($$, $3);
	}
	| ParamDec {
		$$ = init(ParamList);
		appendSyn($$, $1);
	}
	;
ParamDec : Specifier VarDec {
		$$ = init(ParamDec);
		appendSyn($$, $1);
		appendSyn($$, $2);
	}
	;

CompSt : LC DefList StmtList RC {
		$$ = init(CompSt);
		appendLex($$, LC);
		appendSyn($$, $2);
		appendSyn($$, $3);
		appendLex($$, RC);
	}
	;
StmtList : Stmt StmtList {
		$$ = init(StmtList);
		appendSyn($$, $1);
		appendSyn($$, $2);
	}
	| {$$ = NULL;}
	;
Stmt : Exp SEMI {
		$$ = init(Stmt);
		appendSyn($$, $1);
		appendLex($$, SEMI);
	}
	| CompSt {
		$$ = init(Stmt);
		appendSyn($$, $1);
	}
	| RETURN Exp SEMI {
		$$ = init(Stmt);
		appendLex($$, RETURN);
		appendSyn($$, $2);
		appendLex($$, SEMI);
	}
	| IF LP Exp RP Stmt {
		$$ = init(Stmt);
		appendLex($$, IF);
		appendLex($$, LP);
		appendSyn($$, $3);
		appendLex($$, RP);
		appendSyn($$, $5);
	}
	| IF LP Exp RP Stmt {
		$$ = append(Stmt);
		appendLex($$, IF);
		appendLex($$, LP);
		appendSyn($$, $3);
		appendLex($$, RP);
		appendSyn($$, $5);
	}
	;

/* Local Definitions*/
DefList : Def DefList {
		$$ = init(DefList);
		appendSyn($$, $1);
		appendSyn($$, $2);
	}
	|
	;
Def : Specifier DecList SEMI {
		$$ = init(Def);
		appendSyn($$, $1);
		appendSyn($$, $2);
		appendLex($$, SEMI);
	}
	;
DecList : Dec {
		$$ = init(DecList);
		appendSyn($$, $1);
	}	
	| Dec COMMA DecList {
		$$ = init(DecList);
		appendSyn($$, $1);
		appendLex($$, COMMA);
		appendSyn($$, $3);
	}
	;
Dec : VarDec {
		$$ = init(Dec);
		appendSyn($$, $1);
	}
	| VarDec ASSIGNOP Exp{
		$$ = init(Dec);
		appendSyn($$, $1);
		appendLex($$, ASSIGNOP);
		appendSyn($$, $3);
	}
	;

/* Expressions */
Exp : Exp ASSIGNOP Exp {
		$$ = init(Exp);
		appendSyn($$, $1);
		appendLex($$, ASSIGNOP);
		appendSyn($$, $3);
	}
	| Exp AND Exp {
		$$ = init(Exp);
		appendSyn($$, $1);
		appendLex($$, AND);
		appendSyn($$, $3);
	}
	| Exp OR Exp {
		$$ = init(Exp);
		appendSyn($$, $1);
		appendLex($$, OR);
		appendSyn($$, $3);
	}
	| Exp RELOP Exp {
		$$ = init(Exp);
		appendSyn($$, $1);
		appendLex($$, RELOP);
		appendSyn($$, $3);
	}
	| Exp PLUS Exp {
		$$ = init(Exp);
		appendSyn($$, $1);
		appendLex($$, PLUS);
		appendSyn($$, $3);
	}
	| Exp MINUS Exp {
		$$ = init(Exp);
		appendSyn($$, $1);
		appendLex($$, MINUS);
		appendSyn($$, $3);
	}
	| Exp STAR Exp {
		$$ = init(Exp);
		appendSyn($$, $1);
		appendLex($$, STAR);
		appendSyn($$, $3);
	}
	| LP Exp RP {
		$$ = init(Exp);
		appendLex($$, LP);
		appendSyn($$, $2);
		appendLex($$, RP);
	}
	| MINUS Exp %prec UMINUS {
		$$ = init(Exp);
		appendLex($$, MINUS);
		appendSyn($$, $2);
	}
	| NOT Exp {
		$$ = init(Exp);
		appendLex($$, NOT);
		appendSyn($$, $2);
	}
	| ID {
		$$ = init(Exp);
		appendLexID($$, ID, $1);
	} 
	| INT {
		$$ = init(Exp);
		appendLexINT($$, INT, $1);
	} 
	| FLOAT {
		$$ = init(Exp);
		appendLexFLOAT($$, FLOAT, $1);
	} 
	;
Args : Exp COMMA Args{
		$$ = init(Args);
		appendSyn($$, $1);
		appendLex($$, COMMA);
		appendSyn($$, $3);
	}
	| Exp{
		$$ = init(Args);
		appendSyn($$, $1);
	}
	;
%%
