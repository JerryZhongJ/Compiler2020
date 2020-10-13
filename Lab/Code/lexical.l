%{
	#include"syntax.tab.h"
    #include<stdio.h>
	#include<stdlib.h>
	#define TYPE_INT false
	#define TYPE_FLOAT true
%}
%option yylineno
%option noyywrap
digit [0-9]
letter [a-zA-Z]
letter_ [A-Za-z_]

%%

; { return SEMI; }
, { return COMMA; }
= { return ASSIGNOP;}
>|<|>=|<=|==|!= { return RELOP; }
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
	return FLOAT; 
}
([0-9]*\.?[0-9]+|[0-9]+\.)[Ee][+-]?[0-9]+ { 
	yylval.type_float = strtof(yytext, NULL);
	return FLOAT; 
}
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
{letter_}({letter_}|{digit})* {    
	yylval.type_str = (char *)malloc(yyleng + 1);
	strcpy(yylval.type_str, yytext);
	return ID; 
}
"//"[^\r\n]* { /* empty */}
"/*"([^*]|\*+[^*/])*"*/" { /* empty */ }
[ \t\r\n]+ {}
. {
    printf("Error type A at Line %d: Illeagal character \'%s\'.\n", yylineno, yytext);
}

%%
