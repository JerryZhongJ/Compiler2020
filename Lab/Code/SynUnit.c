#include"common.h"

SynUnit* init(SynType type){
	SynUnit* unit = (SynUnit*)malloc(sizeof(SynUnit));
	unit->syn_type = type;
	unit -> lineno = 0;
	unit -> prod_num = 0;
}

void appendSyn(SynUnit* unit, SynUnit* child){
	unit -> prod_type[unit -> prod_num] = SYN;
	unit -> prod[unit -> prod_num].child = child;
	unit -> prod_num++;
}
void appendLex(SynUnit* unit, LexType type){
	unit -> prod_type[unit->prod_num] = LEX;
	unit -> prod[unit -> prod_num].lex_type = type;
	unit -> prod_num++;
}

void appendLexINT(SynUnit* unit, LexType type, int ival){
	assert(type == INT);
	unit->prod[unit->prod_num].ival = ival;
	appendLex(unit, type);
}
void appendLexFLOAT(SynUnit* unit, LexType type, int fval){
	assert(type == FLOAT);
	
	unit->prod[unit->prod_num].fval = fval;
	appendLex(unit, type);
}
void appendLexID(SynUnit* unit, LexType type, char* id){
	assert(type == ID);
	unit->prod[unit->prod_num].id = id;
	appendLex(unit, type);
}
void appendLexTYPE(SynUnit* unit, LexType type, bool iorf){
	assert(type == TYPE);
	unit->prod[unit->prod_num].iorf = iorf;
	appendLex(unit, type);
}