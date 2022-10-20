#ifdef MU_HELPER
#define MU_HELPER

#include <stdint.h>
#include <math.h>

/***************************************************************/
/* HELPER Function Declerations.                                                                                                */
/***************************************************************/
typedef struct MIPS_INSTRUCT {
 char* op;
 int rs;
 int rt;
 int rd;
 uint32_t shamt;
 char* funct;
 uint32_t immediate;
 char* address;
} MIPS;


char* returnRegister(char* reg);
char* hex_to_binary(char Hexdigit);
char FindFormat(char* instruction);
char* GetIFunction(char* instruction, char* rt);
char* GetJFunction(char* instruction);
int convertBinarytoDecimal(char * binary);
void returnRFormat(char* instruction, MIPS*);
void returnIFormat(char* instruction, MIPS*);
void returnJFormat(char* instruction, MIPS*);
void getSingleInstruct(MIPS*);
void print_instruction(uint32_t addr);

#endif
