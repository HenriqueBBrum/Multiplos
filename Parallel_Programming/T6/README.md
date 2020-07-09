[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2020a) > Trabalhos

# T6: Primeiros passos com MPI

Este trabalho/exercício acompanha a introdução a MPI (Message Passing Interface) disponível [nestes slides](https://docs.google.com/presentation/d/1ItSn3EyWDocwVI7_gdz0RwDKPy274nsSRobtcrdV2V0/edit?usp=sharing). Para desenvolvê-lo, você vai precisar instalar OpenMPI, que é uma implementação do padrão MPI. As principais distribuições Linux possuem pacotes para isso (por exemplo, no Ubuntu, instale os pacotes openmpi-bin e libopenmpi-dev).


## Aquecimento

Para começar, exercite compilação e execução de programas MPI:

- Baixe o arquivo [hello_mpi.c](hello_mpi.c).

- Compile o programa:
  ```
  mpicc -o hello_mpi hello_mpi.c
  ```

- Execute o programa com 5 processos e observe a saída:
  ```
  mpiexec -np 5 hello_mpi
  ```


## Parte 1

Implemente um programa MPI que transporte uma mensagem em um pipeline formado por processos de 0 a NP-1 (processo 0 envia para 1, processo 1 envia para 2, ..., processo NP-1 mostra o resultado). A mensagem pode ser um número inteiro que é incrementado antes de ser passado adiante.


## Parte 2


+ O programa [mpi_errado1.c](mpi_errado1.c) deveria realizar a troca de mensagens entre 2 processos, mas ele não funciona como esperado. Identifique o erro e corrija-o.

+ O programa [mpi_errado2.c](mpi_errado2.c) deveria realizar a troca de mensagens entre 2 processos, mas também não funciona como esperado. Identifique o erro e corrija-o.



## Entrega


No repositório de entrega do trabalho, crie um documento `Entrega.md`, contendo:
 - Identificação completa da disciplina e do aluno;
 - Parte 1: Link para o programa produzido e comentários sobre possíveis dificuldades/facilidades;
 - Parte 2: Explicação sobre cada erro e programas corrigidos.



## Material de apoio


- [Tutorial MPI](https://computing.llnl.gov/tutorials/mpi/)  
  Tutorial do Lawrence Livermore National Laboratory (LLNL) sobre MPI.
