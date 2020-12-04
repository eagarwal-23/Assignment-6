#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

enum {BUFSIZE = 48};

char grade = 'D';
char name[BUFSIZE];

void readString(void)
{
   char buf[BUFSIZE];
   int i = 0; 
   int c;

   for (;;)
   {
      c = fgetc(stdin);
      if ((c == EOF) || (c == '\n')) 
         break;
      buf[i] = c;
      i++;
   }
   buf[i] = '\0';

   for (i = 0; i < BUFSIZE; i++) 
      name[i] = buf[i];
}

void getName(void)
{
   printf("What is your name?\n");
   readString();
}

int main(void)
{
   mprotect((void*)((unsigned long)name & 0xfffffffffffff000), 1,
            PROT_READ | PROT_WRITE | PROT_EXEC);

   getName();

   if (strcmp(name, "Andrew Appel") == 0) 
      grade = 'B';

   printf("%c is your grade.\n", grade);
   printf("Thank you, %s.\n", name);

   return 0;
}



/* grade = A in x1 */
mov x1, A
adr x2, grade
strb x1, x2 

/* print */
   0x40085c <main+60>:	        adrp	x0, 0x420000 /need
   0x400860 <main+64>:	        strb	w1, [x0,#68]
   0x400864 <main+68>:	        adrp	x0, 0x400000
   0x400868 <main+72>:	        add	x0, x0, #0x960 /need
   0x40086c <main+76>:	        adrp	x1, 0x420000
   0x400870 <main+80>:	        ldrb	w1, [x1,#68] /need
   0x400874 <main+84>:	        bl	0x400600 <printf@plt> /done

bl printf

mov x0, +

bl printf

b 0x400878, adress of b

    unsigned int uiMovInstr = MiniAssembler_mov(1, 0x41);
    unsigned int uiAdrInstr = MiniAssembler_adr(2, 0x420044, 0x42007C);
    unsigned int uiStrbInstr = MiniAssembler_strb(1, 2);
    unsigned int uiBInstr = MiniAssembler_b(0x40085c, 0x420084);

