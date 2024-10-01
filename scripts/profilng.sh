gcc profiling/main.c src/ordenacao.c -O3 -lm -g

tamanhos=("1000000" "4000000" "7000000" "10000000")

for tamanho in "${tamanhos[@]}"; do
    valgrind --tool=cachegrind --cache-sim=yes --cachegrind-out-file="$tamanho" ./a.out "$tamanho"
done
