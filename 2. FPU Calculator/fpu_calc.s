.code32

.section .text

.section .data
    plus: .float 0.01
    minus: .float -0.01

    num_a: .float 1.01
    num_b: .float -5.12

    control_word: .float 0

.globl _start

_start:

# ===================================
# ustawienia rejestru control word
# -----------------------------------

cw_settings:
    # zaladownie rejetru CW do rejestru ecx
    FSTCW control_word
    MOV control_word, %ecx

    # ustawienie bitów PC - Precision Control - REAL4/REAL8/REAL10
    # za PC odpowiadaja bity 8 i 9 - tylko na nich operuje, reszte
    # pozostawiam bez zmian
    # 00 - REAL4 - float
    # 10 - REAL8 - double
    # 11 - REAL10 - extended 
    AND $0b1111110011111111, %ecx
    OR  $0b0000000000000000, %ecx # float
    # OR  $0x0000001000000000b, %ecx # double
    # OR  $0x0000001100000000b, %ecx # extended

    # ustawienie bitów RC - Round Control - REAL4/REAL8/REAL10
    # za RC odpowiadaja bity 10 i 11 - tylko na nich operuje, reszte
    # pozostawiam bez zmian
    # 00 - round to nearest
    # 01 - round down (-> -inf)
    # 10 - round up (-> +inf)
    # 11 - truncate (-> 0)
    AND $0b1111001111111111, %ecx
    OR  $0b0000000000000000, %ecx # nearest
    # OR  $0b0000010000000000, %ecx # down
    # OR  $0b0000100000000000, %ecx # up
    # OR  $0b0000110000000000, %ecx # truncate

    # zaladowanie ustawionego rejestru control word
    MOV %ecx, control_word
    FLDCW control_word

    JMP calculator

# ===================================
# kalkulator - operacje na num_a oraz num_b
# -----------------------------------

calculator:

# num_a + num_b
addition:
    FLD num_b
    FLD num_a
    FADDP

# num_a - num_b
substraction:
    FLD num_b
    FLD num_a
    FSUBP

# num_a * num_b
multipliction:
    FLD num_b
    FLD num_a
    FMULP

# num_a / num_b
division:
    FLD num_b
    FLD num_a
    FDIVP

    JMP end


# ===================================
# tutaj generowane sa same wyjatki
# -----------------------------------

exceptions:

# 0 / dodania liczba
plus_zero:
    FLD plus
    FLDZ
    FDIVP

# 0 / ujemna liczba
minus_zero:
    FLD minus
    FLDZ
    FDIVP

# dodania liczba / 0
plus_inf:
    FLDZ
    FLD plus
    FDIVP

# ujemna liczba / 0
minus_inf:
    FLDZ
    FLD minus
    FDIVP

# pierwiastek drugiego stopnia z ujemnej liczby
NaN:
    FLD minus
    FSQRT


# ===================================
# koniec programu
# -----------------------------------

end: 
    MOV $1, %eax
    MOV $0, %ebx
    INT $0x80