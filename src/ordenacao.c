#include "ordenacao.h"


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>


void Bolha(int n, int *v) {
    char trocou = 1;
    for (int i = n - 1; i > 0 && trocou; i--) {
        trocou = 0;
        for (int j = 0; j < i; j++)
            if (v[j] > v[j + 1]) {
                Troca(v + j, v + j + 1);
                trocou = 1;
            }
    }
}


void Bolha_CD(int n, int *v, Dados *dados) {
    char trocou = 1;
    for (int i = n - 1; i > 0 && trocou; i--) {
        trocou = 0;
        for (int j = 0; j < i; j++) {
            if (v[j] > v[j + 1]) {
                Troca(v + j, v + j + 1);
                trocou = 1;
                dados->movimentacoes += 3;
            }
            dados->comparacoes++;
        }
    }
}


void Coquetel(int n, int *v) {
    char trocou = 1;
    for (int i = 0, j = n - 1; i < j && trocou; i++, j--) {
        trocou = 0;
        for (int k = i; k < j; k++)
            if (v[k] > v[k + 1])
                Troca(v + k, v + k + 1), trocou = 1;
        if (trocou) trocou = 0;
        else return;
        for (int k = j - 2; k >= i; k--)
            if (v[k] > v[k + 1])
                Troca(v + k, v + k + 1), trocou = 1;
    }
}


void Coquetel_CD(int n, int *v, Dados *dados) {
    char trocou = 1;
    for (int i = 0, j = n - 1; i < j && trocou; i++, j--) {
        trocou = 0;
        for (int k = i; k < j; k++) {
            if (v[k] > v[k + 1]) {
                Troca(v + k, v + k + 1);
                trocou = 1;
                dados->movimentacoes += 3;
            }
            dados->comparacoes++;
        }
        if (trocou) trocou = 0;
        else return;
        for (int k = j - 2; k >= i; k--) {
            if (v[k] > v[k + 1]) {
                Troca(v + k, v + k + 1);
                trocou = 1;
                dados->movimentacoes += 3;
            }
            dados->comparacoes++;
        }
    }
}


void Selecao(int n, int *v) {
    for (int i = 0; i < n - 1; i++) {
        int j = i;
        for (int k = i + 1; k < n; k++)
            if (v[j] > v[k])
                j = k;
        if (j > i) Troca(v + i, v + j);
    }
}


void Selecao_CD(int n, int *v, Dados *dados) {
    for (int i = 0; i < n - 1; i++) {
        int j = i;
        for (int k = i + 1; k < n; k++) {
            if (v[j] > v[k])
                j = k;
            dados->comparacoes++;
        }
        if (j > i) {
            Troca(v + i, v + j);
            dados->movimentacoes += 3;
        }
    }
}


void H_Ordena(int n, int h, int *v) {
    int chave, j;
    for (int i = h; i < n; i++) {
        chave = v[i];
        for (j = i; j >= h && v[j - h] > chave; j -= h)
            v[j] = v[j - h];
        v[j] = chave;
    }
}


void H_Ordena_CD(int n, int h, int *v, Dados *dados) {
    int chave, j;
    for (int i = h; i < n; i++) {
        chave = v[i];
        for (j = i; j >= h && v[j - h] > chave; j -= h) {
            v[j] = v[j - h];
            dados->comparacoes++;
            dados->movimentacoes++;
        }
        v[j] = chave;
        if (j >= h) dados->comparacoes++;
        dados->movimentacoes += 2;
    }
}


void Insercao(int n, int *v) {
    H_Ordena(n, 1, v);
}


void Insercao_CD(int n, int *v, Dados *dados) {
    H_Ordena_CD(n, 1, v, dados);
}


// [Artigo] Marcin Ciura 2001: Best Increments for the Average Case of Shellsort
// [ PDF  ] https://web.archive.org/web/20180923235211/http://sun.aei.polsl.pl/~mciura/publikacje/shellsort.pdf
// CiuraOriginalSeq = 1, 4, 10, 23, 57, 132, 301, 701, 1750
// CiuraSeq[i] = (i < 10 ? CiuraOriginalSeq[i] : 2.25 * Ciura[i - 1])
// Os 24 primeiros elementos invertidos:
int const CiuraSeq[] = { 335622013, 149165339, 66295706, 29464758, 13095448, 5820199, 2586755, 1149669, 510964, 227095, 100931, 44858, 19937, 8861, 3938, 1750, 701, 301, 132, 57, 23, 10, 4, 1 };


void Shellsort(int n, int *v) {
    for (int i = 0; i < 24; i++)
        H_Ordena(n, CiuraSeq[i], v);
}


void Shellsort_CD(int n, int *v, Dados *dados) {
    for (int i = 0; i < 24; i++)
        H_Ordena_CD(n, CiuraSeq[i], v, dados);
}


void Mergesort(int n, int *v) {
    int *v_aux = AlocaVetor(n);
    MergesortRec(0, n, v, v_aux);
    free(v_aux);
}


void MergesortRec(int l, int r, int *v, int *v_aux) {
    if (l < r - 1) {
        int m = (l + r) / 2;
        MergesortRec(l, m, v, v_aux);
        MergesortRec(m, r, v, v_aux);
        Merge(l, m, r, v, v_aux);
    }
}


void Merge(int l, int m, int r, int *v, int *v_aux) {
    CopiaVetor(r - l, v + l, v_aux + l);
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (v_aux[i] <= v_aux[j]) {
            v[k++] = v_aux[i++];
        } else {
            v[k++] = v_aux[j++];
        }
    }
    while (i < m) {
        v[k++] = v_aux[i++];
    }
}


void Mergesort_CD(int n, int *v, Dados *dados) {
    int *v_aux = AlocaVetor(n);
    MergesortRec_CD(0, n, v, v_aux, dados);
    free(v_aux);
}


void MergesortRec_CD(int l, int r, int *v, int *v_aux, Dados *dados) {
    if (l < r - 1) {
        int m = (l + r) / 2;
        MergesortRec_CD(l, m, v, v_aux, dados);
        MergesortRec_CD(m, r, v, v_aux, dados);
        Merge_CD(l, m, r, v, v_aux, dados);
    }
}


void Merge_CD(int l, int m, int r, int *v, int *v_aux, Dados *dados) {
    CopiaVetor(r - l, v + l, v_aux + l);
    dados->movimentacoes += r - l;
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (v_aux[i] <= v_aux[j]) v[k++] = v_aux[i++];
        else v[k++] = v_aux[j++];
        dados->comparacoes++;
        dados->movimentacoes++;
    }
    while (i < m) {
        v[k++] = v_aux[i++];
        dados->movimentacoes++;
    }
}


void Heapsort(int n, int *v) {
    ConstroiHeap(n, v);
    for (int i = n - 1; i > 0; i--) {
        Troca(v, v + i);
        Heapifica(0, i, v);
    }
}


void ConstroiHeap(int n, int *v) {
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapifica(i, n, v);
}


void Heapifica(int i, int n, int *v) {
    int chave = v[i], j = 2 * i + 1;
    while (j < n) {
        if (j < n - 1 && v[j] < v[j + 1]) j++;
        if (chave >= v[j]) break;
        v[i] = v[j];
        i = j;
        j = 2 * j + 1;
    }
    v[i] = chave;
}


void Heapsort_CD(int n, int *v, Dados *dados) {
    ConstroiHeap_CD(n, v, dados);
    for (int i = n - 1; i > 0; i--) {
        Troca(v, v + i);
        Heapifica_CD(0, i, v, dados);
        dados->movimentacoes += 3;
    }
}


void ConstroiHeap_CD(int n, int *v, Dados *dados) {
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapifica_CD(i, n, v, dados);
}


void Heapifica_CD(int i, int n, int *v, Dados *dados) {
    int chave = v[i], j = 2 * i + 1;
    dados->movimentacoes++;
    while (j < n) {
        if (j < n - 1) {
            if (v[j] < v[j + 1]) j++;
            dados->comparacoes++;
        }
        if (chave >= v[j]) {
            dados->comparacoes++;
            break;
        }
        v[i] = v[j];
        i = j;
        j = 2 * j + 1;
        dados->movimentacoes++;
    }
    v[i] = chave;
    dados->movimentacoes++;
}


void Quicksort(int n, int *v) {
    QuicksortRec(0, n - 1, v);
}


void QuicksortRec(int l, int r, int *v) {
    while (l < r) {
        int j = Particiona(l, r, v);
        if (j - l < r - j) {
            QuicksortRec(l, j - 1, v);
            l = j + 1;
        } else {
            QuicksortRec(j + 1, r, v);
            r = j - 1;
        }
    }
}


void Quicksort_CD(int n, int *v, Dados *dados) {
    QuicksortRec_CD(0, n - 1, v, dados);
}


void QuicksortRec_CD(int l, int r, int *v, Dados *dados) {
    while (l < r) {
        int j = Particiona_CD(l, r, v, dados);
        if (j - l < r - j) {
            QuicksortRec_CD(l, j - 1, v, dados);
            l = j + 1;
        } else {
            QuicksortRec_CD(j + 1, r, v, dados);
            r = j - 1;
        }
    }
}


void QuicksortI(int n, int *v) {
    QuicksortIRec(0, n - 1, v);
    Insercao(n, v);
}


void QuicksortIRec(int l, int r, int *v) {
    while (r - l > QS_LIMITE) {
        int j = Particiona(l, r, v);
        if (j - l < r - j) {
            QuicksortIRec(l, j, v);
            l = j + 1;
        } else {
            QuicksortIRec(j, r, v);
            r = j - 1;
        }
    }
}


void QuicksortI_CD(int n, int *v, Dados *dados) {
    QuicksortIRec_CD(0, n - 1, v, dados);
    Insercao_CD(n, v, dados);
}


void QuicksortIRec_CD(int l, int r, int *v, Dados *dados) {
    while (r - l > QS_LIMITE) {
        int j = Particiona_CD(l, r, v, dados);
        if (j - l < r - j) {
            QuicksortIRec_CD(l, j, v, dados);
            l = j + 1;
        } else {
            QuicksortIRec_CD(j, r, v, dados);
            r = j - 1;
        }
    }
}


void Introsort(int n, int *v) {
    IntrosortRec(0, n - 1, log2(n) * 2, v);
    Insercao(n, v);
}


void IntrosortRec(int l, int r, int d, int *v) {
    while (r - l > QS_LIMITE) {
        if (d == 0) {
            Heapsort(r - l + 1, v + l);
            return;
        }
        --d;
        int j = Particiona2(l, r, v);
        IntrosortRec(l, j, d, v);
        l = j + 1;
    }
}


void Introsort_CD(int n, int *v, Dados *dados) {
    IntrosortRec_CD(0, n - 1, log2(n) * 2, v, dados);
    Insercao_CD(n, v, dados);
}


void IntrosortRec_CD(int l, int r, int d, int *v, Dados *dados) {
    while (r - l > QS_LIMITE) {
        if (d == 0) {
            Heapsort_CD(r - l + 1, v + l, dados);
            return;
        }
        --d;
        int j = Particiona2_CD(l, r, v, dados);
        IntrosortRec_CD(l, j, d, v, dados);
        l = j + 1;
    }
}


int Particiona(int l, int r, int *v) {
    Troca(v + r, v + GeraNumeroAleatorioNoIntervalo(l, r));
    int pivo = v[r], j = l;
    for (int i = l; i < r; i++)
        if (v[i] <= pivo) {
            Troca(v + j, v + i);
            j++;
        }
    v[r] = v[j]; v[j] = pivo;
    return j;
}


int Particiona_CD(int l, int r, int *v, Dados *dados) {
    Troca(v + r, v + GeraNumeroAleatorioNoIntervalo(l, r));
    int pivo = v[r], j = l;
    for (int i = l; i < r; i++) {   
        if (v[i] <= pivo) {
            Troca(v + j, v + i);
            j++;
            dados->movimentacoes += 3;
        }
        dados->comparacoes++;
    }
    v[r] = v[j]; v[j] = pivo;
    dados->movimentacoes += 6;
    return j;
}


int Particiona2(int l, int r, int *v) {
    MoveMedianaFim(l, r, v);
    int pivot = v[r], i = l - 1, j = r + 1;
    while (1) {
        do --j; while (v[j] > pivot);
        do ++i; while (v[i] < pivot);
        if (i >= j) break;
        Troca(v + i, v + j);
    }
    return j;
}


int Particiona2_CD(int l, int r, int *v, Dados *dados) {
    MoveMedianaFim_CD(l, r, v, dados);
    int pivot = v[r], i = l - 1, j = r + 1;
    while (1) {
        do {
            --j;
            dados->comparacoes++;
        } while (v[j] > pivot);
        do {
            ++i;
            dados->comparacoes++;
        } while (v[i] < pivot);
        if (i >= j) break;
        Troca(v + i, v + j);
        dados->movimentacoes += 3;
    }
    return j;
}


void MoveMedianaFim(int l, int r, int *v) {
    int m = (l + r) / 2;
    if (v[l] < v[m]) Troca(v + l, v + m);
    if (v[r] < v[m]) Troca(v + r, v + m);
    if (v[l] < v[r]) Troca(v + l, v + r);
}


void MoveMedianaFim_CD(int l, int r, int *v, Dados *dados) {
    int m = (l + r) / 2;
    if (v[l] < v[m]) {
        Troca(v + l, v + m);
        dados->movimentacoes += 3;
    }
    if (v[r] < v[m]) {
        Troca(v + r, v + m);
        dados->movimentacoes += 3;
    }
    if (v[l] < v[r]) {
        Troca(v + l, v + r);
        dados->movimentacoes += 3;
    }
    dados->comparacoes += 3;
}


void Countingsort(int n, int *v) {
    int maior_el = MaxEl(n, v);
    int *cont = AlocaVetorLimpo(maior_el + 1);
    int *v_aux = AlocaVetor(n);
    for (int i = 0; i < n; i++) {
        cont[v[i]]++;
    }
    for (int i = 1; i <= maior_el; i++) {
        cont[i] += cont[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        v_aux[cont[v[i]] - 1] = v[i];
        cont[v[i]]--;
    }
    for (int i = 0; i < n; i++) {
        v[i] = v_aux[i];
    }
    free(cont);
    free(v_aux);
}


void Countingsort_CD(int n, int *v, Dados *dados) {
    int maior_el = MaxEl_CD(n, v, dados);
    int *cont = AlocaVetorLimpo(maior_el + 1);
    int *v_aux = AlocaVetor(n);
    for (int i = 0; i < n; i++) {
        cont[v[i]]++;
    }
    for (int i = 1; i <= maior_el; i++) {
        cont[i] += cont[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        v_aux[cont[v[i]] - 1] = v[i];
        cont[v[i]]--;
        dados->movimentacoes++;
    }
    for (int i = 0; i < n; i++) {
        v[i] = v_aux[i];
        dados->movimentacoes++;
    }
    free(cont);
    free(v_aux);
}


void Bucketsort(int n, int *v) {
    Celula **bucket = (Celula **) malloc(n * sizeof(Celula*));
    int maior_el = MaxEl(n, v);
    double t = ceil((maior_el + 1) / (double) n);
    for (int i = 0; i < n; i++) {
        bucket[i] = NULL;
    }
    for (int i = n - 1; i >= 0; i--) {
        int j = (int) floor(v[i] / t);
        InsereOrdenado(v[i], &bucket[j]);
    }
    for (int i = 0, k = 0; i < n; i++) {
        Celula *atual = bucket[i];
        while (atual != NULL) {
            v[k++] = atual->valor;
            Celula *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(bucket);
}


void Bucketsort_CD(int n, int *v, Dados *dados) {
    Celula **bucket = (Celula **) malloc(n * sizeof(Celula*));
    int maior_el = MaxEl_CD(n, v, dados);
    double t = ceil((maior_el + 1) / (double) n);
    for (int i = 0; i < n; i++) {
        bucket[i] = NULL;
    }
    for (int i = n - 1; i >= 0; i--) {
        int j = (int) floor(v[i] / t);
        InsereOrdenado_CD(v[i], &bucket[j], dados);
    }
    for (int i = 0, k = 0; i < n; i++) {
        Celula *atual = bucket[i];
        while (atual != NULL) {
            v[k++] = atual->valor;
            Celula *temp = atual;
            atual = atual->prox;
            free(temp);
            dados->movimentacoes++;
        }
    }
    free(bucket);
}


void RadixsortC(int n, int *v) {
    int maior_el = MaxEl(n, v);
    int *cont = AlocaVetor(10);
    int *v_aux = AlocaVetor(n);
    for (int p = 1; maior_el / p > 0; p *= 10) {
        for (int i = 0; i < 10; i++) {
            cont[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            cont[(v[i] / p) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            cont[i] += cont[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            int j = (v[i] / p) % 10;
            v_aux[cont[j] - 1] = v[i];
            cont[j]--;
        }
        for (int i = 0; i < n; i++) {
            v[i] = v_aux[i];
        }
    }
    free(cont);
    free(v_aux);
}


void RadixsortC_CD(int n, int *v, Dados *dados) {
    int *cont = AlocaVetor(10);
    int *v_aux = AlocaVetor(n);
    int maior_el = MaxEl_CD(n, v, dados);
    for (int p = 1; maior_el / p > 0; p *= 10) {
        for (int i = 0; i < 10; i++) {
            cont[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            cont[(v[i] / p) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            cont[i] += cont[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            int j = (v[i] / p) % 10;
            v_aux[cont[j] - 1] = v[i];
            cont[j]--;
            dados->movimentacoes++;
        }
        for (int i = 0; i < n; i++) {
            v[i] = v_aux[i];
            dados->movimentacoes++;
        }
    }
    free(cont);
    free(v_aux);
}


void RadixsortB(int n, int *v) {
    Celula **celula = (Celula**) malloc( n * sizeof(Celula*));
    Celula **bucket = (Celula**) malloc(10 * sizeof(Celula*));
    int maior_el = MaxEl(n, v);
    for (int i = 0; i < 10; i++) {
        bucket[i] = NULL;
    }
    for (int i = 0; i < n; i++) {
        celula[i] = (Celula *) malloc(sizeof(Celula));
        celula[i]->prox = NULL;
    }
    for (int p = 1; maior_el / p > 0; p *= 10) {
        for (int i = n - 1; i >= 0; i--) {
            int j = (v[i] / p) % 10;
            celula[i]->valor = v[i];
            celula[i]->prox = bucket[j];
            bucket[j] = celula[i];
        }
        for (int i = 0, k = 0; i < 10; i++) {
            while (bucket[i] != NULL) {
                v[k++] = bucket[i]->valor;
                bucket[i] = bucket[i]->prox;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        free(celula[i]);
    }
    free(celula);
    free(bucket);
}


void RadixsortB_CD(int n, int *v, Dados *dados) {
    Celula **celula = (Celula**) malloc( n * sizeof(Celula*));
    Celula **bucket = (Celula**) malloc(10 * sizeof(Celula*));
    int maior_el = MaxEl_CD(n, v, dados);
    for (int i = 0; i < 10; i++) {
        bucket[i] = NULL;
    }
    for (int i = 0; i < n; i++) {
        celula[i] = (Celula *) malloc(sizeof(Celula));
        celula[i]->prox = NULL;
    }
    for (int p = 1; maior_el / p > 0; p *= 10) {
        for (int i = n - 1; i >= 0; i--) {
            int j = (v[i] / p) % 10;
            celula[i]->valor = v[i];
            celula[i]->prox = bucket[j];
            bucket[j] = celula[i];
            dados->movimentacoes += 3;
        }
        for (int i = 0, k = 0; i < 10; i++) {
            while (bucket[i] != NULL) {
                v[k++] = bucket[i]->valor;
                bucket[i] = bucket[i]->prox;
                dados->movimentacoes += 2;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        free(celula[i]);
    }
    free(celula);
    free(bucket);
}


void InsereOrdenado(int valor, Celula **bucket) {
    Celula *celula = (Celula *) malloc(sizeof(Celula));
    celula->valor = valor;
    celula->prox = NULL;
    if (*bucket == NULL || (*bucket)->valor >= valor) {
        celula->prox = *bucket;
        *bucket = celula;
    } else {
        Celula *atual = *bucket;
        while (atual->prox && atual->prox->valor < valor)
            atual = atual->prox;
        celula->prox = atual->prox;
        atual->prox = celula;
    }
}


void InsereOrdenado_CD(int valor, Celula **bucket, Dados *dados) {
    Celula *celula = (Celula *) malloc(sizeof(Celula));
    celula->valor = valor;
    celula->prox = NULL;
    dados->movimentacoes++;
    dados->comparacoes++;
    if (*bucket == NULL || (*bucket)->valor >= valor) {
        celula->prox = *bucket;
        *bucket = celula;
        dados->movimentacoes += 2;
    } else {
        Celula *atual = *bucket;
        while (atual->prox && atual->prox->valor < valor) {
            atual = atual->prox;
            dados->movimentacoes++;
            dados->comparacoes++;
        }
        celula->prox = atual->prox;
        atual->prox = celula;
        dados->movimentacoes += 2;
    }
}


Parametros ResolveParametros(int argc, char **argv) {
    if (argc < 5) {
        FinalizaExecucao("Informe todos os parametros necessarios");
    }

    Parametros parametros;
    parametros.tamanho = atoi(argv[2]);
    parametros.tipo = atoi(argv[3]);
    parametros.arquivo_saida = argv[1];
    parametros.execucao = atoi(argv[4]);

    if (parametros.tamanho < 1 || parametros.tamanho > MAX_TAM)
        FinalizaExecucao("Tamanho invalido");

    if (parametros.tipo < CRE || parametros.tipo > ALE)
        FinalizaExecucao("Tipo invalido");

    return parametros;
}


void FinalizaExecucao(const char *mensagem) {
    if (mensagem) {
        printf("Erro: %s\n", mensagem);
    }
    exit(1);
}


int *AlocaVetor(int n) {
    int *v = (int *)malloc(n * sizeof(int));
    if (v == NULL) {
        FinalizaExecucao("Falha ao tentar alocar vetor");
    }
    return v;
}


int *AlocaVetorLimpo(int n) {
    int *v = (int *)calloc(n, sizeof(int));
    if (v == NULL) {
        FinalizaExecucao("Falha ao tentar alocar vetor");
    }
    return v;
}


int GeraNumeroAleatorioNoIntervalo(int a, int b) {
    if (a > b || a < MIN_EL || b > MAX_EL) {
        printf("\nGeraNumeroAleatorioNoIntervalo - Intervalo invalido: [%i, %i]\n", a, b);
        FinalizaExecucao(NULL);
    }
    return a + rand() % (b - a + 1);
}


int *CriaVetor(int n, VTipo tipo) {
    int *v = AlocaVetor(n);
    double t = floor(MAX_EL / (double) n);
    for (int i = 0; i < n; ++i) {
        if (tipo == CRE)        v[i] = GeraNumeroAleatorioNoIntervalo(i * t, (i + 1) * t - 1);
        if (tipo == DEC)        v[i] = GeraNumeroAleatorioNoIntervalo((n - i - 1) * t, (n - i) * t - 1);
        if (tipo == ALE)        v[i] = GeraNumeroAleatorioNoIntervalo(MIN_EL, MAX_EL);
    }
    return v;
}


void CopiaVetor(int n, int *origem, int *destino) {
    for (int i = 0; i < n; ++i)
        destino[i] = origem[i];
}


void Troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int Min(int a, int b) {
    return (a < b ? a : b);
}


int Max(int a, int b) {
    return (a > b ? a : b);
}


int MaxEl(int n, int *v) {
    int res = v[0];
    for (int i = 1; i < n; i++)
        res = Max(res, v[i]);
    return res;
}


int MaxEl_CD(int n, int *v, Dados *dados) {
    int res = v[0];
    for (int i = 1; i < n; i++) {
        dados->comparacoes++;
        if (res < v[i]) {
            res = v[i];
            dados->movimentacoes++;
        }
    }
    return res;
}


void ImprimeVetor(int n, int *v) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}


void VerificaOrdenacao(int n, int *v, AlgInfo *alg_info) {
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            printf("\nErro em: %s\n", alg_info->nome);
            FinalizaExecucao("O vetor nao esta ordenado\n");
        }
    }
}


Dados ObterDados(int n, int *v, AlgInfo *alg_info) {
    Dados dados = (Dados){ 0LL, 0LL, 0.0 };

    int *v_copia = AlocaVetor(n);
    CopiaVetor(n, v, v_copia);
    alg_info->impl_coletor(n, v_copia, &dados);
    VerificaOrdenacao(n, v_copia, alg_info);
    free(v_copia);

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    alg_info->impl(n, v);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    dados.tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;
    VerificaOrdenacao(n, v, alg_info);

    return dados;
}

void ImprimeHorarioAtual() {
    struct timeval tv;
    struct tm *tm_info;
    long milliseconds;
    gettimeofday(&tv, NULL);
    milliseconds = tv.tv_usec / 1000;
    tm_info = localtime(&tv.tv_sec);
    printf("Horario Atual: %02d:%02d:%02d:%03ld\n",
           tm_info->tm_hour,      // Horas
           tm_info->tm_min,       // Minutos
           tm_info->tm_sec,       // Segundos
           milliseconds           // Milissegundos
    );
}
