struct Tokens{
    enum
    {
        INT,
        FLOAT,
        ID,
        SEMI,
        COMMA,
        ASSIGNOP,
        RELOP,
        PLUS,
        MUNUS,
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
    int colno;
    // here is a pointer to symbol table
    enum
    {
        DEC,
        OCT,
        HEX,
        NORMF,
        SCIF
    } format;          
    union{
        unsigned int ival;
        float fval;
    };                  //used if type == INT || type == FLOAT
    
};

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
