/*
这是一个指令输出模块，封装了应该要用到的mips32指令格式
使用时，配合storage.h，以获得寄存器的regIdx
使用之前要调用初始化函数initial_instr_module()
之后，可以通过get_instr_format_of(int idx)获得idx对应命令的Instr 对象，各个命令的宏xxx_FORMAT 可以作为参数
可以使用Instr对象的instr_print(Instr*_this)函数输出指令
在输出之前，需要使用rebuild(Instr*_this,...)函数将相应指令格式需要的若干个参数（寄存器、立即数、标签等）传递给对象
*/

#ifndef __MIPS32_H__
#define __MIPS32_H__

#define INSTR_NAME_MAX_NUM 5
#define INSTR_OPERAND_MAX_NUM 3
#define INSTR_FORMATS_MAX_NUM 30

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef short int16_t;

typedef struct _Instr
{
    struct
    {
        union
        {
            struct
            {
                uint8_t basicRegIdx;
                uint8_t __empty__;
                int16_t offset;
            } address;
            int regIdx;
            int immediate;
            char *labelName;
        };
    } operand0, operand1, operand2, operand3;

    void (*instr_print)(struct _Instr *_this);
    void (*rebuild)(struct _Instr *_this, ...);

} Instr;

#define LABEL_FORMAT 0                       // labelname
#define LI_IMM_TO_REG_FORMAT 1               //regIdx, immediate
#define MOVE_REG_TO_REG_FORMAT 2             //regIdx, regIdx
#define ADD_REG_AND_IMM_TO_REG_FORMAT 3      //regIdx, regIdx, immediate
#define ADD_REG_AND_REG_TO_REG_FORMAT 4      //regIdx, regIdx, regIdx
#define SUB_REG_AND_REG_TO_REG_FORMAT 5      //regIdx, regIdx, regIdx
#define MUL_REG_AND_REG_TO_REG_FORMAT 6      //regIdx, regIdx, regIdx
#define DIV_REG_TO_REG_FORMAT 7              //regIdx, regIdx
#define MFLO_REG_FORMAT 8                    //regIdx
#define LW_REG_FROM_ADDRESS_FORMAT 9         //regIdx address{offset,regIdx}
#define SW_REG_TO_ADDRESS_FORMAT 10          //regIdx address{offset,regIdx}
#define J_TO_LABEL_FORMAT 11                 //labelname
#define JAL_LABEL_FORMAT 12                  //labelname
#define MOVE_IMM_TO_REG_FORMAT 13            //NULL for it is equal to li
#define JR_TO_REG_FORMAT 14                  //regIdx
#define BEQ_REG_AND_REG_TO_ADDRESS_FORMAT 15 // regIdx, regIdx, regIdx
#define BNE_REG_AND_REG_TO_ADDRESS_FORMAT 16 // regIdx, regIdx, regIdx
#define BGT_REG_AND_REG_TO_ADDRESS_FORMAT 17 // regIdx, regIdx, regIdx
#define BLT_REG_AND_REG_TO_ADDRESS_FORMAT 18 // regIdx, regIdx, regIdx
#define BGE_REG_AND_REG_TO_ADDRESS_FORMAT 19 // regIdx, regIdx, regIdx
#define BLE_REG_AND_REG_TO_ADDRESS_FORMAT 20 // regIdx, regIdx, regIdx

#define concat(a, b) a##b

#define _INSTR_CREATOR_FUNC_NAME_(idx) concat(creator, idx)
#define _INSTR_CREATOR_FUNC_LABEL_(idx) void _INSTR_CREATOR_FUNC_NAME_(idx)(int index)

#define _INSTR_PRINT_FUNC_NAME_(idx) concat(printer, idx)
#define _INSTR_PRINT_FUNC_LABEL_(idx) void _INSTR_PRINT_FUNC_NAME_(idx)(Instr * _this)

#define _INSTR_REBUILD_FUNC_NAME_(idx) concat(rebuilder, idx)
#define _INSTR_REBUILD_FUNC_LABEL_(idx) void _INSTR_REBUILD_FUNC_NAME_(idx)(Instr * _this, ...)

#define _MAKE_INSTR_(idx)                                             \
    do                                                                \
    {                                                                 \
        static_instr_formats[idx].instr_print = concat(printer, idx); \
        concat(creator, idx)(idx);                                    \
    } while (0)

//Initial the mudule
void initial_instr_module();
Instr get_instr_format_of(int idx); //API---- get a copy of an initialized instruction format singleton pattern

//creator functions declearation
_INSTR_CREATOR_FUNC_LABEL_(LABEL_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(LI_IMM_TO_REG_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(MOVE_REG_TO_REG_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(ADD_REG_AND_IMM_TO_REG_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(ADD_REG_AND_REG_TO_REG_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(SUB_REG_AND_REG_TO_REG_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(MUL_REG_AND_REG_TO_REG_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(DIV_REG_TO_REG_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(MFLO_REG_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(LW_REG_FROM_ADDRESS_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(SW_REG_TO_ADDRESS_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(J_TO_LABEL_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(JAL_LABEL_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(MOVE_IMM_TO_REG_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(JR_TO_REG_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(BEQ_REG_AND_REG_TO_ADDRESS_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(BNE_REG_AND_REG_TO_ADDRESS_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(BGT_REG_AND_REG_TO_ADDRESS_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(BLT_REG_AND_REG_TO_ADDRESS_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(BGE_REG_AND_REG_TO_ADDRESS_FORMAT);
_INSTR_CREATOR_FUNC_LABEL_(BLE_REG_AND_REG_TO_ADDRESS_FORMAT);

#endif //__MIPS32_H__