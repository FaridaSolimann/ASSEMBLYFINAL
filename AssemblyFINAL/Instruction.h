#include <iostream>
#include"globals.h"
//Globals x;
#ifndef Instruction_H
#define Instruction_H

class Instruction
{
public:
	static Globals x;

	//Globals x;
	string instString;
	vector<string> returnInstString() /// I dont think we need this anymore
	{
		return x.InstructionString;
	}
	void run();
	vector<int> returnLabels()  ///TO BE CONSTINUEDDDDD........[WALAHY MAFAHEM DH BEYE3MEL EH]
	{
		return x.labels;
	}
	int returnPC()
	{
		return x.PC;
	}
	Instruction(unsigned int); //constructor that takes the binary number
	string toString() const;
	friend ostream& operator<<(ostream&, const Instruction&);
	int signedImm;
protected:
	const unsigned int instWord;
	unsigned int opcode;
	//int PC;


};

#endif