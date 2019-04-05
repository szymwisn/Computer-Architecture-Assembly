# ##################################
# Szymon Wiśniewski
# 241269
# 05.04.2019, 11:00
#
# wykorzystane rejestry i ich przeznaczenie:
#    eax - pierwsza liczba
#    ebx - druga liczba
#    edi - iterator
#    ecx - obsluga ostatniej pozyczki
#
#    na stosie bedzie przechowywany ostateczny wynik
#    operacje w U2
#
# ##################################

.code32

.section .text

.section .data
    liczba1:
        .long 0x0000032A, 0x23456789, 0x00000000, 0xBBBBBBBB

    liczba2:
        .long 0xAB43CEFA, 0x12345678, 0x33333333, 0xAAAAAAAA

    # ilosc liczb
    index = (. - liczba1) / 8 - 1

.globl _start

_start:
    # zapewnienie, że flaga przeniesienia jest = 0
    CLC

    # odlozenie flag na stos
    PUSHF

    # ustawienie iteratora na rownowartosc ilosci liczb, będę schodził do 0
    MOVL $index, %edi

loop:
    # pobranie ze stosu flag
    POPF

    # wczytanie liczb do wybranych rejestrów
    MOVL liczba1(,%edi,4), %eax
    MOVL liczba2(,%edi,4), %ebx

    # odjecie zawartosci obu rejestrów z pozyczka
    # w uproszczeniu: eax = eax - ebx
    SBBL %ebx, %eax

    # odlozenie wyniku na stos
    PUSHL %eax

    # odlozenie flag na stos
    PUSHF

    # dekrementacja iteratora
    SUBL $1, %edi

    # porownanie iteratora z 0
    CMPL $0, %edi

    # jesli iterator >= 0, petla sie dalej wykonuje
    JGE loop

    # pobranie ze stosu flag
    POPF
    
    # jesli w ostatnim odejmowaniu nie ma pozyczki, to koniec programu
    JNC end

borrow_last:
    PUSHL $0xF


end: 
    MOVL $1, %eax
    MOVL %edi, %ebx
    INT $0x80
