%{
	#include"syntax.tab.h"
    #include<stdio.h>
	#include<stdlib.h>
	#define TYPE_INT false
	#define TYPE_FLOAT true
	#define EQ 0
	#define LES_EQ 1
	#define GRT_EQ 2
	#define LES 3
	#define GRT 4
	#define NOT_EQ 5
	int yycolumn = 1;
	extern int yynerrs;
	#define YY_USER_ACTION \
		yylloc.first_line = yylloc.last_line = yylineno;\
		yylloc.first_column = yycolumn;\
		yylloc.last_column = yycolumn + yyleng - 1;\
		yycolumn += yyleng;
%}
%option yylineno
%option noyywrap
digit [0-9]
letter [a-zA-Z]
letter_ [A-Za-z_]
newline \r?\n
%x BLOCK_COMMENT
%x LINE_COMMENT
%%

; { return SEMI; }
, { return COMMA; }
"==" { 
	yylval.type_int = EQ;
	return RELOP; 
}
"!=" { 
	yylval.type_int = NOT_EQ;
	return RELOP; 
}
">=" { 
	yylval.type_int = GRT_EQ;
	return RELOP; 
}
"<=" { 
	yylval.type_int = LES_EQ;
	return RELOP; 
}
">" { 
	yylval.type_int = GRT;
	return RELOP; 
}
"<" { 
	yylval.type_int = LES;
	return RELOP; 
}
= { return ASSIGNOP;}
\+ { return PLUS; }
- { return MINUS; }
\* { return STAR; }
\/ { return DIV; }
&& { return AND; }
\|\| { return OR; }
\. { return DOT; }
! { return NOT; }
int { 
	yylval.type_bool = TYPE_INT;
	return TYPE; 
}
float {
	yylval.type_bool = TYPE_FLOAT;
	return TYPE;
}
\( { return LP; }
\) { return RP; }
\[ { return LB; }
\] { return RB; }
\{ { return LC; }
\} { return RC; }
struct { return STRUCT; }
return { return RETURN; }
if { return IF; }
else { return ELSE; }
while { return WHILE; }
0|([1-9][0-9]*) { 
	yylval.type_int = strtol(yytext, NULL, 0);
	return INT; 
}
0[0-7]+ { 
	yylval.type_int = strtol(yytext, NULL, 0);
	return INT; 
}
0[xX][0-9A-Fa-f]+ { 
	yylval.type_int = strtol(yytext, NULL, 0);
	return INT; 
}
[0-9]+\.[0-9]+ { 
	yylval.type_float = strtof(yytext, NULL);
	//printf(yytext);
	return FLOAT; 
}
([0-9]*\.?[0-9]+|[0-9]+\.)[Ee][+-]?[0-9]+ { 
	yylval.type_float = strtof(yytext, NULL);
	//printf(yytext);
	return FLOAT; 
}
0{digit}+  {
    printf("Error type A at Line %d:%d: Illegal Octal number \"%s\".\n", yylloc.first_line, yylloc.first_column, yytext);
	yynerrs++;
}
0[xX][0-9A-Za-z]+ {
    printf("Error type A at Line %d:%d: Illegal Hexcadecimal number \"%s\".\n", yylloc.first_line, yylloc.first_column, yytext);
	yynerrs++;
}
[0-9]*\.|\.[0-9]* {
    printf("Error type A at Line %d:%d: Illegal float number \"%s\".\n", yylloc.first_line, yylloc.first_column, yytext);
	yynerrs++;
}
([0-9]*\.?[0-9]+|[0-9]+\.)[Ee][+-]*([0-9]*\.?[0-9]+|[0-9]+\.)? {
    printf("Error type A at Line %d:%d: Illegal scientific notation \"%s\".\n", yylloc.first_line, yylloc.first_column, yytext);
	yynerrs++;
}
{letter_}({letter_}|{digit})* {    
	yylval.type_str = (char *)malloc(yyleng + 1);
	strcpy(yylval.type_str, yytext);
	return ID; 
}
{digit}({letter_}|{digit})* {    
	printf("Error type A at Line %d:%d: Illegal identifier \"%s\".\n", yylloc.first_line, yylloc.first_column, yytext);
}
"//" {BEGIN(LINE_COMMENT);}
<LINE_COMMENT>{
	{newline} {yycolumn = 1;BEGIN(INITIAL);}
	. {}
} 
"/*" {BEGIN(BLOCK_COMMENT);}
<BLOCK_COMMENT>{
	"*/" { BEGIN(INITIAL);}
	<<EOF>> {yynerrs++;printf("Error type A at Line %d:%d: EOF in a block comment.\n", yylloc.first_line, yylloc.first_column);yyterminate();}
	{newline} {yycolumn = 1;}
	. {}
}
[ \t\r]+ {}
{newline} {
	yycolumn = 1;
}
. {
    printf("Error type A at Line %d:%d: Illegal character \'%s\'.\n", yylloc.first_line, yylloc.first_column, yytext);
	yynerrs++;
}
%%
