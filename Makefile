DIFFICULTIES = 8 12

.DEFAULT: bench
.PHONY: bench clean view

BINS = $(patsubst %,mandel%,$(DIFFICULTIES))

all: bench view

bench: $(BINS)

view: mandelview

mandelview: mandelview.c
	gcc -o mandelview mandelview.c -lSDL2

$(BINS): mandel%: mandelbench.c
	gcc -o $@ mandelbench.c -O3 -DDIFFICULTY=$*

clean: 
	rm -rf mandelview $(DIFFICULTIES)