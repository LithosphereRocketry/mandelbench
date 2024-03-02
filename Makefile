.DEFAULT: bench
.PHONY: bench clean view

all: bench view

bench: mandel8

view: mandelview

mandelview: mandelview.c
	gcc -o mandelview mandelview.c -lSDL2

mandel8: mandel8.c
	gcc -o mandel8 mandel8.c -O3

clean: 
	rm -rf mandelview mandel8