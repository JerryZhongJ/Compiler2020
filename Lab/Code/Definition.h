struct Symbol{
	char *name;
};
struct Tokens
{
	enum Tokens_t
    {
        INT,
        FLOAT,
        ID,
        SEMI,
        COMMA,
        ASSIGNOP,
        RELOP,
        PLUS,
        MINUS,
        STAR,
        DIV,
        AND,
        OR,
        DOT,
        NOT,
        TYPE,
        LP,
        RP,
        LB,
        RB,
        LC,
        RC,
        STRUCT,
        RETURN,
        IF,
        ELSE,
        WHILE,
        FOR
    } type;
    char *lexeme; // remember to malloc!
    int lineno;
	union{
		struct Symbol* sym_ptr;
        unsigned int ival;
        float fval;
    };                  //used if type == INT || type == FLOAT
} token;

char tokens_type[][10] = {"INT",
						  "FLOAT",
						  "ID",
						  "SEMI",
						  "COMMA",
						  "ASSIGNOP",
						  "RELOP",
						  "PLUS",
						  "MUNUS",
						  "STAR",
						  "DIV",
						  "AND",
						  "OR",
						  "DOT",
						  "NOT",
						  "TYPE",
						  "LP",
						  "RP",
						  "LB",
						  "RB",
						  "LC",
						  "RC",
						  "STRUCT",
						  "RETURN",
						  "IF",
						  "ELSE",
						  "WHILE",
						  "FOR"};
