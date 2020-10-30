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
	unit -> symbol[unit -> symbol_num].lex_child = (LexUnit*) malloc(sizeof(LexUnit));
	unit -> symbol_num++;
}
void appendLex(SynUnit* unit, LexType type){
	unit -> symbol_type[unit->symbol_num] = LEX;
	unit -> symbol[unit -> symbol_num].lex_child->lex_type = type;
	unit -> symbol_num++;
}

void appendLexINT(SynUnit* unit, LexType type, int ival){
	assert(type == INT);
	appendLex(unit, type);
	unit->symbol[unit->symbol_num - 1].lex_child -> ival = ival;
	
}
void appendLexFLOAT(SynUnit* unit, LexType type, float fval){
	assert(type == FLOAT);
	appendLex(unit, type);
	unit->symbol[unit->symbol_num - 1].lex_child->fval = fval;
	
}
void appendLexID(SynUnit* unit, LexType type, char* id){
	assert(type == ID);
	appendLex(unit, type);
	unit->symbol[unit->symbol_num - 1].lex_child->id = id;
	
}
void appendLexTYPE(SynUnit* unit, LexType type, bool iorf){
	//printf("%d %d\n", type, TYPE);
	assert(type == TYPE);
	appendLex(unit, type);
	unit->symbol[unit->symbol_num - 1].lex_child->iorf = iorf;
	
}