/*
本模块提供了必要的寄存器和栈内存资源的管理功能和寄存器名称转换功能
使用前使用initial_storage_module()初始化模块
使用后使用free_storage_module()释放内存
提供了4个API函数进行操作
*/

#ifndef __STORAGE_H__
#define __STORAGE_H__

#define R_ZERO 0
#define R_AT 1
#define R_V0 2
#define R_V1 3
#define R_A0 4
#define R_A1 5
#define R_A2 6
#define R_A3 7
#define R_T0 8
#define R_T1 9
#define R_T2 10
#define R_T3 11
#define R_T4 12
#define R_T5 13
#define R_T6 14
#define R_T7 15
#define R_S0 16
#define R_S1 17
#define R_S2 18
#define R_S3 19
#define R_S4 20
#define R_S5 21
#define R_S6 22
#define R_S7 23
#define R_T8 24
#define R_T9 25
#define R_K0 26
#define R_K1 27
#define R_GP 28
#define R_SP 29
#define R_S8 30
#define R_RA 31

const char* reg_tags[] = {
    "zero",
    "at",
    "v0","v1",
    "a0","a1","a2","a3",
    "t0","t1","t2","t3","t4","t5","t6","t7",
    "s0","s1","s2","s3","s4","s5","s6","s7",
    "t8","t9",
    "k0","k1",
    "gp",
    "sp",
    "s8",
    "ra"
};
const char*get_reg_tag(int idx);

void initial_storage_module();
void free_storage_module();
int check_attach_state(int is_temp_var,int _var_,int *is_in_reg);//check where the var is record return offset or reg idx,"is_in_reg can be NULL",return -1 if can not find target
int try_attach_reg(int temp_var_,int *ok);//try to get an unoccupied register idx and return the idx,if it failed ,return the offset by sp int current frame
int dis_attach_reg(int temp_var_);//return 0 if failed
int attach_memory(int var_,int size);//get a series of memroy block and return the start address(offset by sp)
#endif//__STORAGE_H__