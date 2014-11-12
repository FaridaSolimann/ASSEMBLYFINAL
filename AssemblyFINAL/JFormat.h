#ifndef JFormat_h
#define JFormat_h
#include <iostream>
#include<string>
#include<vector>
#include"Instruction.h"
#include"Globals.h"

using namespace std;

class JFormat :public Instruction
{
private:
	unsigned int add;
	unsigned int opCode;
	void(JFormat::*myFunctionPointer)();

public:
	JFormat(unsigned int n) :Instruction(n)
	{
		int first4digits, xx;
		string a, b;
		first4digits = x.PC && 15;
		xx = instWord && 4294967295;
		add = xx << 2;
		a = to_string(first4digits);
		b = to_string(add);
		a = a + b;

		add = atoi(a.c_str());
		decodeInstruction();

	}

	void decodeInstruction()
	{

		opCode = instWord >> 26;
		if (opCode == 2)
		{
			jDisassemble();
			myFunctionPointer = &JFormat::jSimulate;
		}

		if (opcode == 3)
		{
			jalDisassemble();
			myFunctionPointer = &JFormat::jalSimulate;
		}

		else
			cout << "unknown instruction" << endl;


	}

	void jDisassemble()
	{
		string lName = to_string(x.labels.size() - 1);
		lName = "label" + lName;
		x.labels.push_back(add);
		instString = "j " + lName;

	}

	void jalDisassemble()
	{
		string lName = to_string(x.labels.size() - 1);
		lName = "label" + lName;
		x.labels.push_back(add);
		instString = "jal" + lName;
	}

	void jSimulate()
	{
		x.PC = add;
	}

	void jalSimulate()
	{
		x.PC = add;
		x.registers[31].value = x.PC + 8;
	}



};
#endif