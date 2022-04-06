CFLAGS:=-I include/ -Wall -Wextra -pedantic

lab_04: obj/clist.o obj/main.o | obj
	gcc -g obj/clist.o obj/main.o -o lab_04

obj/clist.o: include/clist.h src/clist.c | obj
	gcc -g -c $(CFLAGS) src/clist.c -o obj/clist.o

obj/main.o: include/clist.h src/main.c | obj
	gcc -g -c $(CFLAGS) src/main.c -o obj/main.o

obj:
	mkdir obj

.PHONY: clean
clean: | obj
	rm -rf obj lab_04
