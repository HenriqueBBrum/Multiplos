#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

/** Não tive nenhuma dificuldades
    Achei bem fácil e simples a maneira de usar o MPI para mandar mensgaens entre processo */

int main(int argc, char* argv[]) {
  int myrank;         // "rank" do processo (0 a P-1)
  int p;              // número de processos
  int source;         // "rank" do processo remetente
  int dest;           // "rank" do processo destinatário
  int tag = 0;        // "etiqueta" da mensagem
  char msg[100];      // a mensagem
  MPI_Status status;  // "status" de uma operação efetuada

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  if (myrank == 0) {
    sprintf(msg, "Processo %d mandou para o processo %d o seguinte valor: %d", myrank, myrank+1, 10);
    // envia mensagem ao processo 1
    dest =  myrank+1;
    MPI_Send(msg, strlen(msg)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);

  }else if(myrank> 0  && myrank<p-1){
    MPI_Recv(msg, 100, MPI_CHAR, myrank-1, tag, MPI_COMM_WORLD, &status);
    printf("%s\n", msg); // mostra mensagem

    char aux_msg[100];
    sprintf(aux_msg, "Processo %d mandou para o processo %d o seguinte valor: ", myrank-1, myrank);

    size_t int_str_size = strlen(msg) - strlen(aux_msg);

    char* int_str = malloc(int_str_size+1);
    strncpy(int_str, msg+strlen(aux_msg),  int_str_size);
    int_str[int_str_size] = '\n';
    // Aumenta o valor recebido
    int val = atoi(int_str);
    val++;

    free(int_str);

    sprintf(msg, "Processo %d mandou para o processo %d o seguinte valor: %d", myrank, myrank+1, val);
    // envia mensagem ao processo myrank+1
    dest =  myrank+1;
    MPI_Send(msg, strlen(msg)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);

  }else{
    MPI_Recv(msg, 100, MPI_CHAR, myrank-1, tag, MPI_COMM_WORLD, &status);
    printf("%s\n", msg); // mostra mensagem

  }


  MPI_Finalize(); // finaliza MPI
  return 0;
}
