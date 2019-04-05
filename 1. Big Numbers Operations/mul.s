# ##################################
# TODO 
# zaimplementowac dodawanie sum skladowych
#
# ##################################
# wykorzystane rejestry i ich przeznaczenie:
#    eax - pierwsza liczba
#    ebx - druga liczba
#    edi - iterator
#
# dodawanie poszczegolnych iloczynow blokow
#    ecx - suma dodawania
#    edx - iloczyn bloku
#
#    na stosie bedzie przechowywany ostateczny wynik
#
# ##################################

.code32

.section .text

.section .data
    liczba1:
        .long 0x00000003, 0x00000005, 0x00000003, 0x00000001

    liczba2:
        .long 0x00000003, 0x00000002, 0x00000004, 0x00000002

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

# --------------------------------------
loop1:
    # pobranie ze stosu flag
    POPF

    # wczytanie liczb do wybranych rejestrów
    MOVL liczba1(,%edi,4), %eax
    MOVL liczba2(,%edi,4), %ebx

    # pomnozenie zawartosci rejestrow, wynik przechowywany w ebx
    IMUL %eax, %ebx

    # zaladowanie wyniku na stos
    PUSH %ebx

    # zaladowanie flag na stos
    PUSHF

    # dekrementacja iteratora    
    SUBL $1, %edi

    # porownanie iteratora z 0
    CMPL $0, %edi

    # jesli iterator >= 0, petla sie dalej wykonuje
    JGE loop1

# --------------------------------------
addition:
    # wyzerowanie flagi przeniesienia
    CLC

    # zaladowanie flag na stos
    PUSHF

    # zaladowanie iteratora na nowo
    MOV $index, %edi

loop2:
    # pobranie ze stosu flag
    POPF

    # pobranie wyniku mnozenia pojedynczego bloku ze stosu
    POP %edx    # najpierw laduje sie 0x00000000
    POP %edx    # potem odpowiednia liczba

    # dodanie do ecx
    ADCL %edx, %ecx 

    # zaladowanie flag na stos
    PUSHF

    # dekrementacja iteratora    
    SUBL $1, %edi

    # porownanie iteratora z 0
    CMPL $0, %edi

    # jesli iterator >= 0, petla sie dalej wykonuje
    JGE loop2
    
    # jesli w ostatnim dodawaniu nie ma przeniesienia, to koniec programu
    JNC end

carry_last:
    PUSHL $1

# --------------------------------------
end: 
    MOVL $1, %eax
    MOVL %edi, %ebx
    INT $0x80
