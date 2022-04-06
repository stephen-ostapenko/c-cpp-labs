CFLAGS:=-I include/

lab_02: obj/str.o obj/test_str.o obj/test.o | obj
	gcc obj/str.o obj/test_str.o obj/test.o -o lab_02

obj/str.o: include/str.h src/str.c | obj
	gcc -c $(CFLAGS) src/str.c -o obj/str.o

obj/test_str.o: include/test_str.h include/str.h src/test_str.c | obj
	gcc -c $(CFLAGS) src/test_str.c -o obj/test_str.o

obj/test.o: include/test_str.h include/str.h src/test.c | obj
	gcc -c $(CFLAGS) src/test.c -o obj/test.o

obj:
	mkdir obj

.PHONY: clean
clean: | obj
	rm -rf obj lab_02
