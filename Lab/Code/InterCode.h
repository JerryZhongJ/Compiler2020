# ifndef __InterCODE__
# define __InterCODE__
#include<stdbool.h>
#include<stdio.h>
typedef struct Operand_{
    enum
    {
        OPR_VARIABLE,       // 源程序定义中的变量
        OPR_TMP,            //临时变量
        OPR_CONST,
        OPR_LABEL,          // 标签 同时作为 函数名
        //OPR_RELOP
        OPR_REF             // 引用, 形如 &y
    } kind;
    union{
        int var_no;     // 变量编号
        struct {
            int tmp_no;     // 临时变量编号
            bool used;      // 临时变量会被使用(引用)
        };
        int const_value;    // 常量值
        struct
        {
            int label_no;
            int ref_num;    // 出现在GOTO中的次数, 优化时记得维护这个值
        };
        struct Operand_ *refered;  // 用于引用类型, 记录被引用变量是不是临时变量, 编号多少
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
    } kind;
    union {
        struct {
            Operand right, left;
        } assign, assign_from, assign_into, call;

        struct {
            Operand res, op1, op2;
        } plus, sub, mul, div;

        struct {
            Operand label_name;
        } label, jmp, func;

        struct {
            Operand op;
        } ret, arg, param, read, write;

        struct {
            Operand op1, op2;
            enum
            {
                EQ = 1, LES_EQ=2, GRT_EQ=3, LES=-3, GRT=-2, NOT_EQ=-1
            } relop;
            Operand label_name;
        } cond_jmp;
        struct {
            Operand op;
            int size;
        } dec;
    };
    struct InterCode *prev, *next;
} InterCode;

extern InterCode *codes;
extern InterCode *tail;
extern Operand entry;
Operand getVarName();
Operand getTmpVarName();
Operand getConst();
Operand getLabel();
Operand getRef(Operand refered);
void genCode1(int, Operand opr);
void genCode2(int kind, Operand left, Operand right);
void genCode3(int kind, Operand res, Operand opr1, Operand opr2);
void genCode4(int kind, Operand opr1, Operand opr2, int relop, Operand label_name);
void genCodeDec(Operand op, int size);
void printCode(FILE *);
#endif
