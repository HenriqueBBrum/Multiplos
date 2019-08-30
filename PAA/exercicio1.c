#include<stdio.h>


void buscaSoma(int* vet, int esq, int dir, int value, int i)
{
    if (esq < dir)
    {

        int m = (esq+dir)/2;

        if(m==i)
            return;

        if(vet[m]+vet[i]==value){
            printf("A soma buscada eh vet[%d] = %d + vet[%d] = %d => %d\n",m, vet[m], i, vet[i],value);
            return;
        }
        //busca a soma nas duas partes pois
        //o vetor pode nao estar ordenado
        buscaSoma(vet, esq, m, value, i);
        buscaSoma(vet, m+1, dir, value, i);

    }
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
    int vet[] = {12, 11, 13, 5, 6, 7, 14, 53, 11};
    int n = sizeof(vet)/sizeof(vet[0]);
    int value;

    printf("O vetor eh\n");
    printArray(vet, n);

    printf("Digite o valor resultante das somas : \n");
    scanf("%d", &value);
    int i = 0;
    while(i<n){
        buscaSoma(vet, 0, n - 1, value, i);
        i++;
    }


    return 0;
}
