#include "IFormat.h"
#include"Globals.h"

IFormat::IFormat(unsigned int n) : Instruction(n)
{
	rt = (instWord >> 16) & 0x1f;
	rs = (instWord >> 21) & 0x1f;
	imm = (instWord & 0x0000FFFF);
	decodeInst();

}

void IFormat::decodeInst()
{
	switch (opcode)
	{
	case 0x8:			addiDisassemble();
		myFunctionPointer = &IFormat::addiSimulate;
		break;
	case 0x9:			addiuDisassemble();
		myFunctionPointer = &IFormat::addiuSimulate;

		break;
	case 0xc:			andiDisassemble();
		myFunctionPointer = &IFormat::andiSimulate;

		break;
	case 0x4:			beqDisassemble();
		myFunctionPointer = &IFormat::beqSimulate;
		break;

		case 0x5:			bneDisassemble();
		//myFunctionPointer = &IFormat::bneSimulate;
		break;

	case 0xf:			luiDisassemble();
		//myFunctionPointer = &IFormat::luiSimulate;
		break;
	case 0x23:			lwDisassemble();
		myFunctionPointer = &IFormat::lwSimulate;

		break;
	case 0xd:			oriDisassemble();
		myFunctionPointer = &IFormat::oriSimulate;
		break;


	case 0xa:
		sltiDisassemble();
		myFunctionPointer = &IFormat::sltiSimulate;
		break;

	case 0x28:			sbDisassemble();
		myFunctionPointer = &IFormat::sbSimulate;
		break;


	case 0x29:			shDisassemble();
		myFunctionPointer = &IFormat::shSimulate;
		break;


	case 0x2b:			swDisassemble();
		myFunctionPointer = &IFormat::swSimulate;
		break;

	default:
		instString = "Unknown Instrution";
		//return instString;
	}
}

void IFormat::addiDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	instString += "addi " + x.registers[rs].name + "," + x.registers[rt].name + "," + to_string(signedImm);
}

void IFormat::luiDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	instString += "lui " + x.registers[rs].name + "," + x.registers[rt].name + "," + to_string(signedImm);

}
void IFormat::addiuDisassemble()
{
	instString += "addiu" + x.registers[rs].name + "," + x.registers[rt].name + "," + to_string(imm);
}

void IFormat::andiDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	instString += "andi" + x.registers[rs].name + "," + x.registers[rt].name + "," + to_string(signedImm);
}

void IFormat::beqDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	x.labels.push_back(signedImm);
	instString += "beq" + x.registers[rs].name + "," + x.registers[rt].name + "," + " label" + to_string(x.labels.size()-1);
}

void IFormat::bneDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	x.labels.push_back(signedImm);
	instString += "bne" + x.registers[rs].name + "," + x.registers[rt].name + "," + " label" + to_string(x.labels.size() - 1);
}

void IFormat::lwDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	instString += "lw" + x.registers[rt].name + "," + to_string(signedImm) + "(" + x.registers[rs].name + ")";
}

void IFormat::oriDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	instString += "ori " + x.registers[rs].name + "," + x.registers[rt].name + "," + to_string(signedImm);
}

void IFormat::sltiDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	instString += "slti" + x.registers[rs].name + "," + x.registers[rt].name + "," + to_string(signedImm);
}

void IFormat::sbDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	instString += "sb" + x.registers[rt].name + "," + to_string(signedImm) + "(" + x.registers[rs].name + ")";

}


void IFormat::shDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	instString += "sh" + x.registers[rt].name + "," + to_string(signedImm) + "(" + x.registers[rs].name + ")";

}

void IFormat::swDisassemble()
{
	signedImm = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;
	instString += "sw" + x.registers[rt].name + "," + to_string(signedImm) + "(" + x.registers[rs].name + ")";

}
void IFormat::addiSimulate()
{

	x.registers[rt].value = x.registers[rt].value + signedImm;

	if (x.registers[rt].value > 4294967295) //2^32
	{
		x.registers[rt].value = x.registers[rt].value * -1; //????
	}
	x.PC += 4; //fake pc
}

void IFormat::addiuSimulate()
{

	x.registers[rt].value = abs(x.registers[rt].value) + abs(signedImm);          // should be zero extended!!!

	//if (x.registers[rt].value > 4294967295) //2^32
	//{
	//	x.registers[rt].value = x.registers[rt].value * -1; //????
	//}
	x.PC += 4; //fake pc
}

void IFormat::swSimulate()
{
	x.M[(x.registers[rs].value + signedImm)] = x.registers[rt].value;
	x.PC += 4;

}
void IFormat::shSimulate()
{
	x.M[x.registers[rs].value + signedImm] = x.registers[rt].value;
	x.PC += 4;
}
void IFormat::andiSimulate()
{
	x.PC += 4;
	x.registers[rt].value = x.registers[rs].value & signedImm; // zero extended?
}
void IFormat::oriSimulate()
{
	x.registers[rt].value = x.registers[rs].value | signedImm;
	x.PC += 4;
}
void IFormat::sbSimulate()
{
	x.M[x.registers[rs].value + signedImm] = x.registers[rt].value;
	x.PC += 4;
}

void IFormat::sltiSimulate()
{
	x.registers[rt].value = (x.registers[rs].value < signedImm) ? 1 : 0;
	x.PC += 4;
}

void IFormat::lwSimulate()
{
	x.registers[rt].value = x.M[x.registers[rs].value + signedImm];      // assuming we have a vector called memory
	x.PC += 4;
}

void IFormat::beqSimulate()
{
	if (x.registers[rs].value == x.registers[rt].value)
		x.PC = x.PC + 4 + signedImm; // actualPC (pointer) or simulated PC? (signedImm here means address)
}