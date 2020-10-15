%{
	#include"syntax.tab.h"
    #include<stdio.h>
	#include<stdlib.h>
	#define TYPE_INT false
	#define TYPE_FLOAT true
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
	//printf(yytext);
	return FLOAT; 
}
([0-9]*\.?[0-9]+|[0-9]+\.)[Ee][+-]?[0-9]+ { 
	yylval.type_float = strtof(yytext, NULL);
	//printf(yytext);
	return FLOAT; 
}
0{digit}+  {
    printf("Error type A at Line %d:%d: Illeagal Octal number \"%s\".\n", yylloc.first_line, yylloc.first_column, yytext);
	yynerrs++;
}
0[xX][0-9A-Za-z]+ {
    printf("Error type A at Line %d:%d: Illeagal Hexcadecimal number \"%s\".\n", yylloc.first_line, yylloc.first_column, yytext);
	yynerrs++;
}
[0-9]*\.|\.[0-9]* {
    printf("Error type A at Line %d:%d: Illeagal float number \"%s\".\n", yylloc.first_line, yylloc.first_column, yytext);
	yynerrs++;
}
([0-9]*\.?[0-9]+|[0-9]+\.)[Ee][+-]*([0-9]*\.?[0-9]+|[0-9]+\.)? {
    printf("Error type A at Line %d:%d Illeagal scientific notation \"%s\".\n", yylloc.first_line, yylloc.first_column, yytext);
	yynerrs++;
}
{letter_}({letter_}|{digit})* {    
	yylval.type_str = (char *)malloc(yyleng + 1);
	strcpy(yylval.type_str, yytext);
	return ID; 
}
"//"[^\r\n]* { /* empty */}
"/*"([^*]|\*+[^*/])*"*/" { 		
	/* Block Comment */
	// rule explanation: '*' should not appear, otherwise any sequence of '*' should be follow by other character (other than '*' or '/')
	//reset column line
	yycolumn = 1;
	for(int i = yyleng - 1;i >= 0 && yytext[i] != '\n';i--)
		yycolumn++;
 }
[ \t\r]+ {}
\n {
	yycolumn = 1;
}
. {
    printf("Error type A at Line %d:%d: Illeagal character \'%s\'.\n", yylloc.first_line, yylloc.first_column, yytext);
	yynerrs++;
}
%%
