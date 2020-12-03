/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero and ???                                        */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"

/*--------------------------------------------------------------------*/

/* Return the machine language equivalent of "mov reg, immed" where
   reg is a W register.
   
   Parameters:
      uiReg: the number of reg.
      uiImmed: the immed value. */
   
unsigned int MiniAssembler_mov(unsigned int uiReg,
   unsigned int uiImmed)
{
   unsigned int uiInstr; /* Instruction */

   /* 0101 0010 100x xx...xx xxxx */
   uiInstr = 0x52800000;
   
   /* Getting the Rd value in */
   uiInstr |= uiReg;

   /* Move immed value 21 bits so it starts there and stuff */
   uiImmed = uiImmed << 21;

   /* Getting the immed value in from 4 to 20 */
   uiInstr |= uiImmed;

   return uiInstr;
}
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* Return the machine language equivalent of "adr reg, addr". 

   Parameters:
      uiReg: the number of reg.
      ulAddr: the address denoted by addr.
      ulAddrOfThisInstr: the address of the adr instruction itself. */

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr; /* Instruction */
   unsigned int uiDisp; 
   unsigned int uiDispLo; 
   unsigned int uiDispHi;
         
   uiInstr = 0x10000000;
   
   uiInstr |= uiReg;
    
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   uiDispLo = uiDisp & 0x3;
   uiDispLo = uiDispLo << 29;
   uiInstr |= uiDispLo;
   
   uiDispHi = uiDisp >> 2;
   uiDispHi = uiDispHi << 5;
   uiDispHi &= 0x00ffffe0;
   uiInstr |= uiDispHi;
   
   return uiInstr;
}

/*--------------------------------------------------------------------*/

/* Return the machine language equivalent of "strb fromreg,[toreg]", 
   where fromreg is a W register and toreg is a X register.

   Parameters:
      uiFromReg: the number of fromreg.
      uiToReg: the number of toreg. */

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg) {
      unsigned int uiInstr;
      
      /* 0011 1000 000x xx...xx xxxx */
      uiInstr = 0x39000000;

      /* Rightmost 5 bits to contain the number of the
         register from where byte has to be moved. */
      uiInstr |= uiFromReg;

      /* Shift number of register to where byte has
         to be moved left by 5 bits. */
      uiToReg = uiToReg << 5;


      uiInstr |= uiToReg;

      return uiInstr;
   }

/*--------------------------------------------------------------------*/

/* Return the machine language equivalent of "b addr". 
   
   Parameters:
      ulAddr: the address denoted by addr, that is, the address to
         which the branch should occur.
      ulAddrOfThisInstr: the address of the b instruction itself. */

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr; /* Instruction */
   unsigned int uiDisp; 
   
   uiInstr = 0x14000000;

   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);
   uiDisp = uiDisp & 0x1A;
   /* uiDisp = uiDisp << 26; */
   uiInstr |= uiDisp; 

   return uiInstr;
}

