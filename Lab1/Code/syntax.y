%{
	#include"common.h"
	#include<stdio.h>
	extern SynUnit* init(LexType, int);
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
		$$ = init(Program, @$.first_line);
		appendSyn($$, $1);
		start = $$;
}
	;

ExtDefList : ExtDef ExtDefList {
		$$ = init(ExtDefList, @$.first_line);
		appendSyn($$, $1);
		appendSyn($$, $2);
	}
	| {$$ = NULL;}
	;

ExtDef : Specifier ExtDecList SEMI {
		$$ = init(ExtDef, @$.first_line);
		appendSyn($$, $1);
		appendSyn($$, $2);
		appendLex($$, SEMI);
	}
	| Specifier SEMI {
		$$ = init(ExtDef, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, SEMI);
	}
	| Specifier FunDec CompSt {
		$$ = init(ExtDef, @$.first_line);
		appendSyn($$, $1);
		appendSyn($$, $2);
		appendSyn($$, $3);
	}
	| Specifier error CompSt {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected function Definitions"));}
	| error FunDec CompSt {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected function Definitions"));}
	| error error CompSt {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected function Definitions"));}
	;
ExtDecList : VarDec {
		$$ = init(ExtDecList, @$.first_line);
		appendSyn($$, $1);
	}
	| VarDec COMMA ExtDecList {
		$$ = init(ExtDecList, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, COMMA);
		appendSyn($$, $3);
	}
	| error VarDec {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected ExtDecList"));}
	;

/* Specifiers*/
Specifier : TYPE {
		$$ = init(Specifier, @$.first_line);
		appendLexTYPE($$, TYPE, $1);
	}
	| StructSpecifier {
		$$ = init(Specifier, @$.first_line);
		appendSyn($$, $1);
	}
	| error Specifier {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected Specifier"));}
	;
StructSpecifier : STRUCT OptTag LC DefList RC {
		$$ = init(StructSpecifier, @$.first_line);
		appendLex($$, STRUCT);
		appendSyn($$, $2);
		appendLex($$, LC);
		appendSyn($$, $4);
		appendLex($$, RC);
	}
	| STRUCT Tag {
		$$ = init(StructSpecifier, @$.first_line);
		appendLex($$, STRUCT);
		appendSyn($$, $2);
	}
	;
OptTag : ID {
		$$ = init(OptTag, @$.first_line);
		appendLexID($$, ID, $1);
	}
	| {$$ = NULL;}
	;
Tag : ID {
		$$ = init(Tag, @$.first_line);
		appendLexID($$, ID, $1);
	}
	;

/* Declarators*/
VarDec : ID {
		$$ = init(VarDec, @$.first_line);
		appendLexID($$, ID, $1);
	}
	| VarDec LB INT RB {
		$$ = init(VarDec, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, LB);
		appendLexINT($$, INT, $3);
		appendLex($$, RB);
	}
	| error VarDec {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected VarDec"));}
	;
FunDec : ID LP ParamList RP {
		$$ = init(FunDec, @$.first_line);
		appendLexID($$, ID, $1);
		appendLex($$, LP);
		appendSyn($$, $3);
		appendLex($$, RP);
	}
	| ID LP RP {
		$$ = init(FunDec, @$.first_line);
		appendLexID($$, ID, $1);
		appendLex($$, LP);
		appendLex($$, RP);
	}
	| error FunDec {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected FunDec"));}
	;
ParamList : ParamDec COMMA ParamList {
		$$ = init(ParamList, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, COMMA);
		appendSyn($$, $3);
	}
	| ParamDec {
		$$ = init(ParamList, @$.first_line);
		appendSyn($$, $1);
	}
	| error ParamList {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected ParamList"));}
	;
ParamDec : Specifier VarDec {
		$$ = init(ParamDec, @$.first_line);
		appendSyn($$, $1);
		appendSyn($$, $2);
	}
	;

CompSt : LC DefList StmtList RC {
		$$ = init(CompSt, @$.first_line);
		appendLex($$, LC);
		appendSyn($$, $2);
		appendSyn($$, $3);
		appendLex($$, RC);
	}
	| error CompSt {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected CompSt"));}
	;
StmtList : Stmt StmtList {
		$$ = init(StmtList, @$.first_line);
		appendSyn($$, $1);
		appendSyn($$, $2);
	}
	| {$$ = NULL;}
	;
Stmt : Exp SEMI {
		$$ = init(Stmt, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, SEMI);
	}
	| CompSt {
		$$ = init(Stmt, @$.first_line);
		appendSyn($$, $1);
	}
	| RETURN Exp SEMI {
		$$ = init(Stmt, @$.first_line);
		appendLex($$, RETURN);
		appendSyn($$, $2);
		appendLex($$, SEMI);
	}
	| IF LP Exp RP Stmt {
		$$ = init(Stmt, @$.first_line);
		appendLex($$, IF);
		appendLex($$, LP);
		appendSyn($$, $3);
		appendLex($$, RP);
		appendSyn($$, $5);
	}
	| IF LP Exp RP Stmt ELSE Stmt {
		$$ = init(Stmt, @$.first_line);
		appendLex($$, IF);
		appendLex($$, LP);
		appendSyn($$, $3);
		appendLex($$, RP);
		appendSyn($$, $5);
		appendLex($$, ELSE);
		appendSyn($$, $7);
	}
	| WHILE LP Exp RP Stmt {
		$$ = init(Stmt, @$.first_line);
		appendLex($$, WHILE);
		appendLex($$, LP);
		appendSyn($$, $3);
		appendLex($$, RP);
		appendSyn($$, $5);
	}
	| error Stmt {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected Stmt"));}
	;

/* Local Definitions*/
DefList : Def DefList {
		$$ = init(DefList, @$.first_line);
		appendSyn($$, $1);
		appendSyn($$, $2);
	}
	| {$$ = NULL;}
	;
Def : Specifier DecList SEMI {
		$$ = init(Def, @$.first_line);
		appendSyn($$, $1);
		appendSyn($$, $2);
		appendLex($$, SEMI);
	}
	| error Def {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected Def"));}
	;
DecList : Dec {
		$$ = init(DecList, @$.first_line);
		appendSyn($$, $1);
	}	
	| Dec COMMA DecList {
		$$ = init(DecList, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, COMMA);
		appendSyn($$, $3);
	}
	| error DecList {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected DecList"));}
	;
Dec : VarDec {
		$$ = init(Dec, @$.first_line);
		appendSyn($$, $1);
	}
	| VarDec ASSIGNOP Exp{
		$$ = init(Dec, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, ASSIGNOP);
		appendSyn($$, $3);
	}
	;

/* Expressions */
Exp : Exp ASSIGNOP Exp {
		$$ = init(Exp, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, ASSIGNOP);
		appendSyn($$, $3);
	}
	| Exp AND Exp {
		$$ = init(Exp, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, AND);
		appendSyn($$, $3);
	}
	| Exp OR Exp {
		$$ = init(Exp, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, OR);
		appendSyn($$, $3);
	}
	| Exp RELOP Exp {
		$$ = init(Exp, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, RELOP);
		appendSyn($$, $3);
	}
	| Exp PLUS Exp {
		$$ = init(Exp, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, PLUS);
		appendSyn($$, $3);
	}
	| Exp MINUS Exp {
		$$ = init(Exp, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, MINUS);
		appendSyn($$, $3);
	}
	| Exp STAR Exp {
		$$ = init(Exp, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, STAR);
		appendSyn($$, $3);
	}
	| Exp DIV Exp {
		$$ = init(Exp, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, DIV);
		appendSyn($$, $3);
	}
	| LP Exp RP {
		$$ = init(Exp, @$.first_line);
		appendLex($$, LP);
		appendSyn($$, $2);
		appendLex($$, RP);
	}
	| MINUS Exp %prec UMINUS {
		$$ = init(Exp, @$.first_line);
		appendLex($$, MINUS);
		appendSyn($$, $2);
	}
	| NOT Exp {
		$$ = init(Exp, @$.first_line);
		appendLex($$, NOT);
		appendSyn($$, $2);
	}
	| ID LP Args RP {
		$$ = init(Exp, @$.first_line);
		appendLexID($$, ID, $1);
		appendLex($$, LP);
		appendSyn($$, $3);
		appendLex($$, RP);
	}
	| ID LP RP {
		$$ = init(Exp, @$.first_line);
		appendLexID($$, ID, $1);
		appendLex($$, LP);
		appendLex($$, RP);
	}
	| Exp LB Exp RB { 
		$$ = init(Exp, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, LB);
		appendSyn($$, $3);
		appendLex($$, RB);
	}

	| Exp DOT ID {
		$$ = init(Exp, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, DOT);
		appendLexID($$, ID, $3);
	}
	| ID {
		$$ = init(Exp, @$.first_line);
		appendLexID($$, ID, $1);
	} 
	| INT {
		$$ = init(Exp, @$.first_line);
		appendLexINT($$, INT, $1);
	} 
	| FLOAT {
		$$ = init(Exp, @$.first_line);
		appendLexFLOAT($$, FLOAT, $1);
	}
	| error Exp {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected expressions"));}
	;
Args : Exp COMMA Args{
		$$ = init(Args, @$.first_line);
		appendSyn($$, $1);
		appendLex($$, COMMA);
		appendSyn($$, $3);
	}
	| Exp{
		$$ = init(Args, @$.first_line);
		appendSyn($$, $1);
	}
	| error Args {yyerror(errorf(SYN_ERROR,@$.first_line,"unexpected args"));}
	;
%%
void yyerror(const char *s){
	if(errorOutput)
	{
		puts(s);
		errorOutput = 0;
	}
}