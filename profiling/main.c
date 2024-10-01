#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "../src/ordenacao.h"


int main(int argc, char **argv) {
    srand(time(NULL));

    int N = atoi(argv[1]);

    int *vetor_original = CriaVetor(N, ALE);
    int *vetor = AlocaVetor(N);

    void (*algoritmo[])(int, int *) = {
        // Bolha,
        // Coquetel,
        // Selecao,
        // Insercao,
        // Shellsort,
        // Mergesort,
        // Heapsort,
        // Quicksort,
        // QuicksortI,
        // Introsort,
        Countingsort,
        Bucketsort,
        RadixsortC,
        RadixsortB
    };

    int k = sizeof(algoritmo) / sizeof(void (*)(int, int *));

    for (int i = 0; i < k; i++) {
        CopiaVetor(N, vetor_original, vetor);
        algoritmo[i](N, vetor);
    }

    free(vetor_original);
    free(vetor);

    return 0;
}
