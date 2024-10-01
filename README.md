## Execução dos testes
O script `scripts/testes.sh` pode ser usado para executar os algoritmos para vários tamanhos e tipos de vetor de forma automatizada, edite esse arquivo de acordo com seu interesse e em seguida execute:
```bash
./scripts/testes.sh
```

## Profiling

### Dependências
Use os comandos a seguir para instalar as dependências `valgrind` e `kcachegrind`:
```bash
sudo apt update
sudo apt install valgrind kcachegrind
```

### Gerar uma saída única para um tamanho específico
Após instalar as dependências, use os comandos a seguir para compilar `profiling/main.c` e usar o `valgrind` com a ferramenta `cachegrind` para gerar um arquivo que poderá ser visualizado no programa `kcachegrind`:
```bash
gcc profiling/main.c src/ordenacao.c -O3 -lm -g
valgrind --tool=cachegrind --cache-sim=yes --cachegrind-out-file=<arquivo-saida> ./a.out <tamanho-vetor>
kcachegrind <arquivo-saida>
```

### Gerar saídas para vários tamanhos
Edite os arquivos `profiling/main.c` e `scripts/profiling.sh` de acordo com a necessidade e em seguida execute:
```bash
./scripts/profiling.sh
```
