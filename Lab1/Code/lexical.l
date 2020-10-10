
alpha [a-zA-Z]
digit [0-9]
ud (0)|([1-9][0-9]*)
uo 0((0)|([1-7][0-7]*))
uh 0x((0)|([1-9a-f][0-9a-f]*))

int  {ud}|{uo}|{uh}
float ({ud}\.{ud})|((({ud}*\.{ud}+)|({ud}+\.))(e|E)-?{ud})
id (_|[a-zA-Z])[_0-9a-zA-Z]*
semi ;
comma ,
assignop ">"|"<"|">="|"<="|"=="|"!="
plus "+"
minus "-"
star "*"
div "/"
and "&&"
or "||"
dot "."
not "!"
type int|float
lp "("
rp ")"
lb "["
rb "]"
lc "{"
rc "}"
__struct struct
__return return
__if if
__else else
__while while

%%
{semi} {printf("SEMI ");}
{comma} {printf("COMMA ");}
{assignop} {printf("ASSIGNOP ");}
{plus} {printf("PLUS ");}
{minus} {printf("MINUS ");}
{star} {printf("STAR ");}
{div} {printf("DIV ");}
{and} {printf("AND ");}
{or} {printf("OR ");}
{dot} {printf("DOT ");}
{not} {printf("NOT ");}
{type} {printf("TYPE ");}
{lp} {printf("LP ");}
{rp} {printf("RP ");}
{lb} {printf("LB ");}
{rb} {printf("RB ");}
{lc} {printf("LC ");}
{rc} {printf("RC ");}
{__struct} {printf("STRUCT ");}
{__return} {printf("RETURN ");}
{__if} {printf("IF ");}
{__else} {printf("ELSE ");}
{__while} {printf("WHILE ");}
{int} {printf("INT ");}
{float} {printf("FLOAT ");}
{id} {printf("ID ");;}
%%
int main(int argc,char*argv[]){
    if(argc<2)
    {
        return -1;
    }
    else
    {
        if(yyin = fopen(argv[1],"r"))
        {
            yylex();
        }
        else
        {
            return -1;
        }
    }
    return 0;
}