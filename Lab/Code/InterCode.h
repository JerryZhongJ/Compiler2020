# ifndef __INTERCODE__
# define __INTERCODE__
#include<stdbool.h>
#include<stdio.h>
#include"MIPS32.h"
typedef struct Operand_{
    enum
    {
        OPR_VARIABLE,       // 源程序定义中的变量
        
        OPR_CONST,
        OPR_LABEL,          // 标签 同时作为 函数名
        OPR_FUNCNAME,
        //OPR_RELOP
        OPR_REF             // 引用, 形如 &y
    } type;
    union{
        struct{
            int var_no;
            bool var_tmp;
            // -1 for null, 0 - 31 for reg num
            int var_reg;
            // 0 for null, + for downside, - for upside
            int var_mem;
            RefRecord* var_refrec;
        };

        int const_value;  // 常量值
        struct
        {
            int label_no;
        };
        struct Operand_ *refered;  // 用于引用类型, 记录被引用变量是不是临时变量, 编号多少
        char *funcname;
    };
} *Operand;
typedef struct InterCode {
    enum
    {
        CODE_LABEL,       //LABEL x:
        CODE_FUNC,        // FUNCTION f :
        CODE_ASSIGN,      // x := y
        CODE_PLUS,        // x := y + z
        CODE_SUB,         // x := y - z
        CODE_MUL,         // x := y * z
        CODE_DIV,         // x := y / z
        //CODE_GET_ADDR,    // x := &y
        CODE_ASSIGN_FROM, // x := *y
        CODE_ASSIGN_INTO, // *x = y
        CODE_JMP,         // GOTO x
        CODE_COND_JMP,    // IF x [relop] y GOTO z
        CODE_RET,         // RETURN x
        CODE_DEC,         // DEC x [size]
        CODE_ARG,         // ARG x
        CODE_CALL,        // x := CALL f
        CODE_PARAM,       // PARAM x
        CODE_READ,        // READ x
        CODE_WRITE        // WRITE x
    } type;
    union {
        struct {
            Operand right, left;
        } assign, assign_from, assign_into;
        struct {
            Operand right, left;
            ARGList* arg_list;
        } call;
        struct {
            Operand res, op1, op2;
        } plus, sub, mul, div;

        struct {
            Operand label_name;
        } label, jmp;

        struct{
            Operand funcname;
        } func;
        
        struct {
            Operand op;
        } ret, arg, param, read, write;

        struct {
            Operand op1, op2;
            enum
            {
                EQ = 0, LES_EQ, GRT_EQ, LES, GRT, NOT_EQ
            } relop;
            Operand label_name;
        } cond_jmp;
        struct {
            Operand op;
            int size;
        } dec;
    };
    int lineno;
    struct InterCode *prev, *next;
} InterCode;

extern InterCode *codes;
extern InterCode *tail;
extern Operand entry;
Operand getVarName(bool);
Operand getConst();
Operand getLabel();
Operand getRef(Operand refered);
Operand getFuncName(char *);
void genCode1(int, Operand opr);
void genCode2(int kind, Operand left, Operand right);
void genCode3(int kind, Operand res, Operand opr1, Operand opr2);
void genCode4(int kind, Operand opr1, Operand opr2, int relop, Operand label_name);
void genCodeDec(Operand op, int size);
void printCode(FILE *);
#endif