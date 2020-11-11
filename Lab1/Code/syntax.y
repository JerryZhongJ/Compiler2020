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
%define parse.error verbose
%define parse.lac full
%token <type_int> INT 260 "interger"
%token <type_float> FLOAT 261 "float"
%token <type_str> ID 262 "identifier"
%token <type_bool> TYPE 275 
%token SEMI 263 ";" 
%token COMMA 264 "," 
%token LC 280 "{"
%token RC 281 "}"
%token STRUCT 282 "struct"
%token RETURN 283 "return"
%token IF 284 "if"
%token ELSE 285 "else"
%token WHILE 286 "while"
%token ASSIGNOP 265 "="
%token OR 272 "||"
%token AND 271 "&&"
%token RELOP 266 "relational operator"
%token PLUS 267 "+" 
%token MINUS 268 "-"
%token STAR 269 "*" 
%token DIV 270 "/"
%token NOT 274 "!"
%token LP 276 "("
%token RP 277 ")"
%token LB 278 "["
%token RB 279 "]"
%token DOT 273 "."
%type <type_syn> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec FunDec ParamList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args 
%right ASSIGNOP
%left OR 
%left AND 
%left RELOP  
%left PLUS  MINUS 
%left STAR  DIV 
%right UMINUS NOT 
%left LP RP LB RB DOT 
%start Program

%precedence RC
%precedence PRIOR


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
	| error ExtDefList {yyerrok;$$ = $2;};
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
	| error SEMI {yyerrok;$$=NULL;}
	| error CompSt {yyerrok;$$=NULL;}
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
	| error ParamList {yyerrok;$$=$2;}
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
	| error RC {yyerrok;$$=NULL;}
	;
StmtList : Stmt StmtList {
		$$ = init(StmtList, @$.first_line);
		appendSyn($$, $1);
		appendSyn($$, $2);
	}
	| {$$ = NULL;} %prec PRIOR
	| error StmtList {yyerrok;$$ = $2;}
	| Stmt error Def DefList StmtList {yyerrok;$$ = NULL;}
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
	| error SEMI {yyerrok;$$=NULL;}
	| IF error Stmt {yyerrok;$$=NULL;}
	| IF error ELSE Stmt  {yyerrok;$$=NULL;}
	| WHILE error Stmt  {yyerrok;$$=NULL;}
	;

/* Local Definitions*/
DefList : Def DefList {
		$$ = init(DefList, @$.first_line);
		appendSyn($$, $1);
		appendSyn($$, $2);

	}
	| {$$ = NULL;}
	| error Def DefList {yyerrok;$$ = $2;}
	;
Def : Specifier DecList SEMI {
		$$ = init(Def, @$.first_line);
		appendSyn($$, $1);
		appendSyn($$, $2);
		appendLex($$, SEMI);
	}
	| Specifier error SEMI {yyerrok;$$=NULL;}  
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
	//| error COMMA DecList {yyerrok;$$=NULL;}
	//| Dec error DecList  {yyerrok;$$=NULL;}
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
	//| VarDec ASSIGNOP error {$$=NULL;}
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
	//| error COMMA Args {yyerrok;$$=NULL;}
	//| Exp error Args  {yyerrok;$$=NULL;}
	;
%%
void yyerror(char const *s){
	printf("Error type B at Line %d:%d: %s\n", yylloc.first_line, yylloc.first_column ,s);
}
