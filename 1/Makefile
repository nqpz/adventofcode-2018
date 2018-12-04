include ../lib/common.mk

.PHONY: answers clean

answers: answer1 answer2

answer1: emitter1
	../bin/run_emitted emitter1 true < input > answer1

answer2: emitter2
	../bin/run_emitted emitter2 true < input > answer2

emitter1: ../lib/read.h ../lib/emit.h common.h emitter1.c
	gcc $(EMITTER_FLAGS) -o emitter1 emitter1.c

emitter2: ../lib/read.h ../lib/emit.h common.h emitter2.c
	gcc $(EMITTER_FLAGS) -o emitter2 emitter2.c

clean:
	rm -f emitter1 emitter2 answer1 answer2
