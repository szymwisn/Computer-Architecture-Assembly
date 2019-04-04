# ##################################
# Szymon Wiśniewski
# 241269
# 05.04.2019, 11:00
#
# wykorzystane rejestry i ich przeznaczenie:
#    eax - pierwsza liczba
#    ebx - druga liczba
#    edi - iterator
#    ecx - obsluga ostatniego przeniesienia
#
#    na stosie bedzie przechowywany ostateczny wynik
#
# założenia: 
#   - dlugosc obu liczb jest rowna
#
# ##################################

.code32

.section .text

.section .data
    liczba1:
        .long 0x00000003, 0x00000000, 0x77777777, 0x10101010

    liczba2:
        .long 0xFFFFFFFF, 0x12345678, 0x33333333, 0xF1010101

    # ilosc liczb
    index = 3

.globl _start

_start:
    # zapewnienie, że flaga przeniesienia jest = 0
    CLC

    # ustawienie iteratora na dlugosc liczby, będę schodził do 0
    MOVL $index, %edi

loop:
    # pobranie ze stosu flag
    POPF

    # wczytanie liczb do wybranych rejestrów
    MOVL liczba1(,%edi,4), %eax
    MOVL liczba2(,%edi,4), %ebx

    # dodanie zawartosci obu rejestrów z przeniesieniem
    # w uproszczeniu: ebx = ebx + eax
    ADCL %eax, %ebx

    # odlozenie wyniku na stos
    PUSHL %ebx

    # odlozenie flag na stos
    PUSHF

    # dekrementacja iteratora
    # dlaczego nie działa?
    # DECL %edi
    SUBL $1, %edi

    # porownanie iteratora z 0
    CMPL $0, %edi

    # jesli iterator >= 0, petla sie dalej wykonuje
    JGE loop

    # pobranie ze stosu flag
    POPF
    
    # jesli w ostatnim dodawaniu nie ma przeniesienia, to koniec programu
    JNC end

carry_last:
    MOVL $1, %ecx
    PUSHL %ecx

end: 
    MOVL $1, %eax
    MOVL %edi, %ebx
    INT $0x80
