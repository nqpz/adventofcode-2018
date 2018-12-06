include ../lib/common.mk

.PHONY: answers clean

answers: answer1 answer2

answer1: program1
	./program1 < input > answer1

answer2: program2
	./program2 < input > answer2

program1: program1.o
	gcc $(NORMAL_FLAGS) -DPROGRAM1 -o program1 program1.o program.c -lm -lOpenCL

program1.o: program1.c
	gcc -O3 -c program1.c

program1.c: program1.fut lib
	futhark-opencl --library program1.fut

program2: program2.o
	gcc $(NORMAL_FLAGS) -DPROGRAM2 -o program2 program2.o program.c -lm -lOpenCL

program2.o: program2.c
	gcc -O3 -c program2.c

program2.c: program2.fut lib
	futhark-c --library program2.fut # futhark-opencl ends up with an allocation inside a kernel that it cannot handle.

lib: futhark.pkg
	futhark-pkg sync

clean:
	rm -f program1.c program1.h program1.o program1 program2.c program2.h program2.o program2 answer1 answer2
