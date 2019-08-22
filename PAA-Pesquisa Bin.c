#include<stdio.h>


int bin(int* vet, int init, int end, int num){
    if(end<=init)
        return -1;
    int mid =(end+init)/2;

    if(num==vet[mid]){
        return mid;
    }else if(num>vet[mid]){
        return bin(vet,mid+1,end, num);
    }else {
        return bin(vet,init,mid, num);
    }

}

int pesquisa_bin(int* vetor, int n, int num){

    int result = bin(vetor,0,n-1,num);
    return result;

}

int main(){
    int vetor[] = {1,2,3,4,5,7,8,9};
    int num = 7;
    int n = 9;
    int  r = pesquisa_bin(vetor,n,num);
    printf("posicao do num %d = %d\n",num, r);


}
