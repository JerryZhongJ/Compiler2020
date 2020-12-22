#include "mips32.h"
#include "storage.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
static Instr static_instr_formats[INSTR_FORMATS_MAX_NUM]; //singleton pattens with correct function will be initialized and never be changed later
Instr get_instr_format_of(int idx)
{
    return static_instr_formats[idx];
}

//print functions declearation
static _INSTR_PRINT_FUNC_LABEL_(LABEL_FORMAT)
{
    printf("%s:\n", _this->operand0.labelName);
}
static _INSTR_PRINT_FUNC_LABEL_(LI_IMM_TO_REG_FORMAT)
{
    printf("li $%s, %d\n", get_reg_tag(_this->operand0.regIdx), _this->operand1.immediate);
}
static _INSTR_PRINT_FUNC_LABEL_(MOVE_REG_TO_REG_FORMAT)
{
    printf("move $%s, $%s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx));
}
static _INSTR_PRINT_FUNC_LABEL_(ADD_REG_AND_IMM_TO_REG_FORMAT)
{
    printf("addi $%s, $%s, %d\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx), _this->operand2.immediate);
}
static _INSTR_PRINT_FUNC_LABEL_(ADD_REG_AND_REG_TO_REG_FORMAT)
{
    printf("add $%s, $%s, $%s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx), get_reg_tag(_this->operand2.regIdx));
}
static _INSTR_PRINT_FUNC_LABEL_(SUB_REG_AND_REG_TO_REG_FORMAT)
{
    printf("sub $%s, $%s, $%s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx), get_reg_tag(_this->operand2.regIdx));
}
static _INSTR_PRINT_FUNC_LABEL_(MUL_REG_AND_REG_TO_REG_FORMAT)
{
    printf("mul $%s, $%s, $%s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx), get_reg_tag(_this->operand2.regIdx));
}
static _INSTR_PRINT_FUNC_LABEL_(DIV_REG_TO_REG_FORMAT)
{
    printf("div $%s, $%s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx));
}
static _INSTR_PRINT_FUNC_LABEL_(MFLO_REG_FORMAT)
{
    printf("mflo, $%s\n", get_reg_tag(_this->operand0.regIdx));
}
static _INSTR_PRINT_FUNC_LABEL_(LW_REG_FROM_ADDRESS_FORMAT)
{
    printf("lw $%s, %d($%s)\n", get_reg_tag(_this->operand0.regIdx), _this->operand1.address.offset, get_reg_tag(_this->operand1.address.basicRegIdx));
}
static _INSTR_PRINT_FUNC_LABEL_(SW_REG_TO_ADDRESS_FORMAT)
{
    printf("sw $%s, %d($%s)\n", get_reg_tag(_this->operand0.regIdx), _this->operand1.address.offset, get_reg_tag(_this->operand1.address.basicRegIdx));
}
static _INSTR_PRINT_FUNC_LABEL_(J_TO_LABEL_FORMAT)
{
    printf("j %s\n", _this->operand0.labelName);
}
static _INSTR_PRINT_FUNC_LABEL_(JAL_LABEL_FORMAT)
{
    printf("jal %s\n", _this->operand0.labelName);
}
static _INSTR_PRINT_FUNC_LABEL_(MOVE_IMM_TO_REG_FORMAT)
{
    //null; equl to li
}
static _INSTR_PRINT_FUNC_LABEL_(JR_TO_REG_FORMAT)
{
    printf("jr $%s\n", get_reg_tag(_this->operand0.regIdx));
}
static _INSTR_PRINT_FUNC_LABEL_(BEQ_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    printf("beq $%s, $%s, %s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx), _this->operand2.labelName);
}
static _INSTR_PRINT_FUNC_LABEL_(BNE_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    printf("bne $%s, $%s, %s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx), _this->operand2.labelName);
}
static _INSTR_PRINT_FUNC_LABEL_(BGT_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    printf("bgt $%s, $%s, %s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx), _this->operand2.labelName);
}
static _INSTR_PRINT_FUNC_LABEL_(BLT_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    printf("blt $%s, $%s, %s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx), _this->operand2.labelName);
}
static _INSTR_PRINT_FUNC_LABEL_(BGE_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    printf("bge $%s, $%s, %s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx), _this->operand2.labelName);
}
static _INSTR_PRINT_FUNC_LABEL_(BLE_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    printf("ble $%s, $%s, %s\n", get_reg_tag(_this->operand0.regIdx), get_reg_tag(_this->operand1.regIdx), _this->operand2.labelName);
}

//rebuild functions declearation
static _INSTR_REBUILD_FUNC_LABEL_(LABEL_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.labelName = va_arg(ap, char *);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(LI_IMM_TO_REG_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.immediate = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(MOVE_REG_TO_REG_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(ADD_REG_AND_IMM_TO_REG_FORMAT)
{
    va_list(ap);
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    _this->operand2.immediate = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(ADD_REG_AND_REG_TO_REG_FORMAT)
{
    va_list(ap);
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    _this->operand2.regIdx = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(SUB_REG_AND_REG_TO_REG_FORMAT)
{
    va_list(ap);
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    _this->operand2.regIdx = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(MUL_REG_AND_REG_TO_REG_FORMAT)
{
    va_list(ap);
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    _this->operand2.regIdx = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(DIV_REG_TO_REG_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(MFLO_REG_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(LW_REG_FROM_ADDRESS_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.address.offset = va_arg(ap, int);
    _this->operand1.address.basicRegIdx = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(SW_REG_TO_ADDRESS_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.address.offset = va_arg(ap, int);
    _this->operand1.address.basicRegIdx = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(J_TO_LABEL_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.labelName = va_arg(ap, char *);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(JAL_LABEL_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.labelName = va_arg(ap, char *);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(MOVE_IMM_TO_REG_FORMAT)
{
    //NULL
}
static _INSTR_REBUILD_FUNC_LABEL_(JR_TO_REG_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(BEQ_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    _this->operand2.labelName = va_arg(ap, char *);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(BNE_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    _this->operand2.labelName = va_arg(ap, char *);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(BGT_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    _this->operand2.labelName = va_arg(ap, char *);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(BLT_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    _this->operand2.labelName = va_arg(ap, char *);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(BGE_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    _this->operand2.labelName = va_arg(ap, char *);
    va_end(ap);
}
static _INSTR_REBUILD_FUNC_LABEL_(BLE_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    va_list ap;
    va_start(ap, _this);
    _this->operand0.regIdx = va_arg(ap, int);
    _this->operand1.regIdx = va_arg(ap, int);
    _this->operand2.labelName = va_arg(ap, char *);
    va_end(ap);
}

#define _ASSIGN_FUNCTION_(idx)                                                \
    do                                                                        \
    {                                                                         \
        static_instr_formats[idx].instr_print = _INSTR_PRINT_FUNC_NAME_(idx); \
        static_instr_formats[idx].rebuild = _INSTR_REBUILD_FUNC_NAME_(idx);   \
    } while (0)

//creator functions
_INSTR_CREATOR_FUNC_LABEL_(LABEL_FORMAT)
{
    _ASSIGN_FUNCTION_(LABEL_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(LI_IMM_TO_REG_FORMAT)
{
    _ASSIGN_FUNCTION_(LI_IMM_TO_REG_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(MOVE_REG_TO_REG_FORMAT)
{
    _ASSIGN_FUNCTION_(MOVE_REG_TO_REG_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(ADD_REG_AND_IMM_TO_REG_FORMAT)
{
    _ASSIGN_FUNCTION_(ADD_REG_AND_IMM_TO_REG_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(ADD_REG_AND_REG_TO_REG_FORMAT)
{
    _ASSIGN_FUNCTION_(ADD_REG_AND_REG_TO_REG_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(SUB_REG_AND_REG_TO_REG_FORMAT)
{
    _ASSIGN_FUNCTION_(SUB_REG_AND_REG_TO_REG_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(MUL_REG_AND_REG_TO_REG_FORMAT)
{
    _ASSIGN_FUNCTION_(MUL_REG_AND_REG_TO_REG_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(DIV_REG_TO_REG_FORMAT)
{
    _ASSIGN_FUNCTION_(DIV_REG_TO_REG_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(MFLO_REG_FORMAT)
{
    _ASSIGN_FUNCTION_(MFLO_REG_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(LW_REG_FROM_ADDRESS_FORMAT)
{
    _ASSIGN_FUNCTION_(LW_REG_FROM_ADDRESS_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(SW_REG_TO_ADDRESS_FORMAT)
{
    _ASSIGN_FUNCTION_(SW_REG_TO_ADDRESS_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(J_TO_LABEL_FORMAT)
{
    _ASSIGN_FUNCTION_(J_TO_LABEL_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(JAL_LABEL_FORMAT)
{
    _ASSIGN_FUNCTION_(JAL_LABEL_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(MOVE_IMM_TO_REG_FORMAT)
{
    _ASSIGN_FUNCTION_(MOVE_IMM_TO_REG_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(JR_TO_REG_FORMAT)
{
    _ASSIGN_FUNCTION_(JR_TO_REG_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(BEQ_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    _ASSIGN_FUNCTION_(BEQ_REG_AND_REG_TO_ADDRESS_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(BNE_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    _ASSIGN_FUNCTION_(BNE_REG_AND_REG_TO_ADDRESS_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(BGT_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    _ASSIGN_FUNCTION_(BGT_REG_AND_REG_TO_ADDRESS_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(BLT_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    _ASSIGN_FUNCTION_(BLT_REG_AND_REG_TO_ADDRESS_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(BGE_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    _ASSIGN_FUNCTION_(BGE_REG_AND_REG_TO_ADDRESS_FORMAT);
}
_INSTR_CREATOR_FUNC_LABEL_(BLE_REG_AND_REG_TO_ADDRESS_FORMAT)
{
    _ASSIGN_FUNCTION_(BLE_REG_AND_REG_TO_ADDRESS_FORMAT);
}

void initial_instr_module()
{
    _MAKE_INSTR_(LABEL_FORMAT);
    _MAKE_INSTR_(LI_IMM_TO_REG_FORMAT);
    _MAKE_INSTR_(MOVE_REG_TO_REG_FORMAT);
    _MAKE_INSTR_(ADD_REG_AND_IMM_TO_REG_FORMAT);
    _MAKE_INSTR_(ADD_REG_AND_REG_TO_REG_FORMAT);
    _MAKE_INSTR_(SUB_REG_AND_REG_TO_REG_FORMAT);
    _MAKE_INSTR_(MUL_REG_AND_REG_TO_REG_FORMAT);
    _MAKE_INSTR_(DIV_REG_TO_REG_FORMAT);
    _MAKE_INSTR_(MFLO_REG_FORMAT);
    _MAKE_INSTR_(LW_REG_FROM_ADDRESS_FORMAT);
    _MAKE_INSTR_(SW_REG_TO_ADDRESS_FORMAT);
    _MAKE_INSTR_(J_TO_LABEL_FORMAT);
    _MAKE_INSTR_(JAL_LABEL_FORMAT);
    _MAKE_INSTR_(MOVE_IMM_TO_REG_FORMAT);
    _MAKE_INSTR_(JR_TO_REG_FORMAT);
    _MAKE_INSTR_(BEQ_REG_AND_REG_TO_ADDRESS_FORMAT);
    _MAKE_INSTR_(BNE_REG_AND_REG_TO_ADDRESS_FORMAT);
    _MAKE_INSTR_(BGT_REG_AND_REG_TO_ADDRESS_FORMAT);
    _MAKE_INSTR_(BLT_REG_AND_REG_TO_ADDRESS_FORMAT);
    _MAKE_INSTR_(BGE_REG_AND_REG_TO_ADDRESS_FORMAT);
    _MAKE_INSTR_(BLE_REG_AND_REG_TO_ADDRESS_FORMAT);
}