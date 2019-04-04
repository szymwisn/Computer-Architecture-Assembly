all: add sub

add: add.o
	ld add.o -o add

add.o: add.s
	as --gstabs+ -ggdb add.s -o add.o

sub: sub.o
	ld sub.o -o sub

sub.o: sub.s   
	as sub.s -o sub.o
