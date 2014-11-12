#include <iostream>
#include"RFormat.h"
#include"Globals.h"
#include <string>
using namespace std;

RFormat::RFormat(unsigned int n) : Instruction(n)
{
	func = instWord & 0x3F;
	shamt = (instWord >> 6) & 0x1f;
	rd = (instWord >> 11) & 0x1f;
	rt = (instWord >> 16) & 0x1f;
	rs = (instWord >> 21) & 0x1f;
	decodeInst();

}

void RFormat::decodeInst()
{
	switch (func)
	{
	case 0x20:			addDisassemble();
		myFunctionPointer = &RFormat::addSimulate;
		break;
	case 0x21:			adduDisassemble();
		myFunctionPointer = &RFormat::adduSimulate;

		break;
	case 0x24:			andDisassemble();
		myFunctionPointer = &RFormat::andSimulate;

		break;
	case 0x08:			jrDisassemble();
		myFunctionPointer = &RFormat::jrSimulate;
		break;

	case 0x2a:			sltDisassemble();
		myFunctionPointer = &RFormat::sltSimulate;
		break;
	case 0x2b:			sltuDisassemble();
		myFunctionPointer = &RFormat::sltuSimulate;
		break;

		//break;
	case 0x00:			sllDisassemble();
		myFunctionPointer = &RFormat::sllSimulate;

		break;
	case 0x02:			srlDisassemble();
		myFunctionPointer = &RFormat::srlSimulate;
		break;


	case 0x22:			subDisassemble();
		myFunctionPointer = &RFormat::subSimulate;
		break;

	case 0x23:			subuDisassemble();
		myFunctionPointer = &RFormat::subuSimulate;
		break;



	default:
		instString = "Unknown Intruction";
		//cout << instString;
	}
}

void RFormat::addDisassemble()
{
	instString = "add" + string(" ") + x.registers[rd].name + string(",") + x.registers[rs].name + string(",") + x.registers[rt].name; // vector of rd
}
void RFormat::adduDisassemble()
{
	instString = "addu" + string(" ") + x.registers[rd].name + string(",") + x.registers[rs].name + string(",") + x.registers[rt].name;
}
void RFormat::adduSimulate()
{
	x.registers[rd].value = x.registers[rs].value + x.registers[rt].value;
}

void RFormat::addSimulate()
{
	int ans = x.registers[rs].value + x.registers[rt].value;

	int temp = x.registers[rs].value ^ x.registers[rt].value;

	if (temp > 0)
	{
		temp = ans ^ x.registers[rs].value;
		if (temp > 0)
			cout << "overflow in register" << x.registers[rd].name << endl;
	}

	x.registers[rd].value = x.registers[rs].value + x.registers[rt].value;
}
void RFormat::andDisassemble()
{
	instString = "and" + string(" ") + x.registers[rd].name + string(",") + x.registers[rs].name + string(",") + x.registers[rt].name;
}
void RFormat::andSimulate()
{
	x.registers[rd].value = x.registers[rs].value & x.registers[rt].value;    // .value??????
}
void RFormat::jrDisassemble()
{
	instString = "jr" + string(" ") + x.registers[rs].name;
}
void RFormat::jrSimulate()
{
	x.PC = x.registers[rs].value;
}
void RFormat::sltDisassemble()
{
	instString = "slt" + string(" ") + x.registers[rd].name + string(",") + x.registers[rs].name + string(",") + x.registers[rt].name;
}
void RFormat::sltSimulate()
{
	x.registers[rd].value = (x.registers[rs].value < x.registers[rt].value) ? 1 : 0;
	x.PC += 4;
}
void RFormat::sltuSimulate()
{
	x.registers[rd].value = (abs(x.registers[rs].value) < abs(x.registers[rt].value)) ? 1 : 0;
	x.PC += 4;
}
void RFormat::sltuDisassemble()

{
	instString = "sltu" + string(" ") + x.registers[rd].name + string(",") + x.registers[rs].name + string(",") + x.registers[rt].name;
}
void RFormat::sllDisassemble()
{
	instString = "sll" + string(" ") + x.registers[rd].name + string(",") + x.registers[rt].name + string(",") + to_string(shamt);
	//cout << instString;
}
void RFormat::sllSimulate()
{
	x.registers[rd].value = x.registers[rt].value << shamt;
	x.PC += 4;
}
void RFormat::srlDisassemble()
{
	instString = "srl" + string(" ") + x.registers[rd].name + string(",") + x.registers[rt].name + string(",") + to_string(shamt);
	//cout << instString;
	x.PC += 4;
}
void RFormat::srlSimulate()
{
	x.registers[rd].name = x.registers[rt].value >> shamt;    
	x.PC += 4;
}
void RFormat::subDisassemble()
{
	instString = "sub" + string(" ") + x.registers[rd].name + string(",") + x.registers[rs].name + string(",") + x.registers[rt].name;
	x.PC += 4;
}
void RFormat::subSimulate()
{
	x.registers[rd].value = x.registers[rs].value - x.registers[rt].value;
	x.PC += 4;
}

void RFormat::subuSimulate()
{
	x.registers[rd].value = x.registers[rs].value - x.registers[rt].value;
	x.PC += 4;
}
void RFormat::subuDisassemble()
{
	instString = "subu" + string(" ") + x.registers[rd].name + string(",") + x.registers[rs].name + string(",") + x.registers[rt].name;
	cout << instString;
	x.PC += 4;
}