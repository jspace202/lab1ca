/***************************************************************/
/*                                                             */
/*   RISC-V RV32 Instruction Level Simulator                   */
/*                                                             */
/*   ECEN 4243                                                 */
/*   Oklahoma State University                                 */
/*                                                             */
/***************************************************************/

#ifndef _SIM_ISA_H_
#define _SIM_ISA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

//
// MACRO: Check sign bit (sb) of (v) to see if negative
//   if no, just give number
//   if yes, sign extend (e.g., 0x80_0000 -> 0xFF80_0000)
//
#define SIGNEXT(v, sb) ((v) | ( (0 < ( (v) & (1 << (sb-1) ) )) ? ~( (1 << (sb-1) )-1 ) : 0))

int ZEROEXT(int v, int sb) {
  if(sb == 8) {
    int z = 0XFF & v;
    return z;
   }
   else if(sb == 5) {
    int z = 0X1F & v;
    return z;
   }
   else if(sb == 16) {
    int z = 0XFFFF & v;
    return z;
   }
}

// R instructions

int ADD (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int SUB (int Rd, int Rs1, int Rs2, int Funct3, int Funct7) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] - CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;

}

int SLL (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs2] << CURRENT_STATE.REGS[Rs1];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int SLT (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  if(CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2]) {
    cur = 1;
  }
  else { cur = 0; }
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

unsigned SLTU (unsigned Rd, unsigned Rs1, unsigned Rs2, unsigned Funct3) {

   unsigned cur = 0;
    if(CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2], 5) {
      cur = 1;
    }
    else { cur = 0; } 
    NEXT_STATE.REGS[Rd] = cur;
    return 0;

}

int XOR (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] ^ CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;

}

int SRL (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;

}

unsigned SRA (unsigned Rd, unsigned Rs1, unsigned Rs2, unsigned Funct3, unsigned Funct7) {

  unsigned cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;

}

int OR (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] | CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;

}

int AND (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] & CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;

}

// I Instructions

int LB (int Rd, int Rs1, int Imm, int Funct3) {

  uint32_t memAddress = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  int readData = mem_read_32(memAddress);
  int data = readData & 0xFF;
  NEXT_STATE.REGS[Rd] = SIGNEXT((data),8); 
  return 0;

}

int LH (int Rd, int Rs1, int Imm, int Funct3) {

  uint32_t memAddress = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  int readData = mem_read_32(memAddress);
  int data = readData & 0xFFFF;
  NEXT_STATE.REGS[Rd] = SIGNEXT((data),16); 
  return 0;

}

int LW (int Rd, int Rs1, int Imm, int Funct3) {

  uint32_t memAddress = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  uint32_t data = mem_read_32(memAddress);
  NEXT_STATE.REGS[Rd] = data; 
  return 0;

}

int LBU (int Rd, int Rs1, int Imm, int Funct3) {

  uint32_t memAddress = CURRENT_STATE.REGS[Rs1] + ZEROEXT(Imm, 12);
  int readData = mem_read_32(memAddress);
  int data = readData & 0xFF;
  NEXT_STATE.REGS[Rd] = ZEROEXT((data),16); 
  return 0;

}


int LHU (int Rd, int Rs1, int Imm, int Funct3) {

  uint32_t memAddress = CURRENT_STATE.REGS[Rs1] + ZEROEXT(Imm, 12);
  int readData = mem_read_32(memAddress);
  int data = readData & 0xFFFF;
  NEXT_STATE.REGS[Rd] = ZEROEXT((data),16); 
  return 0;

}

int ADDI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int SLLI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] << Rd;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int SLTI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  if(CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[SIGNEXT(Imm, 12)]) {
    cur = 1;
  }
  else { cur = 0; } 
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int SLTIU (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  if(CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[ZEROEXT(Imm, 12)]) {
    cur = 1;
  }
  else {
    cur = 0;
  }
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int XORI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] ^ CURRENT_STATE.REGS[SIGNEXT(Imm, 12)];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;

}
int SRLI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> Rd;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int SRAI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = SIGNEXT(CURRENT_STATE.REGS[Rs1],12) >> Rd;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int ORI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] | SIGNEXT(Imm, 12);
  NEXT_STATE.REGS[Rd] =cur;  
  return 0;

}

int ANDI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] & SIGNEXT(Imm, 12);
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;

}

int JALR (int Rd, int Rs1, int Imm, int Funct3) {

  Imm = Imm << 1;
  NEXT_STATE.PC = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = (CURRENT_STATE.PC + 4);

}

// B instructions

int BEQ (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] = CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = CURRENT_STATE.PC + 4 + SIGNEXT(Imm,12);
  return 0;

}

int BNE (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] != CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = CURRENT_STATE.PC + SIGNEXT(Imm,12);
  return 0;

}

int BLT (int Rs1, int Rs2, int Imm, int Funct3) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = CURRENT_STATE.PC + 4 + SIGNEXT(Imm,12);
  return 0;

}

int BGE (int Rs1, int Rs2, int Imm, int Funct3_) {

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = CURRENT_STATE.PC + 4 + SIGNEXT(Imm,12);
  return 0;

}

unsigned BLTU (unsigned Rs1, unsigned Rs2, unsigned Imm, unsigned Funct3) {

  unsigned cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = CURRENT_STATE.PC + 4 + SIGNEXT(Imm,12);
  return 0;

}

unsigned BGEU (unsigned Rs1, unsigned Rs2, unsigned Imm, unsigned Funct3) {

  unsigned cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = CURRENT_STATE.PC + 4 + SIGNEXT(Imm,12);
  return 0;

}

// S Instruction

int SB (int Rs1, int Rs2, int Imm, int Funct3) {

  uint32_t address = CURRENT_STATE.REGS[Rs1]+ SIGNEXT(Imm, 12);
  uint32_t data =  SIGNEXT(CURRENT_STATE.REGS[Rs2], 8);
  mem_write_32(address, data);
  return 0;

}

int SH (int Rs1, int Rs2, int Imm, int Funct3) {

  uint32_t address = CURRENT_STATE.REGS[Rs1]+ SIGNEXT(Imm, 12);
  uint32_t data =  SIGNEXT(CURRENT_STATE.REGS[Rs2], 16);
  mem_write_32(address, data);
  return 0;

}
int SW (int Rs1, int Rs2, int Imm, int Funct3) {

  uint32_t data = CURRENT_STATE.REGS[Rs2];
  uint32_t address =  CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  mem_write_32(address, data);
  return 0;

}

// U Instructions

int AUIPC (int Rd, int Imm) {

  int cur = Imm << 12;
  NEXT_STATE.REGS[Rd] = cur + CURRENT_STATE.PC;
  return 0; 

}

int LUI (int Rd, int Imm) {

  int cur = Imm << 12; 
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

// J instructions

int JAL (int Rd, int Imm) {

  int imm = Imm << 1;
  NEXT_STATE.PC = CURRENT_STATE.PC + SIGNEXT(imm,20) - 4;
  NEXT_STATE.REGS[Rd] = CURRENT_STATE.PC + 4;
  return 0;

}

int ECALL (char* i_){
  
  return 0;
  
}

#endif
