#include<stdio.h>


char bin(int* vet, int init, int end, int num){
    if(end<=init)
        return 'n';
    int mid =(end+init)/2;

    if(num==vet[mid]){
        return 's';
    }else if(num>vet[mid]){
        return bin(vet,mid+1,end, num);
    }else {
        return bin(vet,init,mid, num);
    }

}

char pesquisa_bin(int* vetor, int n, int num){

    char result = bin(vetor,0,n-1,num);
    if(result =='s'){

    }

}

int main(){
    int vetor[] = {1,2,3,4,5,7,8,9};
    int  r = pesquisa_bin(vetor,9,);
    printf("%d\n", r);


}
