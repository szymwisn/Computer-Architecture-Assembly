#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix {
    // a - pierwszy wiersz, b - drugi itd.
    float a[4], b[4], c[4], d[4];
} Matrix;

float countDET(Matrix M) {

    float det = 0;
    float result[4];

    __asm__(
        // ==============================
        // blok0    blok1
        // blok2    blok3
        // ==============================

        // ==============================
        // operacje dla wierszy a i b - blok0
        "MOVUPS %1, %%xmm0\n"
        "MOVUPS %2, %%xmm1\n"
        // 1 0 2 0
        "SHUFPS $0b01001000, %%xmm0, %%xmm0\n" // A'
        // 2 3 0 1
        "SHUFPS $0b10110001, %%xmm1, %%xmm1\n" // B'
        "MULPS %%xmm0, %%xmm1\n"               // A'B' w xmm1

        "MOVUPS %1, %%xmm2\n"
        "MOVUPS %2, %%xmm3\n"
        // 2 3 0 1
        "SHUFPS $0b10110001, %%xmm2, %%xmm2\n" // A''
        // 1 0 2 0
        "SHUFPS $0b01001000, %%xmm3, %%xmm3\n" // B''
        "MULPS %%xmm2, %%xmm3\n"               // A''B'' w xmm3

        "SUBPS %%xmm3, %%xmm1\n"  // A'B' - A''B'' w xmm1
        "MOVUPS %%xmm1, %%xmm7\n" // A'B' - A''B'' w xmm7

        // ==============================
        // operacje dla wierszy c i d - blok1
        "MOVUPS %3, %%xmm0\n"
        "MOVUPS %4, %%xmm1\n"
        // 0 1 1 2
        "SHUFPS $0b00010110, %%xmm0, %%xmm0\n" // C'
        // 3 2 3 3
        "SHUFPS $0b11101111, %%xmm1, %%xmm1\n" // D'
        "MULPS %%xmm0, %%xmm1\n"               // C'D' w xmm1

        "MOVUPS %3, %%xmm2\n"
        "MOVUPS %4, %%xmm3\n"
        // 3 2 3 3
        "SHUFPS $0b11101111, %%xmm2, %%xmm2\n" // C''
        // 0 1 1 2
        "SHUFPS $0b00010110, %%xmm3, %%xmm3\n" // D''
        "MULPS %%xmm2, %%xmm3\n"               // C''D'' w xmm3

        "SUBPS %%xmm3, %%xmm1\n"  // C'D' - C''D'' w xmm1
        "MOVUPS %%xmm1, %%xmm6\n" // C'D' - C''D'' w xmm6

        // ==============================
        // (A'B' - A''B'') * (C'D' - C''D'') w xmm6
        "MULPS %%xmm7, %%xmm6\n"

        // ==============================
        // tutaj pozostałe bloki na a i b - blok2
        "MOVUPS %1, %%xmm0\n"
        "MOVUPS %2, %%xmm1\n"
        // 0 0 3 2
        "SHUFPS $0b00001110, %%xmm0, %%xmm0\n" // A'
        // 0 0 1 3
        "SHUFPS $0b00000111, %%xmm1, %%xmm1\n" // B'
        "MULPS %%xmm0, %%xmm1\n"               // A'B' w xmm1

        "MOVUPS %1, %%xmm2\n"
        "MOVUPS %2, %%xmm3\n"
        // 0 0 1 3
        "SHUFPS $0b00000111, %%xmm2, %%xmm2\n" // A''
        // 0 0 3 2
        "SHUFPS $0b00001110, %%xmm3, %%xmm3\n" // B''
        "MULPS %%xmm2, %%xmm3\n"               // A''B'' w xmm3

        "SUBPS %%xmm3, %%xmm1\n"  // A'B' - A''B'' w xmm1
        "MOVUPS %%xmm1, %%xmm5\n" // A'B' - A''B'' w xmm5

        // ==============================
        // tutaj pozostałe bloki na c i d - blok3
        "MOVUPS %3, %%xmm0\n"
        "MOVUPS %4, %%xmm1\n"
        // 0 0 0 0
        "SHUFPS $0b00000000, %%xmm0, %%xmm0\n" // C'
        // 0 0 2 1
        "SHUFPS $0b00001001, %%xmm1, %%xmm1\n" // D'
        "MULPS %%xmm0, %%xmm1\n"               // C'D' w xmm1

        "MOVUPS %3, %%xmm2\n"
        "MOVUPS %4, %%xmm3\n"
        // 0 0 2 1
        "SHUFPS $0b00001001, %%xmm2, %%xmm2\n" // C''
        // 0 0 0 0
        "SHUFPS $0b00000000, %%xmm3, %%xmm3\n" // D''
        "MULPS %%xmm2, %%xmm3\n"               // C''D'' w xmm3

        "SUBPS %%xmm3, %%xmm1\n"  // C'D' - C''D'' w xmm1
        "MOVUPS %%xmm1, %%xmm4\n" // C'D' - C''D'' w xmm4

        // ==============================
        // (A'B' - A''B'') * (C'D' - C''D'') w xmm4
        "MULPS %%xmm5, %%xmm4\n"

        // ==============================
        // addition
        "ADDPS %%xmm4, %%xmm6\n" // w xmm6
        "MOVUPS %%xmm6, %0"

        : "=m"(result)
        : "m"(M.a), "m"(M.b), "m"(M.c), "m"(M.d)
    );

    det = result[0] + result[1] + result[2] + result[3];

    return det;
}

int main() {
    Matrix M;

    float data [4][4] = {
        {8, 1, 2, 4},
        {1, 0, 0, 7},
        {1, 2, 9, 8},
        {5, 8, 6, 2}
    };

    for (int i = 0; i < 4; i++) {
        M.a[i] = data[0][i];
        M.b[i] = data[1][i];
        M.c[i] = data[2][i];
        M.d[i] = data[3][i];
    }

    // wypisanie macierzy
    for (int i = 0; i < 4; i++) {
        printf("%f ", M.a[i]);
    }

    printf("\n");

    for (int i = 0; i < 4; i++) {
        printf("%f ", M.b[i]);
    }

    printf("\n");

    for (int i = 0; i < 4; i++) {
        printf("%f ", M.c[i]);
    }

    printf("\n");

    for (int i = 0; i < 4; i++) {
        printf("%f ", M.d[i]);
    }

    printf("\n");

    printf("\nWyznacznik powyzszej macierzy:\ndetM = %f\n", countDET(M));

    return 0;
}