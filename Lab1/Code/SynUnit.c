#include"common.h"
#include<stdlib.h>
#include<assert.h>
//#include<stdio.h>

SynUnit* init(SynType type, int line){
	SynUnit* unit = (SynUnit*)malloc(sizeof(SynUnit));
	unit->syn_type = type;
	unit -> lineno = line;
	unit -> symbol_num = 0;
}

void appendSyn(SynUnit* unit, SynUnit* child){
	unit -> symbol_type[unit -> symbol_num] = SYN;
	unit -> symbol[unit -> symbol_num].child = child;
	unit -> symbol_num++;
}
void appendLex(SynUnit* unit, LexType type){
	unit -> symbol_type[unit->symbol_num] = LEX;
	unit -> symbol[unit -> symbol_num].lex_type = type;
	unit -> symbol_num++;
}

void appendLexINT(SynUnit* unit, LexType type, int ival){
	assert(type == INT);
	unit->symbol[unit->symbol_num].ival = ival;
	appendLex(unit, type);
}
void appendLexFLOAT(SynUnit* unit, LexType type, int fval){
	assert(type == FLOAT);
	
	unit->symbol[unit->symbol_num].fval = fval;
	appendLex(unit, type);
}
void appendLexID(SynUnit* unit, LexType type, char* id){
	assert(type == ID);
	unit->symbol[unit->symbol_num].id = id;
	appendLex(unit, type);
}
void appendLexTYPE(SynUnit* unit, LexType type, bool iorf){
	//printf("%d %d\n", type, TYPE);
	assert(type == TYPE);
	unit->symbol[unit->symbol_num].iorf = iorf;
	appendLex(unit, type);
}