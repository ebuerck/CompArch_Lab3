#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include "mu-helper.h"
#include "mu-mips.h"


void getSingleInstruct(MIPS* instrAddress){
	uint32_t instr = mem_read_32(CURRENT_STATE.PC);

	char string[9];
	sprintf(string,"%08x", instr);

	char fullbinary[33];
	fullbinary[0] = '\0';

	for(int i = 0; i < 9; i++)
	{
		strcat(fullbinary, hex_to_binary(string[i]));
	}

	switch(FindFormat(fullbinary)) {
		case 'R': {
			returnRFormat(fullbinary,instrAddress);
			break;
		}
		case 'I': {
			returnIFormat(fullbinary,instrAddress);
			break;
		}
		case 'J': {
			returnJFormat(fullbinary,instrAddress);
			break;
		}
		default: {
			printf("You messed up.\n");
			break;
		}
	}
}


char* hex_to_binary(char Hexdigit)
{
	if(isalpha(Hexdigit))
		Hexdigit = toupper(Hexdigit);

	switch (Hexdigit)
	{
	case ' ':
		return "0000";
	case '0':
		return "0000";
	case '1':
		return "0001";
	case '2':
		return "0010";
	case '3':
		return "0011";
	case '4':
		return "0100";
	case '5':
		return "0101";
	case '6':
		return "0110";
	case '7':
		return "0111";
	case '8':
		return "1000";
	case '9':
		return "1001";
	case 'A':
		return "1010";
	case 'B':
		return "1011";
	case 'C':
		return "1100";
	case 'D':
		return "1101";
	case 'E':
		return "1110";
	case 'F':
		return "1111";
	default:
		return "\0";
		break;
	}
}

char FindFormat(char* instruction)
{
	char opcode[7];
	strncpy(opcode,instruction, 6);
	opcode[6] = '\0';

	if(!strcmp(opcode, "000000"))
	{
		return 'R';
	}
	else if (!strcmp(opcode, "000010") || !strcmp(opcode, "000011"))
	{
		return 'J';
	}
	else
	{
		return 'I';
	}
}

char* GetRFunction(char* instruction)
{
	if(!strcmp(instruction, "100000"))
	{
		return "ADD";
	}
	if(!strcmp(instruction, "100001"))
	{
		return "ADDU";
	}
	if(!strcmp(instruction, "100010"))
	{
		return "SUB";
	}
	if(!strcmp(instruction, "100011"))
	{
		return "SUBU";
	}
	if(!strcmp(instruction, "011000"))
	{
		return "MULT";
	}
	if(!strcmp(instruction, "011001"))
	{
		return "MULTU";
	}
	if(!strcmp(instruction, "011010"))
	{
		return "DIV";
	}
	if(!strcmp(instruction, "011011"))
	{
		return "DIVU";
	}
	if(!strcmp(instruction, "100100"))
	{
		return "AND";
	}
	if(!strcmp(instruction, "100101"))
	{
		return "OR";
	}
	if(!strcmp(instruction, "100110"))
	{
		return "XOR";
	}
	if(!strcmp(instruction, "100111"))
	{
		return "NOR";
	}
	if(!strcmp(instruction, "101010"))
	{
		return "SLT";
	}
	if(!strcmp(instruction, "000000"))
	{
		return "SLL";
	}
	if(!strcmp(instruction, "000010"))
	{
		return "SRL";
	}
	if(!strcmp(instruction, "000011"))
	{
		return "SRA";
	}
	if(!strcmp(instruction, "010000"))
	{
		return "MFHI";
	}
	if(!strcmp(instruction, "010010"))
	{
		return "MFLO";
	}
	if(!strcmp(instruction, "010001"))
	{
		return "MTHI";
	}
	if(!strcmp(instruction, "010011"))
	{
		return "MTLO";
	}
	if(!strcmp(instruction, "001000"))
	{
		return "JR";
	}
	if(!strcmp(instruction, "001001"))
	{
		return "JALR";
	}
	return NULL;
}

char* GetIFunction(char* instruction, char* rt)
{
	if(!strcmp(instruction, "001000"))
	{
		return "ADDI";
	}
	else if(!strcmp(instruction, "001001"))
	{
		return "ADDIU";
	}
	else if(!strcmp(instruction, "001100"))
	{
		return "ANDI";
	}
	else if(!strcmp(instruction, "001101"))
	{
		return "ORI";
	}
	else if(!strcmp(instruction, "001110"))
	{
		return "XORI";
	}
	else if(!strcmp(instruction, "001010"))
	{
		return "SLTI";
	}
	else if(!strcmp(instruction, "100011"))
	{
		return "LW";
	}
	else if(!strcmp(instruction, "100000"))
	{
		return "LB";
	}
	else if(!strcmp(instruction, "100001"))
	{
		return "LH";
	}
	else if(!strcmp(instruction, "001111"))
	{
		return "LUI";
	}
	else if(!strcmp(instruction, "101011"))
	{
		return "SW";
	}
	else if(!strcmp(instruction, "101000"))
	{
		return "SB";
	}
	else if(!strcmp(instruction, "101001"))
	{
		return "SH";
	}
	else if(!strcmp(instruction, "000100"))
	{
		return "BEQ";
	}
	else if(!strcmp(instruction, "000101"))
	{
		return "BNE";
	}
	else if(!strcmp(instruction, "000110"))
	{
		return "BLEZ";
	}
	else if(!strcmp(instruction, "000001") && !strcmp(rt, "00000"))
	{
		return "BLTZ";
	}
	else if(!strcmp(instruction, "000001") && !strcmp(rt, "00001"))
	{
		return "BGEZ";
	}
	else if(!strcmp(instruction, "000111"))
	{
		return "BGTZ";
	}
	else{
		return "Instruction not found";
	}

	return NULL;
}

char* GetJFunction(char* instruction)
{
	if(!strcmp(instruction, "000010"))
	{
		return "J";
	}
	if(!strcmp(instruction, "000011"))
	{
		return "JAL";
	}
	if(!strcmp(instruction, "000011"))
	{
		return "JAL";
	}
	return NULL;
}

int convertBinarytoDecimal(char * binary) {
	int num = atoi(binary);
    unsigned int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    unsigned int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }

    return dec_value;
}


void returnRFormat(char* instruction, MIPS* hold) {
	// Read in the rs register
	char rs[6];
	strncpy(rs, &instruction[6], 5);
	rs[5] = '\0';

	// Read in the rt register
	char rt[6];
	strncpy(rt, &instruction[11], 5);
	rt[5] = '\0';

	// read in the rd register
	char rd[6];
	strncpy(rd, &instruction[16], 5);
	rd[5] = '\0';

	// read in the op code
	char op[7];
	strncpy(op, &instruction[0], 6);
	op[6] = '\0';

	char shamnt[6];
	strncpy(shamnt, &instruction[21],5);
	shamnt[5] = '\0';

	char func[7];
	strncpy(func, &instruction[26],6);
	func[6] = '\0';

	printf("%s %s, %s, %s\n",GetRFunction(op),returnRegister(rd), returnRegister(rs), returnRegister(rt));
	hold->op = GetRFunction(op);
	hold->rd = convertBinarytoDecimal(rd);
	hold->rs = convertBinarytoDecimal(rs);
	hold->rt = convertBinarytoDecimal(rt);
	hold->shamt = atoi(shamnt);
	hold->funct = func;
	hold->immediate = 0;
}

void returnIFormat(char* instruction, MIPS* hold) {
	// read in the rs register
	char rs[6];
	strncpy(rs, &instruction[6], 5);
	rs[5] = '\0';

	// read in the rt register
	char rt[6];
	strncpy(rt, &instruction[11],x 5);
	rt[5] = '\0';

	// read in the imm value and convert to decimal
	char imm[17];
	strncpy(imm, &instruction[16], 16);
	imm[16] = '\0';
	long unsigned int imm_hex = strtol(imm, NULL, 2);

	// read in the op code
	char op[7];
	strncpy(op, &instruction[0], 6);
	op[6] = '\0';

	if(!strcmp(GetIFunction(op, rt), "LUI"))
	{
		printf("%s %s, x%lx\n",GetIFunction(op, rt),returnRegister(rt), imm_hex);
		hold->op = GetIFunction(op,rt);
		hold->rt = convertBinarytoDecimal(rt);
		hold->rs = -1;
		hold->immediate = imm_hex;
		hold->shamt = 0;
		hold->funct = "";
		hold->rd = -1;
		hold->address = "";
	}
	else if(!strcmp(GetIFunction(op, rt), "SW") || !strcmp(GetIFunction(op, rt), "SB") || !strcmp(GetIFunction(op, rt), "SH"))
	{
		printf("%s %s, %d(%s)\n",GetIFunction(op, rt),returnRegister(rs),(int)imm_hex,returnRegister(rt));
		hold->op = GetIFunction(op,rt);
		hold->rs = convertBinarytoDecimal(rs);
		hold->rt = convertBinarytoDecimal(rt);
		hold->immediate = imm_hex;
		hold->shamt = 0;
		hold->funct = "";
		hold->rd = -1;
		hold->address = "";
	}
	else if(!strcmp(GetIFunction(op, rt), "LW"))
	{
		printf("%s %s, %d(%s)\n",GetIFunction(op, rt),returnRegister(rt),(int)imm_hex,returnRegister(rs));
		hold->op = GetIFunction(op,rt);
		hold->rs = convertBinarytoDecimal(rs);
		hold->rt = convertBinarytoDecimal(rt);
		hold->immediate = imm_hex;
		hold->shamt = 0;
		hold->funct = "";
		hold->rd = -1;
		hold->address = "";
	}
	else if(!strcmp(GetIFunction(op, rt), "BEQ") || !strcmp(GetIFunction(op, rt), "BNE"))
	{
		printf("%s %s, %s, x%lx\n",GetIFunction(op, rt),returnRegister(rs),returnRegister(rt), imm_hex);
		hold->op = GetIFunction(op,rt);
		hold->rs = convertBinarytoDecimal(rs);
		hold->rt = convertBinarytoDecimal(rt);
		hold->immediate = imm_hex;
		hold->shamt = 0;
		hold->funct = "";
		hold->rd = -1;
		hold->address = "";
	}
	else
	{
		printf("%s %s, %s, x%lx\n",GetIFunction(op, rt),returnRegister(rt), returnRegister(rs), imm_hex);
		hold->op = GetIFunction(op,rt);
		hold->rs = convertBinarytoDecimal(rs);
		hold->rt = convertBinarytoDecimal(rt);
		hold->immediate = imm_hex;
		hold->shamt = 0;
		hold->funct = "";
		hold->rd = -1;
		hold->address = "";
	}
}

void returnJFormat(char* instruction, MIPS* hold) {
	// read in the op code
	char op[7];
	strncpy(op, &instruction[0], 6);
	op[6] = '\0';

	// read in the Jump Addresss
	char address[27];
	strncpy(address, &instruction[6], 26);
	printf("%s %s\n", GetJFunction(op), address);
	hold->op = GetJFunction(op);
	hold->rs = -1;
	hold->rt = -1;
	hold->immediate = 0;
	hold->shamt = 0;
	hold->funct = "";
	hold->rd = -1;
	hold->address = address;
}

char* returnRegister(char* reg){
	if (!strcmp(reg, "00000")) return "$zero";
	if (!strcmp(reg, "00001")) return "$at";
	if (!strcmp(reg, "00010")) return "$v0";
	if (!strcmp(reg, "00011")) return "$v1";
	if (!strcmp(reg, "00100")) return "$a0";
	if (!strcmp(reg, "00101")) return "$a1";
	if (!strcmp(reg, "00110")) return "$a2";
	if (!strcmp(reg, "00111")) return "$a3";
	if (!strcmp(reg, "01000")) return "$t0";
	if (!strcmp(reg, "01001")) return "$t1";
	if (!strcmp(reg, "01010")) return "$t2";
	if (!strcmp(reg, "01011")) return "$t3";
	if (!strcmp(reg, "01100")) return "$t4";
	if (!strcmp(reg, "01101")) return "$t5";
	if (!strcmp(reg, "01110")) return "$t6";
	if (!strcmp(reg, "01111")) return "$t7";
	if (!strcmp(reg, "10000")) return "$s0";
	if (!strcmp(reg, "10001")) return "$s1";
	if (!strcmp(reg, "10010")) return "$s2";
	if (!strcmp(reg, "10011")) return "$s3";
	if (!strcmp(reg, "10100")) return "$s4";
	if (!strcmp(reg, "10101")) return "$s5";
	if (!strcmp(reg, "10110")) return "$s6";
	if (!strcmp(reg, "10111")) return "$s7";
	if (!strcmp(reg, "11000")) return "$t8";
	if (!strcmp(reg, "11001")) return "$t9";
	if (!strcmp(reg, "11010")) return "$k0";
	if (!strcmp(reg, "11011")) return "$k1";
	if (!strcmp(reg, "11100")) return "$gp";
	if (!strcmp(reg, "11101")) return "$sp";
	if (!strcmp(reg, "11110")) return "$fp";
	if (!strcmp(reg, "11111")) return "$ra";
	return NULL;
}

/************************************************************/
/* Print the instruction at given memory address (in MIPS assembly format). */
/************************************************************/
void print_instruction(uint32_t addr){
	//Read in the instructions
	uint32_t instr = mem_read_32(addr);
	char string[9];

	sprintf(string,"%08x", instr);

	// Check for syscall
	if(instr == 0xC)
		return;

	char fullbinay[33];
	fullbinay[0] = '\0';

	MIPS junk;

	for(int i = 0; i < 8; i++)
	{
		strcat(fullbinay, hex_to_binary(string[i]));
	}

	switch(FindFormat(fullbinay)) {
		case 'R': {
			returnRFormat(fullbinay,&junk);
			break;
		}
		case 'I': {
			returnIFormat(fullbinay,&junk);
			break;
		}
		case 'J': {
			returnJFormat(fullbinay,&junk);
			break;
		}
		default: {
			printf("You messed up.\n");
			break;
		}
	}
}
