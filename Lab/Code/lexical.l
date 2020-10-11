%{
    #include<stdio.h>
    #include"Definition.h"
    void print(char*);
%}
%option yylineno
%option noyywrap
digit [0-9]
letter [a-zA-Z]
letter_ [A-Za-z_]

%%

; {
    print("SEMI");
}
, {
    print("COMMA");
}
= {
    print("ASSIGNOP");
}
>|<|>=|<=|==|!= {
    print("RELOP");
}
\+ {
    print("PLUS");
}
- {
    print("MINUS");
}
\* {
    print("STAR");
}
\/ {
    print("DIV");
}
&& {
    print("AND");
}
\|\| {
    print("OR");
}
\. {
    print("DOT");
}
! {
    print("NOT");
}
int|float {
    print("TPYE");
}
\( {
    print("LP");
}
\) {
    print("RP");
}
\[ {
    print("LB");
}
\] {
    print("RB");
}
\{ {
    print("LC");
}
\} {
    print("RC");
}
struct {
    print("STRUCT");
}
return {
    print("return");
}
if {
    print("IF");
}
else {
    print("ELSE");
}
while {
    print("WHILE");
}
0|([1-9][0-9]*) {
    print("DECIMAL");
}

0[0-7]+  {
    print("OCTAL");
}
0[xX][0-9A-Fa-f]+ {
    print("HEXADECIMAL");
}
[0-9]+\.[0-9]+ {
    print("NORMFLOAT");
}
([0-9]*\.?[0-9]+|[0-9]+\.)[Ee][+-]?[0-9]+ {
    print("SCIF");
}
{letter_}({letter_}|{digit})* {
    print("ID");
}
"//"[^\r\n]* {
    // inline comment should include any characters but '\n'
    print("COMMENT");
}
"/*"([^*]|\*+[^*/])*"*/" {
    // '*' should not be appear, otherwise any of '*' sequence should be followed by a character other than '*' or '/'
    print("COMMENT");
}

[ \t\r\n]+ {
    // white space
}
. {
    printf("Something went wrong @ line: %d\n", yylineno);
}

%%
void print(char *type){                 // make Tokens
    printf("%s = \"%s\" @ line: %d\n", type,yytext, yylineno);
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