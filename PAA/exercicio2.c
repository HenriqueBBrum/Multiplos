///a)(0,4);(1,4);(2,4);(3,4);(2,3);
///b) vet = [N, N-1,...,1] pois para qualquer i todos os j serão inversão se i<j



#include<stdio.h>

int contaInversoes(int* vet, int esq, int dir, int i)
{
    int inversoes = 0;
    if (esq < dir)
    {

        int m = (esq+dir)/2;



        if(vet[m]<vet[i] && m>i){
            printf("Achou inversao de vet[%d] com vet[%d]\n", i, m);
            inversoes++;
        }

        //busca a soma nas duas partes pois
        //o vetor pode nao estar ordenado
        inversoes+=contaInversoes(vet, esq, m, i);
        inversoes+=contaInversoes(vet, m+1, dir, i);


    }

    return inversoes;
}


void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main()
{
    int vet[] = {1,20,6,4,5};
    int n = sizeof(vet)/sizeof(vet[0]);

    printf("O vetor eh\n");
    printArray(vet, n);


    int i = 0;
    int qntInversoes = 0;
    while(i<n){
        qntInversoes +=contaInversoes(vet, 0, n, i);
        i++;
    }

    printf("Qnt inversoes  =  %d\n", qntInversoes);


    return 0;
}

