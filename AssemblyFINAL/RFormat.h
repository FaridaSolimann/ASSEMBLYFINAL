#ifndef RFORMAT_H
#define RFORMAT_H
#include <iostream>
#include "Instruction.h"

class RFormat :public Instruction
{
public:
	RFormat(unsigned int); //constructor
	void decodeInstDisassemble();
	void addDisassemble();
	void adduDisassemble();
	void andDisassemble();
	void jrDisassemble();
	void sltDisassemble();
	void sltuDisassemble();
	void sllDisassemble();
	void srlDisassemble();
	void subDisassemble();
	void subuDisassemble();
	void decodeInst();
	void andSimulate();
	void adduSimulate();
	void addSimulate();
	void jrSimulate();
	void sllSimulate();
	void subSimulate();
	void subuSimulate();
	void sltuSimulate();
	void sltSimulate();
	void srlSimulate();

private:
	unsigned int func, shamt, rd, rt, rs;
	void(RFormat::*myFunctionPointer)();
};





#endif