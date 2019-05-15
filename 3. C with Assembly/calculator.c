#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// do dyspozycji mam 8 128-bitowych rejestrów podzielonych na 4 32-bitowe elementy zmiennopozycyjne dodającaej precyzji
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

    obj.a = rand() % 100;
    obj.b = rand() % 100;
    obj.c = rand() % 100;
    obj.d = rand() % 100;

    return obj;
}



// ==========================================================
// SIMD
// ==========================================================

// funkcja dodawania w SIMD
// zwraca usredniony czas wykonania operacji
float addSIMD(int n) {
    // wynik pojedynczego dzialania
    float result[4];
    float num_a[4];
    float num_b[4];

    // przechowywanie sumy otrzymanych czasow
    int sumTime = 0;

    // powtarzam dla okreslonej ilosci liczb
    for(int i = 0; i < n; i++) {

        // wygenerowanie zestawu danych
        for(int j = 0; j < 4; j++) {
            // wygenerowanie pierwszej liczby
            Data data = generate();
            num_a[0] = data.a;
            num_a[1] = data.b;
            num_a[2] = data.c;
            num_a[3] = data.d;

            // wygenerowanie drugiej liczby
            data = generate();
            num_b[0] = data.a;
            num_b[1] = data.b;
            num_b[2] = data.c;
            num_b[3] = data.d;
        }
        
        // 10 pomiarow
        for(int j = 0; j < 10; j++) {

            //TODO tutaj odpalanie timera
            
            for(int k = 0; k < 4; k++) {
                // TODO instrukcja MOVUPS nie dziala
                __asm__(
                    "MOVUPS %1, %%xmm0 \n"         // wpisanie num_a do rejestru xmm0
                    "MOVUPS %2, %%xmm1 \n"         // wpisanie num_b do xmm1
                    "ADDPS %%xmm0, %%xmm1\n"       // wykonanie dodawania, wynik w xmm0
                    "MOVUPS %%xmm0, %0\n"          // zapisanie wyniku do zmiennej "sum"
                    : "=r"(result[k])              // wyjsciowe zmienne
                    : "r"(num_a[k]), "r"(num_b[k]) // wejsciowe zmienne
                    // : "%xmm0", "%xmm1"           // niszczone rejestry (opcjonalnie), czy tego potrzebuje? i tak zawsze w kolejnych dzialaniach bede nadpisywal te rejestry
                );
            }

            //TODO tutaj wylaczenie timera

            // czas pojedynczej iteracji
            // int time = ;

            // suma czasow ze wszystkich iteracji
            // sumTime += time;
        }
    }

    // obliczenie sredniej z 10 pomiarow, do tego uwzglednic jeszcze ilosc liczb
    float avgTime = sumTime / 10;

    // TODO przekonwertowac czas na sekundy, bo prawdopodobnie bedzie w ns
    return avgTime;
}


// dla tych wszystkich funkcji niżej bedzie dokładnie to samo co w dodawaniu tylko ze zmianą ADDPS odpowiednio na SUBPS, MULPS oraz DIVPS

//funkcja odejmowania w SIMD
// zwraca usredniony czas wykonania operacji
float subSIMD(int n) {

    return 1;
}


// funkcja mnozenia w SIMD
// zwraca usredniony czas wykonania operacji
float mulSIMD(int n) {

    return 1;
}


// funkcja dzielenia w SIMD
// zwraca usredniony czas wykonania operacji
float divSIMD(int n) {

    return 1;
}



// ==========================================================
// SISD
// ==========================================================




int main()
{
    // zagwarantowanie "prawdziwszej" losowosci
    srand(time(NULL));

    // ilosc liczb
    int n;

    // ==========================================================
    // SIMD

    n = 2048;
    printf("Typ obliczen: SIMD\n");
    printf("Liczba liczb: %d\n", n);
    printf("Sredni czas [s]:\n");
    printf("+ %f\n", addSIMD(n));
    printf("- %f\n", divSIMD(n));
    printf("* %f\n", mulSIMD(n));
    printf("/ %f\n", divSIMD(n));

    n = 4096;
    printf("\nTyp obliczen: SIMD\n");
    printf("Liczba liczb: %d\n", n);
    printf("Sredni czas [s]:\n");
    printf("+ %f\n", addSIMD(n));
    printf("- %f\n", divSIMD(n));
    printf("* %f\n", mulSIMD(n));
    printf("/ %f\n", divSIMD(n));

    n = 8192;
    printf("\nTyp obliczen: SIMD\n");
    printf("Liczba liczb: %d\n", n);
    printf("Sredni czas [s]:\n");
    printf("+ %f\n", addSIMD(n));
    printf("- %f\n", divSIMD(n));
    printf("* %f\n", mulSIMD(n));
    printf("/ %f\n", divSIMD(n));


    // ==========================================================
    // SISD

    return 0;
}