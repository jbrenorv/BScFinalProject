#!/bin/bash

gcc src/*.c -O3 -lm

OUTPUT_DIR="output"
mkdir -p "$OUTPUT_DIR"
CURRENT_TIME=$(date "+%Y.%m.%d-%H.%M.%S")
OUTPUT_FILE="$OUTPUT_DIR/output_$CURRENT_TIME.csv"

echo "algoritmo,tamanho,tipo,execucao,comparacoes,movimentacoes,tempo" > "$OUTPUT_FILE"

tamanhos=()

intervalos=(
    "10000 100000 5000"
    "100000 1000000 50000"
    "1000000 10000000 500000"
    "10000000 100000001 5000000"
)

for intervalo in "${intervalos[@]}"; do
    read inicio fim passo <<< "$intervalo"
    for ((i=inicio; i<fim; i+=passo)); do
        tamanhos+=("$i")
    done
done

printf "Quantidade de tamanhos: ${#tamanhos[@]}\n"

for tamanho in "${tamanhos[@]}"; do
    for tipo in {0..2}; do
        for execucao in {1..3}; do

            printf "\rExecutando algoritmos... Tamanho: $tamanho - Tipo: $tipo/2 - Execucao: $execucao/3"

            ./a.out "$OUTPUT_FILE" "$tamanho" "$tipo" "$execucao"

            if [ $? -ne 0 ]; then 
                printf "\nO processo finalizou com um codigo diferente de 0\n"
                printf "Cancelando testes...\n"
                rm "$OUTPUT_FILE"
                rm a.out
                exit 1
            fi

        done
    done
done

printf "\nTudo pronto!\n"
printf "Resultado salvo em: $OUTPUT_FILE\n"
rm a.out
