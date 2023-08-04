main: main.o am_file_functions.o am_file_logic.o general_functions.o entry_file_functions.o
	gcc -ansi -Wall -pedantic -g main.o am_file_functions.o am_file_logic.o general_functions.o entry_file_functions.o -o main

main.o: main.c am_file_functions.h am_file_logic.h
	gcc -c -ansi -Wall -pedantic main.c -o main.o

general_functions.o: general_functions.c general_functions.h am_file_functions.h
	gcc -c -ansi -Wall -pedantic general_functions.c -o general_functions.o

am_file_logic.o: am_file_logic.c am_file_logic.h am_file_functions.h general_functions.h
	gcc -c -ansi -Wall -pedantic am_file_logic.c -o am_file_logic.o

am_file_functions.o: am_file_functions.c am_file_functions.h
	gcc -c -ansi -Wall -pedantic am_file_functions.c -o am_file_functions.o

entry_file_functions.o: entry_file_functions.c entry_file_functions.h
	gcc -c -ansi -Wall -pedantic entry_file_functions.c -o entry_file_functions.o

clean:
	rm *.o
