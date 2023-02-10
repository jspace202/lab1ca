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
#define SIGNEXT(v, sb) ((v) | (((v) & (1 << (sb))) ? ~((1 << (sb))-1) : 0))

// I Instructions
int ADDI (int Rd, int Rs1, int Imm, int Funct3) { //I Type

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int LB (char* i_);
int LH (char* i_);
int LW (char* i_);
int LBU (char* i_);
int LHU (char* i_);
int SLLI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] << SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLTI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] < SIGNEXT(Imm,12) ? 1 : 0;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLTIU (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] < SIGNEXT(Imm,12) ? 1 : 0;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int XORI (int Rd, int Rs1, int Imm, int Funct3) { //I Type

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] ^ SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SRLI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SRAI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int ORI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] | SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int ANDI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] && SIGNEXT(Imm,12);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

// U Instruction
int AUIPC (char* i_);
int LUI (char* i_);

// S Instruction
int SB (char* i_);
int SH (char* i_);
int SW (char* i_);

// R instruction
int ADD (int Rd, int Rs1, int Rs2, int Funct3) { //R Type

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SUB (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] - CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLL (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] << CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLT (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2] ? 1 : 0;
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int SLTU (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2] ? 1 : 0;
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
int SRA (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}
int OR(int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] | CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}
int AND (int Rd, int Rs1, int Rs2, int Funct3) {
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] && CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

// B instructions
int BNE (int Rs1, int Rs2, int Imm, int Funct3) { //B Type

  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] != CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;

}
int BEQ (char* i_);
int BLT (char* i_);
int BGE (char* i_);
int BLTU (char* i_);
int BGEU (char* i_);

// I instruction
int JALR (char* i_);

// J instruction
int JAL (char* i_);

int ECALL (char* i_){return 0;}

#endif
