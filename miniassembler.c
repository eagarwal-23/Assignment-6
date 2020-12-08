/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Eesha Agarwal, and Tan vu                     */
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
   
   /* Rightmost 5 bits contain the name of the 32-bit destination 
      register. */
   uiInstr |= uiReg;

   /* Mask off everything except rightmost 16 bits: 0-15 in 5-20. */ 
   uiImmed &= 0x0000FFFF;

   /* Shift the immediate value to the left 5 bits. */
   uiImmed = uiImmed << 5;

   /* Bits 5-20 contain the immediate value. */
   uiInstr |= uiImmed;

   /* Return the final machine code. */
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
   /* uiDisp = uiDisp << 26; */

   /* shift to the right to account for all multiples of 4 */
   uiDisp = uiDisp >> 2;

   /* mask for 26 bits displacement might be negative */
   uiDisp &= 0x03FFFFFF;

   uiInstr |= uiDisp; 

   return uiInstr;
}

/*--------------------------------------------------------------------*/

/* Return the machine language equivalent of "bl addr". 
   
   Parameters:
      ulAddr: the address denoted by addr, that is, the address to
         which the branch should occur.
      ulAddrOfThisInstr: the address of the b instruction itself. */

unsigned int MiniAssembler_bl(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr; /* Instruction */
   unsigned int uiDisp; 
   
   uiInstr = 0x94000000;

   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   /* shift to the right to account for all multiples of 4 */
   uiDisp = uiDisp >> 2;

   /* mask for 26 bits displacement might be negative */
   uiDisp &= 0x03FFFFFF;

   uiInstr |= uiDisp; 

   return uiInstr;
}
/*--------------------------------------------------------------------*/
/* Return the machine language equivalent of "adrp reg, addr". 

   Parameters:
      uiReg: the number of reg.
      ulAddr: the address denoted by addr.
      ulAddrOfThisInstr: the address of the adr instruction itself. */

unsigned int MiniAssembler_adrp(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr; /* Instruction */
   unsigned int uiDisp; 
   unsigned int uiDispLo; 
   unsigned int uiDispHi;
         
   uiInstr = 0x90000000;
   
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

/* Return the machine language equivalent of "add rd, rn, #imm" where
   rd, rn are all X registers.
   
   Parameters:
      uiRegSum: rd,
      uiRegAdd1: rn,
      uiImmed: #imm
*/
   
unsigned int MiniAssembler_add(unsigned int uiRegSum,
   unsigned int uiRegAdd1, unsigned int uiImmed)
{
   unsigned int uiInstr; /* Instruction */

   /* 1001 0001 00.. .... .... .... .... */

   uiInstr = 0x91000000;
   
   /* Getting the Rd value in */
   uiInstr |= uiRegSum;
   
   /* Getting the Rn value in from 5 to 9 */
   uiRegAdd1 = uiRegAdd1 << 5;
   uiInstr |= uiRegAdd1;

   /* Getting the uiImmed value in from 10 to 21 */
   /* mask off everything except rightmost 16 bits: 0-15 in 5-20 */ 
   uiImmed &= 0x0000FFFFF;
   uiImmed = uiImmed << 10;
   uiInstr |= uiImmed;

   return uiInstr;
}


/*--------------------------------------------------------------------*/
