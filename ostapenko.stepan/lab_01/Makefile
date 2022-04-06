CFLAGS:=-I include/ -Wall -Wextra -Werror

lab1: bin/algorithm.o bin/io.o bin/util.o bin/main.o | bin
	gcc bin/*.o -o lab1

bin:
	mkdir bin

bin/main.o: src/main.c include/algorithm.h include/io.h include/util.h | bin
	gcc -c $(CFLAGS) src/main.c -o bin/main.o

bin/algorithm.o: src/algorithm.c include/algorithm.h include/io.h include/util.h | bin
	gcc -c $(CFLAGS) src/algorithm.c -o bin/algorithm.o

bin/io.o: src/io.c include/io.h | bin
	gcc -c $(CFLAGS) src/io.c -o bin/io.o

bin/util.o: src/util.c include/io.h include/util.h | bin
	gcc -c $(CFLAGS) src/util.c -o bin/util.o

.PHONY: clean
clean: | bin
	rm -rf bin lab1
