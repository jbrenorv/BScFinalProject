#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_EL 0
#define MAX_EL 100000000


void Mergesort(int l, int r, int *v, int *v_aux);
void Quicksort(int l, int r, int *v);


int main() {
    srand(time(NULL));

    int N = 1e7;

    int *v1    = (int *)malloc(N * sizeof(int));
    int *v2    = (int *)malloc(N * sizeof(int));
    int *v_aux = (int *)malloc(N * sizeof(int));

    if (v1 == NULL || v2 == NULL || v_aux == NULL) {
        printf("Erro ao tentar alocar memoria, finalizando...\n");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        int valor = (MIN_EL + rand() % (MAX_EL - MIN_EL + 1));
        v1[i] = valor;
        v2[i] = valor;
    }

    Mergesort(0, N, v1, v_aux);
    Quicksort(0, N - 1, v2);

    free(v1);
    free(v2);
    free(v_aux);

    return 0;
}

void Mergesort(int l, int r, int *v, int *v_aux) {
    int i, j, k, m;
    if (l < r - 1) {
        m = (l + r) / 2;
        Mergesort(l, m, v, v_aux);
        Mergesort(m, r, v, v_aux);

        // Merge
        for (i = l; i < r; i++) {
            v_aux[i] = v[i];
        }
        i = l;
        j = m;
        k = l;
        while (i < m && j < r) {
            if (v_aux[i] <= v_aux[j]) {
                v[k++] = v_aux[i++];
            }
            else {
                v[k++] = v_aux[j++];
            }
        }
        while (i < m) {
            v[k++] = v_aux[i++];
        }
    }
}

void Quicksort(int l, int r, int *v) {
    int pivo, p, t, i, j;
    while (l < r) {
        // Seleciona pivo e coloca na posicao r
        p = l + rand() % (r - l + 1);
        t = v[r]; v[r] = v[p]; v[p] = t;
        
        // Particiona
        pivo = v[r];
        j = l;
        for (i = l; i < r; i++) {
            if (v[i] <= pivo) {
                t = v[i]; v[i] = v[j]; v[j] = t;
                j++;
            }
        }
        v[r] = v[j];
        v[j] = pivo;

        // Rec
        if (j - l < r - j) {
            Quicksort(l, j - 1, v);
            l = j + 1;
        } else {
            Quicksort(j + 1, r, v);
            r = j - 1;
        }
    }
}
