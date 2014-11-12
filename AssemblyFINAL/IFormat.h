#ifndef IFormat_h
#define IFormat_h
#include "Instruction.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class IFormat : public Instruction
{
public:
	IFormat(unsigned int);			// constructor
	~IFormat();				// destructor
	void decodeInst();
	void addiDisassemble();
	void luiDisassemble();
	void addiuDisassemble();
	void andiDisassemble();
	void beqDisassemble();
	void bneDisassemble();
	void lwDisassemble();
	void oriDisassemble();
	void sltiDisassemble();
	void sbDisassemble();
	void shDisassemble();
	void swDisassemble();

	void addiSimulate();
	void luiSimulate();
	void addiuSimulate();
	void andiSimulate();
	void beqSimulate();
	void bneSimulate();
	void lwSimulate();
	void oriSimulate();
	void sltiSimulate();
	void sbSimulate();
	void shSimulate();
	void swSimulate();
	// signed Immediate


private:
	unsigned int rt;    //target	
	unsigned int rs;		//source	
	unsigned int imm;	//immediate

	//void(IFormat::*myFunctionPointer)();

	void(IFormat::*myFunctionPointer)();
};

#endif