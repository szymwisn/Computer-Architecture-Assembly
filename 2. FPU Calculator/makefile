all: fpu_calc

fpu_calc: fpu_calc.o
	ld fpu_calc.o -o fpu_calc

fpu_calc.o: fpu_calc.s
	as --gstabs+ -ggdb fpu_calc.s -o fpu_calc.o