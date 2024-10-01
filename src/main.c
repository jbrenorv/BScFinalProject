#include "ordenacao.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char **argv) {
    srand(time(NULL));

    Parametros parametros = ResolveParametros(argc, argv);
    int *vetor_original = CriaVetor(parametros.tamanho, parametros.tipo);
    int *vetor = AlocaVetor(parametros.tamanho);

    AlgInfo algoritmos[] =
    {
        // Nome         , N max    , Alg.        , Alg. coletor
        { "Bolha"       , 100000   , Bolha       , Bolha_CD       , INF },
        { "Coquetel"    , 100000   , Coquetel    , Coquetel_CD    , INF },
        { "Selecao"     , 100000   , Selecao     , Selecao_CD     , INF },
        { "Insercao"    , 100000   , Insercao    , Insercao_CD    , INF },
        { "Shellsort"   , 100000000, Shellsort   , Shellsort_CD   , SUP },
        { "Mergesort"   , 100000000, Mergesort   , Mergesort_CD   , SUP },
        { "Heapsort"    , 100000000, Heapsort    , Heapsort_CD    , SUP },
        { "Quicksort"   , 100000000, Quicksort   , Quicksort_CD   , SUP },
        { "QuicksortI"  , 100000000, QuicksortI  , QuicksortI_CD  , SUP },
        { "Introsort"   , 100000000, Introsort   , Introsort_CD   , SUP },
        { "Countingsort", 10000000 , Countingsort, Countingsort_CD, LIN },
        { "Bucketsort"  , 10000000 , Bucketsort  , Bucketsort_CD  , LIN },
        { "RadixsortC"  , 10000000 , RadixsortC  , RadixsortC_CD  , LIN },
        { "RadixsortB"  , 10000000 , RadixsortB  , RadixsortB_CD  , LIN },
    };
    int num_algoritmos = sizeof(algoritmos) / sizeof(AlgInfo);

    FILE *arquivo_saida;
    if ((arquivo_saida = fopen(parametros.arquivo_saida, "a")) == NULL) {
        free(vetor_original);
        free(vetor);
        FinalizaExecucao("Falha ao tentar abrir arquivo de saida.");
    }

    for (int i = 0; i < num_algoritmos; i++) {
        if (parametros.tamanho > algoritmos[i].tamanho_maximo) continue;

        CopiaVetor(parametros.tamanho, vetor_original, vetor);

        Dados dados = ObterDados(parametros.tamanho, vetor, &algoritmos[i]);

        fprintf(arquivo_saida, "%s,%i,%i,%i,%lli,%lli,%lf\n",
            algoritmos[i].nome,
            parametros.tamanho,
            parametros.tipo,
            parametros.execucao,
            dados.comparacoes,
            dados.movimentacoes,
            dados.tempo
        );
    }

    free(vetor_original);
    free(vetor);
    fclose(arquivo_saida);

    return 0;
}
