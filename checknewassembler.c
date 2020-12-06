#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "miniassembler.h"

int main(void)
{
    /* adrp	x0, 0x400000 */
    unsigned int uiAdrpInstr1 = MiniAssembler_adrp(0, 0x400000, 0x420064); /* 1 */
    /* add	x0, x0, #0x978 */
    unsigned int uiAddInstr1 = MiniAssembler_add(0, 0, 0x978); /* 2 */
    /* adrp	x1, 0x420000*/
    unsigned int uiAdrpInstr2 = MiniAssembler_adrp(1, 0x420000, 0x42006C); /* 3 */
    /* add	x1, x1, #0x58 */
    unsigned int uiAddInstr2 = MiniAssembler_add(1, 1, 0x58);/* 4 */
    /* bl	0x400600 <printf@plt> */
    unsigned int uiBlInstr1 = MiniAssembler_bl(0x400600, 0x420074);/* 5 */
    
    /* grade = + */
    unsigned int uiMovInstr1 = MiniAssembler_mov(1, 0x002B); /* 6 */
    unsigned int uiAdrInstr1 = MiniAssembler_adr(2, 0x420044, 0x42007C); /* 7 */
    unsigned int uiStrbInstr1 = MiniAssembler_strb(1, 2); /* 8 */
    
    /* Branch to printf("%c is your grade.\n", grade); */
    unsigned int uiBInstr1 = MiniAssembler_b(0x400864, 0x420084); /* 9 */

    printf("%u", uiAdrpInstr1);
    printf("%u", uiAddInstr1);
    printf("%u", uiAdrpInstr2);
    printf("%u", uiAddInstr2);
    printf("%u", uiBlInstr1);

    printf("%u", uiMovInstr1);
    printf("%u", uiAdrInstr1);
    printf("%u", uiStrbInstr1);

    printf("%u", uiBInstr1);
    
    return 1;
}

