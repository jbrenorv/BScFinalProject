## Execução dos testes gerais
```bash
./scripts/testes.sh
```

## Profiling (Mergesort e Quicksort)
```bash
cd profiling
sudo apt update
sudo apt install valgrind kcachegrind
gcc main.c -O3 -lm -g
valgrind --tool=cachegrind --cache-sim=yes ./a.out
kcachegrind cachegrind.out.<algum sufix numerico>
```
