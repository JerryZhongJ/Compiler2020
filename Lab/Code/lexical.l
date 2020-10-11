%{
    #include<stdio.h>
    #include"Definition.h"
	#include<stdlib.h>
	#include<string.h>
    void packing(enum Tokens_t);
%}
%option yylineno
%option noyywrap
digit [0-9]
letter [a-zA-Z]
letter_ [A-Za-z_]

%%

; { packing(SEMI); }
, { packing(COMMA); }
= { packing(ASSIGNOP);}
>|<|>=|<=|==|!= { packing(RELOP); }
\+ { packing(PLUS); }
- { packing(MINUS); };
\* { packing(STAR); };
\/ { packing(DIV); };
&& { packing(AND); };
\|\| { packing(OR); };
\. { packing(DOT); };
! { packing(NOT); };
int|float { packing(TYPE); };
\( { packing(LP); };
\) { packing(RP); };
\[ { packing(LB); };
\] { packing(RB); };
\{ { packing(LC); };
\} { packing(RC); };
struct { packing(STRUCT); };
return { packing(RETURN); };
if { packing(IF); };
else { packing(ELSE); };
while { packing(WHILE); };
0|([1-9][0-9]*) { packing(INT); };
0[0-7]+ { packing(INT); };
0[xX][0-9A-Fa-f]+ { packing(INT); };
[0-9]+\.[0-9]+ { packing(FLOAT); };
([0-9]*\.?[0-9]+|[0-9]+\.)[Ee][+-]?[0-9]+ { packing(FLOAT); };
0{digit}+  {
    printf("Error type A at Line %d: Illeagal Octal number \"%s\".\n", yylineno, yytext);
}
0[xX][0-9A-Za-z]+ {
    printf("Error type A at Line %d: Illeagal Hexcadecimal number \"%s\".\n", yylineno, yytext);
}
[0-9]*\.|\.[0-9]* {
    printf("Error type A at Line %d: Illeagal float number \"%s\".\n", yylineno, yytext);
}
([0-9]*\.?[0-9]+|[0-9]+\.)[Ee][+-]*([0-9]*\.?[0-9]+|[0-9]+\.)? {
    printf("Error type A at Line %d: Illeagal scientific notation \"%s\".\n", yylineno, yytext);
}
{letter_}({letter_}|{digit})* {    packing(ID); }
"//"[^\r\n]* {}
"/*"([^*]|\*+[^*/])*"*/" {}
[ \t\r\n]+ {}
. {
    printf("Error type A at Line %d: Illeagal character \'%s\'.\n", yylineno, yytext);
}

%%
void packing(enum Tokens_t type){
	token.type = type;
	token.lexeme = malloc(yyleng + 1);
	strcpy(token.lexeme, yytext);
	token.lineno = yylineno;
	switch(type){
		case INT:
			token.ival = strtol(yytext, NULL, 0);
			break;
		case FLOAT:
			token.fval = strtof(yytext, NULL);
			break;
		case ID:
			// search symbol
			break;
		default:
			token.ival = 0;
	}
}

int main(int argc, char **argv){
    if(argc > 1){
        if(!(yyin = fopen(argv[1], "r"))){
            perror(argv[1]);
            return 1;
        }else{
            while(yylex() != 0);
        }
    }
    return 0;
}