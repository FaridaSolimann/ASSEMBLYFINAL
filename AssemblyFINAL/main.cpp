#include<iostream>
#include<fstream>
#include<vector>
#include"Globals.h"
#include<string>
#include"RFormat.h"
#include <sstream>
#include"IFormat.h"
#include<cstring>
#include"JFormat.h"
int PC;
using namespace std;
//vector<string> labels;
vector<string> psuedoInst;
void openFile(string name);
void callInst();
void disassemble();
void pseudofy();

vector <unsigned int> binaryList;
vector<string> InstructionString;
vector <Instruction*> InstructionList;

void main()
{
	/*
	bool pseudoFlag;
	//string s;
	openFile("meh"); //opening the file and saving it in Binary List
	callInst(); // looping over the binary list and adding the inst pointers to InstructionList
	Instruction** PC; //pointing the program counter to the instructionList
	PC= &InstructionList[0];
	//SIMMULATION??????????????/
	if(pseudoFlag)
	pseudofy();
	//DISPLAYING*/

	string file = "TESTPROJECT.bin";
	openFile(file);
	callInst();
	disassemble();
	//pseudofy();
	for (int i = 0; i < InstructionString.size(); i++)
	cout << InstructionString[i] << endl;

	//for (int i = 0; i < psuedoInst.size(); i++)
		//cout << psuedoInst[i] << endl;

	system("pause");

}

void callInst()
{
	unsigned int OPC;
	for (int i = 0; i < binaryList.size(); i++)
	{

		Instruction*pointer;
		OPC = binaryList[i] >> 26;
		//OPC = OPC >> 26;
		switch (OPC)
		{
		case 0:
			//pointer = new RFormat(binaryList[i], labels);
			pointer = new RFormat(binaryList[i]);
			InstructionList.push_back(pointer);
			break;
		case 2:
		case 3:
			pointer = new JFormat(binaryList[i]);
			InstructionList.push_back(pointer);
			break;
		default:
			pointer = new IFormat(binaryList[i]);
			InstructionList.push_back(pointer);

		}

		//PC = (*InstructionList.back()).returnPC();

		//InstructionString =( *(InstructionList[InstructionList.size()])).returnInstString();//taking the final instruction string from globals file (whcih is included in instruction)
		//we dont need the above line .. we have function disassemble
	}

}
void disassemble()
{
	for (int i = 0; i < InstructionList.size(); i++)
	{
		InstructionString.push_back((*InstructionList[i]).instString); // Accessing instString(which contains the dissassembeled string) in every instruction and pushes it back in InstructionString vector for further use in pseudo
	}
}
void Simulate()
{
	for (int i = 0; i < InstructionList.size(); i++)
	{
		InstructionList[i]->run(); // calls function run which calls whatever function stored in the function pointer
		i = PC - 400000;  // change to initial hexadecimal value of PC
	}
}

void pseudofy()
{
	for (int i = 0; i < InstructionString.size(); i++)
	{
		string temp;
		int index;
		string s = InstructionString[i];
		index = s.find(' ');
		string fxName = s.substr(0, index);
		temp = s;
		temp.erase(0, index);
		index = temp.find(',');
		string reg1 = temp.substr(0, index);
		temp.erase(0, index + 1);
		index = temp.find(',');
		string reg2 = temp.substr(0, index);
		temp.erase(0, index + 1);
		if (fxName == "addi")
		{

			int mostsig = atoi(temp.c_str()) >> 15;
			if (mostsig == 1)
			{
				index = s.find(' ');
				temp = s.erase(0, index + 1);
				psuedoInst.push_back("subi" + ' ' + temp);

			}
			if (reg2 == "$0")
			{
				psuedoInst.push_back("li " + ' ' + reg1 + ',' + temp);
			}

		}

		else
		if ((fxName == "add") || (fxName == "addu"))
		{

			if ((reg2 == "$0") && (temp == "0"))

				psuedoInst.push_back("clear " + reg1);
			else

			if (reg2 == "$0")
				psuedoInst.push_back("move" + ' ' + reg1 + ',' + temp);
			else
			if (temp == "$0")
				psuedoInst.push_back("move" + ' ' + reg1 + ',' + reg2);


		}
		else

		if (fxName == "nor")
		{
			if (temp == "$0")
				psuedoInst.push_back("not " + ' ' + reg1 + "," + reg2);
		}

		else

		if (fxName == "lui")
		{
			string test = test.substr(0, InstructionString[i + 1].find(' '));
			if (test == "or")
			{

				string upperBits = to_string((*(InstructionList[i])).signedImm); // getting the actual instruction (*InstructionList(i)) then getting the signedImm value
				string lowerBits = to_string((*(InstructionList[i])).signedImm);
				upperBits = upperBits + lowerBits;
				i += 1;
				psuedoInst.push_back("la " + ',' + reg1 + "," + upperBits);
				i += 1;

			}
			string tyf = InstructionString[i + 1];
			string test2 = tyf.substr(0, tyf.find(' ')+1);
			if (test2 == "ori ")
			{

				string upperBits = to_string((*(InstructionList[i])).signedImm); // getting the actual instruction (*InstructionList(i)) then getting the signedImm value
				string lowerBits = to_string((*(InstructionList[i])).signedImm);
				upperBits = upperBits + lowerBits;
				//i += 1;
				string EHDA = "la " +  reg1 + "," + upperBits;
				psuedoInst.push_back("la " + reg1 + "," + upperBits);
				InstructionString[i + 1] = "";
				//i++;
			}
		}

		else

		if (fxName == "srl")
		{
			if ((s.substr(0, InstructionString[i + 1].find(' ')) == "sll") && (s.substr(0, InstructionString[i + 2].find(' ')) == "or"))
			{
				i += 2;
				string temp2;
				temp2 = "ror " + reg2, "," + temp;
				psuedoInst.push_back(temp2);

			}
		}
		else

		if (fxName == "slt")
		{
			string temps = InstructionString[i + 1].erase(0, (InstructionString[i + 1].find(",")));//getting the label tbc..
			temps = InstructionString[i + 1].erase(0, (InstructionString[i + 1].find(",")));//getting the label
			if ((s.substr(0, InstructionString[i + 1].find(' ')) == "beq") && (s.substr(InstructionString[i + 1].find(' '), InstructionString[i + 1].find(',')) == reg1))
			{
				psuedoInst.push_back("bge " + reg2 + "," + temp + "," + temps);
				i += 1;
			}
			else
			{
				if (s.substr(InstructionString[i + 1].find(' '), InstructionString[i + 1].find(',')) == reg1)
				{
					psuedoInst.push_back("blt " + reg2 + "," + temp + "," + temps);
					i += 1;
				}

			}
		}
		else
		if (InstructionString[i] != "")
			psuedoInst.push_back(InstructionString[i]);
			

	}
}
void openFile(string name)         // OPEN FILE KEDA!!!!!
{
	ifstream x;
	x.open(name.c_str(), ios::binary | ios::in);
	if (x.fail()){
		cout << "BATEE5";
	}

	unsigned int chara;
	while (!x.eof())
	{
		x.read((char*)&chara, 4);
		binaryList.push_back(chara);
	}


}
