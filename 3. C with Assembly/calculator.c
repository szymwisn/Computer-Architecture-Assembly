#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// do dyspozycji mam 8 128-bitowych rejestrów podzielonych na 4 32-bitowe elementy zmiennopozycyjne pojedynczej precyzji
// xmm0 - xmm7
// rejestr sterujący mxcsr



// struktura będzie przechowywała 128 bitową informację
// 32b * 4 = 128b
typedef struct Data {
    float a, b, c, d;
} Data;


// funkcja generująca 
Data generate() {
    Data obj;

    // + 1 zeby nie dzielic przez 0
    obj.a = (rand() % 1000) + 1;
    obj.b = (rand() % 1000) + 1;
    obj.c = (rand() % 1000) + 1;
    obj.d = (rand() % 1000) + 1;

    return obj;
}



// ==========================================================
// SIMD
// ==========================================================

// funkcja dodawania w SIMD
// zwraca usredniony czas wykonania operacji
double addSIMD(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for(int j = 0; j < 10; j++) {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++) {
            
            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();
            
             __asm__(
                "MOVUPS %1, %%xmm0 \n"         // wpisanie num_a do rejestru xmm0
                "MOVUPS %2, %%xmm1 \n"         // wpisanie num_b do xmm1
                "ADDPS %%xmm0, %%xmm1\n"       // wykonanie dodawania, wynik w xmm0
                "MOVUPS %%xmm0, %0\n"          // zapisanie wyniku do zmiennej "result"
                : "=g"(result)                 // wyjsciowe zmienne
                : "g"(num_a), "g"(num_b)       // wejsciowe zmienne
            );

             // pobranie taktu procesora
             clock_t end = clock();

             // suma czasow ze wszystkich iteracji
             sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }


    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}


//funkcja odejmowania w SIMD
// zwraca usredniony czas wykonania operacji
double subSIMD(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();

            __asm__(
                "MOVUPS %1, %%xmm0 \n"   // wpisanie num_a do rejestru xmm0
                "MOVUPS %2, %%xmm1 \n"   // wpisanie num_b do xmm1
                "SUBPS %%xmm0, %%xmm1\n" // wykonanie odejmowania, wynik w xmm0
                "MOVUPS %%xmm0, %0\n"    // zapisanie wyniku do zmiennej "result"
                : "=g"(result)           // wyjsciowe zmienne
                : "g"(num_a), "g"(num_b) // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}


// funkcja mnozenia w SIMD
// zwraca usredniony czas wykonania operacji
double mulSIMD(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();

            __asm__(
                "MOVUPS %1, %%xmm0 \n"   // wpisanie num_a do rejestru xmm0
                "MOVUPS %2, %%xmm1 \n"   // wpisanie num_b do xmm1
                "MULPS %%xmm0, %%xmm1\n" // wykonanie mnozenia, wynik w xmm0
                "MOVUPS %%xmm0, %0\n"    // zapisanie wyniku do zmiennej "result"
                : "=g"(result)           // wyjsciowe zmienne
                : "g"(num_a), "g"(num_b) // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}


// funkcja dzielenia w SIMD
// zwraca usredniony czas wykonania operacji
double divSIMD(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();

            __asm__(
                "MOVUPS %1, %%xmm0 \n"   // wpisanie num_a do rejestru xmm0
                "MOVUPS %2, %%xmm1 \n"   // wpisanie num_b do xmm1
                "DIVPS %%xmm0, %%xmm1\n" // wykonanie dzielenia, wynik w xmm0
                "MOVUPS %%xmm0, %0\n"    // zapisanie wyniku do zmiennej "result"
                : "=g"(result)           // wyjsciowe zmienne
                : "g"(num_a), "g"(num_b) // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}



// ==========================================================
// SISD
// ==========================================================

// funkcja dodawania w SISD
// zwraca usredniony czas wykonania operacji
double addSISD(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();

            __asm__(
                "MOVL %1, %%eax \n"          // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"          // wpisanie num_b do ebx
                "ADDL %%eax, %%ebx\n"        // wykonanie dzialania
                "MOVL %%eax, %0\n"           // zapisanie wyniku do zmiennej "result"
                : "=g"(result.a)               // wyjsciowe zmienne
                : "g"(num_a.a), "g"(num_b.a) // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "ADDL %%eax, %%ebx\n"         // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.b)                // wyjsciowe zmienne
                : "g"(num_a.b), "g"(num_b.b)  // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "ADDL %%eax, %%ebx\n"         // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.c)                // wyjsciowe zmienne
                : "g"(num_a.c), "g"(num_b.c)  // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "ADDL %%eax, %%ebx\n"         // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.d)                // wyjsciowe zmienne
                : "g"(num_a.d), "g"(num_b.d)  // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}

//funkcja odejmowania w SISD
// zwraca usredniony czas wykonania operacji
double subSISD(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "SUBL %%eax, %%ebx\n"         // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.a)                // wyjsciowe zmienne
                : "g"(num_a.a), "g"(num_b.a)  // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "SUBL %%eax, %%ebx\n"         // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.b)                // wyjsciowe zmienne
                : "g"(num_a.b), "g"(num_b.b)  // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "SUBL %%eax, %%ebx\n"         // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.c)                // wyjsciowe zmienne
                : "g"(num_a.c), "g"(num_b.c)  // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "SUBL %%eax, %%ebx\n"         // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.d)                // wyjsciowe zmienne
                : "g"(num_a.d), "g"(num_b.d)  // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}

// funkcja mnozenia w SISD
// zwraca usredniony czas wykonania operacji
double mulSISD(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "MULL %%ebx\n"                // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.a)              // wyjsciowe zmienne
                : "g"(num_a.a), "g"(num_b.a)  // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "MULL %%ebx\n"                // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.b)              // wyjsciowe zmienne
                : "g"(num_a.b), "g"(num_b.b)  // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "MULL %%eax\n"                // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.c)              // wyjsciowe zmienne
                : "g"(num_a.c), "g"(num_b.c)  // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"           // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"           // wpisanie num_b do ebx
                "MULL %%ebx\n"                // wykonanie dzialania
                "MOVL %%eax, %0\n"            // zapisanie wyniku do zmiennej "result"
                : "=g"(result.d)              // wyjsciowe zmienne
                : "g"(num_a.d), "g"(num_b.d)  // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}

// funkcja dzielenia w SISD
// zwraca usredniony czas wykonania operacji
double divSISD(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();

            __asm__(
                "MOVL %1, %%eax \n"          // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"          // wpisanie num_b do ebx
                "MOVL $0, %%edx\n"           // wyzerowanie edx - reszty z dzielenia
                "DIVL %%ebx\n"               // wykonanie dzialania
                "MOVL %%eax, %0\n"           // zapisanie wyniku do zmiennej "result"
                : "=g"(result.a)             // wyjsciowe zmienne
                : "g"(num_a.a), "g"(num_b.a) // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"          // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"          // wpisanie num_b do ebx
                "MOVL $0, %%edx\n"           // wyzerowanie edx - reszty z dzielenia
                "DIVL %%ebx\n"               // wykonanie dzialania
                "MOVL %%eax, %0\n"           // zapisanie wyniku do zmiennej "result"
                : "=g"(result.b)             // wyjsciowe zmienne
                : "g"(num_a.b), "g"(num_b.b) // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"          // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"          // wpisanie num_b do ebx
                "MOVL $0, %%edx\n"           // wyzerowanie edx - reszty z dzielenia
                "DIVL %%ebx\n"               // wykonanie dzialania
                "MOVL %%eax, %0\n"           // zapisanie wyniku do zmiennej "result"
                : "=g"(result.c)             // wyjsciowe zmienne
                : "g"(num_a.c), "g"(num_b.c) // wejsciowe zmienne
            );

            __asm__(
                "MOVL %1, %%eax \n"          // wpisanie num_a do rejestru eax
                "MOVL %2, %%ebx \n"          // wpisanie num_b do ebx
                "MOVL $0, %%edx\n"           // wyzerowanie edx - reszty z dzielenia
                "DIVL %%ebx\n"               // wykonanie dzialania
                "MOVL %%eax, %0\n"           // zapisanie wyniku do zmiennej "result"
                : "=g"(result.d)             // wyjsciowe zmienne
                : "g"(num_a.d), "g"(num_b.d) // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}



// ==========================================================
// SISD - 2 wariant
// ==========================================================

// funkcja dodawania w SISD
// zwraca usredniony czas wykonania operacji
double addSISD2(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FADDP\n"                     // wykonanie operacji
                : "=m"(result.a)              // wyjsciowe zmienne
                : "m"(num_a.a), "m"(num_b.a)  // wejsciowe zmienne
            );

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FADDP\n"                     // wykonanie operacji
                : "=m"(result.b)              // wyjsciowe zmienne
                : "m"(num_a.b), "m"(num_b.b)  // wejsciowe zmienne
            );

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FADDP\n"                     // wykonanie operacji
                : "=m"(result.c)              // wyjsciowe zmienne
                : "m"(num_a.c), "m"(num_b.c)  // wejsciowe zmienne
            );

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FADDP\n"                     // wykonanie operacji
                : "=m"(result.d)              // wyjsciowe zmienne
                : "m"(num_a.d), "m"(num_b.d)  // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}

//funkcja odejmowania w SISD
// zwraca usredniony czas wykonania operacji
double subSISD2(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FSUBP\n"                     // wykonanie operacji
                : "=m"(result.a)              // wyjsciowe zmienne
                : "m"(num_a.a), "m"(num_b.a)  // wejsciowe zmienne
            );

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FSUBP\n"                     // wykonanie operacji
                : "=m"(result.b)              // wyjsciowe zmienne
                : "m"(num_a.b), "m"(num_b.b)  // wejsciowe zmienne
            );

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FSUBP\n"                     // wykonanie operacji
                : "=m"(result.c)              // wyjsciowe zmienne
                : "m"(num_a.c), "m"(num_b.c)  // wejsciowe zmienne
            );

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FSUBP\n"                     // wykonanie operacji
                : "=m"(result.d)              // wyjsciowe zmienne
                : "m"(num_a.d), "m"(num_b.d)  // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}

// funkcja mnozenia w SISD
// zwraca usredniony czas wykonania operacji
double mulSISD2(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();
            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FMULP\n"                     // wykonanie operacji
                : "=m"(result.a)              // wyjsciowe zmienne
                : "m"(num_a.a), "m"(num_b.a)  // wejsciowe zmienne
            );

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FMULP\n"                     // wykonanie operacji
                : "=m"(result.b)              // wyjsciowe zmienne
                : "m"(num_a.b), "m"(num_b.b)  // wejsciowe zmienne
            );

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FMULP\n"                     // wykonanie operacji
                : "=m"(result.c)              // wyjsciowe zmienne
                : "m"(num_a.c), "m"(num_b.c)  // wejsciowe zmienne
            );
            
            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FMULP\n"                     // wykonanie operacji
                : "=m"(result.d)              // wyjsciowe zmienne
                : "m"(num_a.d), "m"(num_b.d)  // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}

// funkcja dzielenia w SISD
// zwraca usredniony czas wykonania operacji
double divSISD2(int n) {
    // wynik pojedynczego dzialania
    Data result;

    // dodawane liczby
    Data num_a;
    Data num_b;

    // przechowywanie sumy otrzymanych czasow
    double sumTime = 0;

    // 10 pomiarow
    for (int j = 0; j < 10; j++)
    {
        // dzialanie na n liczb
        for (int i = 0; i < n; i++)
        {

            num_a = generate();
            num_b = generate();

            // pobranie taktu procesora
            clock_t begin = clock();

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FDIVP\n"                     // wykonanie operacji
                : "=m"(result.a)              // wyjsciowe zmienne
                : "m"(num_a.a), "m"(num_b.a)  // wejsciowe zmienne
            );

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FDIVP\n"                     // wykonanie operacji
                : "=m"(result.b)              // wyjsciowe zmienne
                : "m"(num_a.b), "m"(num_b.b)  // wejsciowe zmienne
            );

            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FDIVP\n"                     // wykonanie operacji
                : "=m"(result.c)              // wyjsciowe zmienne
                : "m"(num_a.c), "m"(num_b.c)  // wejsciowe zmienne
            );
            
            __asm__(
                "FLD %2\n"                    // zaladowanie pierwszej liczby
                "FLD %1\n"                    // zaladowanie drugiej liczby
                "FDIVP\n"                     // wykonanie operacji
                : "=m"(result.d)              // wyjsciowe zmienne
                : "m"(num_a.d), "m"(num_b.d)  // wejsciowe zmienne
            );

            // pobranie taktu procesora
            clock_t end = clock();

            // suma czasow ze wszystkich iteracji
            sumTime += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }

    // obliczenie sredniej z 10 pomiarow
    double avgTime = sumTime / 10;

    return avgTime;
}

int main() {
    // zagwarantowanie "prawdziwszej" losowosci
    srand(time(NULL));

    // ilosc liczb
    int n;

    FILE *f;
    f = fopen("results.txt", "w");



    // ==========================================================
    // SIMD

    n = 2048;
    fprintf(f, "Typ obliczen: SIMD\n");
    fprintf(f, "Liczba liczb: %d\n", n);
    fprintf(f, "Sredni czas [s]:\n");
    fprintf(f, "+ %f\n", addSIMD(n));
    fprintf(f, "- %f\n", subSIMD(n));
    fprintf(f, "* %f\n", mulSIMD(n));
    fprintf(f, "/ %f\n", divSIMD(n));

    n = 4096;
    fprintf(f, "\nTyp obliczen: SIMD\n");
    fprintf(f, "Liczba liczb: %d\n", n);
    fprintf(f, "Sredni czas [s]:\n");
    fprintf(f, "+ %f\n", addSIMD(n));
    fprintf(f, "- %f\n", subSIMD(n));
    fprintf(f, "* %f\n", mulSIMD(n));
    fprintf(f, "/ %f\n", divSIMD(n));

    n = 8192;
    fprintf(f, "\nTyp obliczen: SIMD\n");
    fprintf(f, "Liczba liczb: %d\n", n);
    fprintf(f, "Sredni czas [s]:\n");
    fprintf(f, "+ %f\n", addSIMD(n));
    fprintf(f, "- %f\n", subSIMD(n));
    fprintf(f, "* %f\n", mulSIMD(n));
    fprintf(f, "/ %f\n", divSIMD(n));

    fprintf(f, "\n============================================\n\n");



    // ==========================================================
    // SISD

    n = 2048;
    fprintf(f, "Typ obliczen: SISD\n");
    fprintf(f, "Liczba liczb: %d\n", n);
    fprintf(f, "Sredni czas [s]:\n");
    fprintf(f, "+ %f\n", addSISD(n));
    fprintf(f, "- %f\n", subSISD(n));
    fprintf(f, "* %f\n", mulSISD(n));
    fprintf(f, "/ %f\n", divSISD(n));

    n = 4096;
    fprintf(f, "\nTyp obliczen: SISD\n");
    fprintf(f, "Liczba liczb: %d\n", n);
    fprintf(f, "Sredni czas [s]:\n");
    fprintf(f, "+ %f\n", addSISD(n));
    fprintf(f, "- %f\n", subSISD(n));
    fprintf(f, "* %f\n", mulSISD(n));
    fprintf(f, "/ %f\n", divSISD(n));

    n = 8192;
    fprintf(f, "\nTyp obliczen: SISD\n");
    fprintf(f, "Liczba liczb: %d\n", n);
    fprintf(f, "Sredni czas [s]:\n");
    fprintf(f, "+ %f\n", addSISD(n));
    fprintf(f, "- %f\n", subSISD(n));
    fprintf(f, "* %f\n", mulSISD(n));
    fprintf(f, "/ %f\n", divSISD(n));

    fprintf(f, "\n============================================\n\n");



    // ==========================================================
    // SISD 2

    n = 2048;
    fprintf(f, "Typ obliczen: SISD2\n");
    fprintf(f, "Liczba liczb: %d\n", n);
    fprintf(f, "Sredni czas [s]:\n");
    fprintf(f, "+ %f\n", addSISD2(n));
    fprintf(f, "- %f\n", subSISD2(n));
    fprintf(f, "* %f\n", mulSISD2(n));
    fprintf(f, "/ %f\n", divSISD2(n));

    n = 4096;
    fprintf(f, "\nTyp obliczen: SISD2\n");
    fprintf(f, "Liczba liczb: %d\n", n);
    fprintf(f, "Sredni czas [s]:\n");
    fprintf(f, "+ %f\n", addSISD2(n));
    fprintf(f, "- %f\n", subSISD2(n));
    fprintf(f, "* %f\n", mulSISD2(n));
    fprintf(f, "/ %f\n", divSISD2(n));

    n = 8192;
    fprintf(f, "\nTyp obliczen: SISD2\n");
    fprintf(f, "Liczba liczb: %d\n", n);
    fprintf(f, "Sredni czas [s]:\n");
    fprintf(f, "+ %f\n", addSISD2(n));
    fprintf(f, "- %f\n", subSISD2(n));
    fprintf(f, "* %f\n", mulSISD2(n));
    fprintf(f, "/ %f\n", divSISD2(n));

    return 0;
}