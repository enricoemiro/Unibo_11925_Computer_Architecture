main: main.o symbol_table.o constant.o helpers.o assembler.o
	gcc -o assembler main.o symbol_table.o constant.o helpers.o assembler.o

main.o: main.c lib/symbol_table.h lib/constant.h lib/helpers.h lib/assembler.h
	gcc -c main.c

assembler.o: assembler.c lib/assembler.h
	gcc -c assembler.c

symbol_table.o: symbol_table.c lib/symbol_table.h
	gcc -c symbol_table.c

helpers.o : helpers.c lib/helpers.h
	gcc -c helpers.c

constant.o: constant.c lib/constant.h
	gcc -c constant.c

clean:
	rm *.o assembler