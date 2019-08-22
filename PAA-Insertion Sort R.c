#include<stdio.h>


void insertion_sort_recursive(int* vet, int n){
    if(n<=1){
        printf("ok\n");
        return;
    }


    insertion_sort_recursive(vet, n-1);

    int last = vet[n-1];
    int j = n -2;

    while(j>=0 && vet[j]>last){
        vet[j+1] = vet[j];
        j--;
    }
    vet[j+1] = last;

}



int main(){
    int vet[] = {2,5,1,7,2,9,21,6};
    int  n = 8;
    insertion_sort_recursive(vet,n);
    for(int i =0;i<n;i++){
        printf("%d ", vet[i]);
    }
}
