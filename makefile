assembler: assembler.o pre_asm.o pre_asm.h
	gcc -ansi -Wall -pedantic -g assembler.o pre_asm.o -o assembler
assembler.o: assembler.c pre_asm.h
	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o
pre_asm.o: pre_asm.c pre_asm.h
	gcc -c -ansi -Wall -pedantic pre_asm.c -o pre_asm.o
clean:
	rm *.o assembler

