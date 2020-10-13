%{
	#include"common.h"
	#include<stdio.h>
	extern SynUnit* init(LexType);
	extern void appendSyn(SynUnit*, SynUnit*);
	extern void appendLex(SynUnit*, LexType);
	extern void appendLexINT(SynUnit*, LexType, int);
	extern void appendLexFLOAT(SynUnit*, LexType, float);
	extern void appendLexTYPE(SynUnit*, LexType, bool);
	extern void appendLexID(SynUnit*, LexType, char*);
	#include"lex.yy.c"
	void yyerror(char const *s);
%}
%code requires{
	#include"common.h"
}
%union {
	int type_int;
	float type_float;
	char *type_str;
	bool type_bool;
	struct SynUnit* type_syn;
}
%token <type_int> INT 0
%token <type_float> FLOAT 1
%token <type_str> ID 2
%token <type_bool> TYPE 15
%token SEMI 3 COMMA 4 LC 20 RC 21 STRUCT 22 RETURN 23 IF 24 ELSE 25 WHILE 26
%type <type_syn> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec FunDec ParamList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args 
%right ASSIGNOP 5 
%left OR 12
%left AND 11
%left RELOP 6
%left PLUS 7 MINUS 8
%left STAR 9 DIV 10
%right UMINUS NOT 14
%left LP 16 RP 17 LB 18 RB 19 DOT 13

%%
/*High level*/
Program : ExtDefList {
		$$ = init(Program);
		appendSyn($$, $1);
		start = $$;
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
		appendLexTYPE($$, TYPE, $1);
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
		appendLexID($$, ID, $1);
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
		appendLexINT($$, INT, $3);
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
	| IF LP Exp RP Stmt ELSE Stmt {
		$$ = init(Stmt);
		appendLex($$, IF);
		appendLex($$, LP);
		appendSyn($$, $3);
		appendLex($$, RP);
		appendSyn($$, $5);
		appendLex($$, ELSE);
		appendSyn($$, $7);
	}
	| WHILE LP Exp RP Stmt {
		$$ = init(Stmt);
		appendLex($$, WHILE);
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
	| {$$ = NULL;}
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
	| Exp DIV Exp {
		$$ = init(Exp);
		appendSyn($$, $1);
		appendLex($$, DIV);
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
	| ID LP Args RP {
		$$ = init(Exp);
		appendLexID($$, ID, $1);
		appendLex($$, LP);
		appendSyn($$, $3);
		appendLex($$, RP);
	}
	| ID LP RP {
		$$ = init(Exp);
		appendLexID($$, ID, $1);
		appendLex($$, LP);
		appendLex($$, RP);
	}
	| Exp LB Exp RB {
		$$ = init(Exp);
		appendSyn($$, $1);
		appendLex($$, LB);
		appendSyn($$, $3);
		appendLex($$, RB);
	}
	| Exp DOT ID {
		$$ = init(Exp);
		appendSyn($$, $1);
		appendLex($$, DOT);
		appendLexID($$, ID, $3);
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
void yyerror(char const *s){
	printf("%s\n", s);
}