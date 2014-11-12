#include <iostream>
#include<string>
#include<vector>
#include"Instruction.h"
using namespace std;

Instruction::Instruction(unsigned int n) : instWord(n) // initializer list
{

	opcode = instWord >> 26;

}
void Instruction::run()
{
	//this->myFunctionPointer();
}

Globals Instruction::x;