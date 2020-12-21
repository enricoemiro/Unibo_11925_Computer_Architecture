main: main.o code_writer.o parser.o helpers.o
	gcc -o VMtranslator main.o code_writer.o parser.o helpers.o

main.o: main.c src/parser.h src/code_writer.h src/helpers.h
	gcc -c main.c

code_writer.o: src/code_writer.c src/code_writer.h
	gcc -c src/code_writer.c

parser.o: src/parser.c src/parser.h src/helpers.h
	gcc -c src/parser.c

helpers.o : src/helpers.c src/helpers.h
	gcc -c src/helpers.c

clean:
	rm *.o VMtranslator
