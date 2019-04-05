all: add sub mul

add: add.o
	ld add.o -o add

add.o: add.s
	as --gstabs+ -ggdb add.s -o add.o

sub: sub.o
	ld sub.o -o sub

sub.o: sub.s   
	as --gstabs+ -ggdb sub.s -o sub.o
	
mul: mul.o
	ld mul.o -o mul
	
mul.o: mul.s
	as --gstabs+ -ggdb mul.s -o mul.o
