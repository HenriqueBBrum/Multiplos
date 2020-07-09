#!/bin/bash
#SBATCH -J T5               # nome da tarefa
#SBATCH -o t5-%j.out        # nome do arquivo de saída (%j se torna jobID), este arquivo pega a saída padrão do terminal
#SBATCH -e t5-%j.err        # nome do arquivo de erros (%j se torna jobID), este arquivo pega erros gerados pelo script no terminal
#SBATCH -c 16               # número máximo de threads necessárias
#SBATCH -p qCDER            # partição --qCDER (partições disponíveis ao executar `sinfo`)
#SBATCH -t 01:30:00         # tempo máximo necessário (hh:mm:ss) - 1h30min


## Incluir módulos necessários para a execução.
## Dependendo dos recursos do OpenMP a serem utilizados,
## pode ser necessário carregar um gcc mais novo,
## para que a versão do OpenMP também seja mais recente.

module load Compilers/gcc-8.3.0


## Compilar aplicação (pode ser compilada antes,
## mas caso algum módulo seja carregado no script,
## será necessário compilar novamente)

make clean
make


## Setando algumas variáveis
SIZE=150
TRIALS=100
PROBS=100
NTHREADS=(1 2 4 6)
NEXECS=3


## Executando a aplicação para diferentes números de threads (10 vezes para cada caso)
## Podem ser criados laços para variar outros parâmetros

for i in ${NTHREADS[@]}; do
    export OMP_NUM_THREADS=$i
    #echo $OMP_NUM_THREADS
    for j in $(seq 1 $NEXECS); do
        ./virusim $SIZE $TRIALS $PROBS #> logs/log-nt$i-$j
    done
done

