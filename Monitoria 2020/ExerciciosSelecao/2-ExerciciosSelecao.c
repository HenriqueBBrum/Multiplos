#include<stdio.h>
#include<math.h>


void program1(){
  int a, b, c;
  printf("\nProg 1 - Digite 3 valores:\n");
  scanf("%d %d %d", &a, &b, &c);
  if(a<b && a<c) printf("A eh o menor\n");
  else if(b<c) printf("B eh o menor\n");
  else printf("C eh o menor\n");
}


void program2(){
  float a, b, c;
  printf("\nProg 2 - Digite 3 valores dos lados do triangulo:\n");
  scanf("%f %f %f", &a, &b, &c);
  if((a+b)>=c && (a+c)>=b && (b+c)>=c) printf("Eh um triangulo\n");
  else{ printf("Nao eh um triangulo\n"); return;}

  if(a == b && a == c) printf("Triangulo equilatero\n");
  else if(a!=b && b!=c && c!=a) printf("Triangulo escaleno\n");
  else if((a==b && a!=c) || (a==c && a!=b) || (b==c && b!=a)) printf("Triangulo isoceles\n");
}

void program3(){
  float indx;
  printf("\nProg 3 - Digite o indice de poluicao\n");
  scanf("%f", &indx);
  if(indx>=0.3 && indx<0.4) printf("Notificar industrias do grupo 1\n");
  else if(indx>=0.4 && indx<0.5) printf("Notificar industrias do grupo 1 e 2\n");
  else if(indx>=0.5) printf("Notificar industrias do grupo 1, 2 e 3\n");
  else printf("Notificar niguem\n");
}

void program4(){
  float s_medio, credito = 0;
  printf("\nProg 4 - Digite o saldo medio:\n");
  scanf("%f", &s_medio);
  if(s_medio>=201 && s_medio<=400) credito = 0.2;
  else if(s_medio>=401 && s_medio<=600) credito = 0.3;
  else if(s_medio>=601) credito = 0.4;

  printf("Saldo medio = %.2f. credito = %.2f\n", s_medio, credito);
}

void program5(){
  unsigned int id, amt, achou = 0;
  float total = 0;
  float id_value[6][2] = {{1001, 5.32}, {1324, 6.45}, {6548, 2.37}, {987, 5.32}, {7623, 6.45}};
  printf("\nProg 5 - Digite o codigo do produto e a quantidade\n");
  scanf("%u %u", &id, &amt);
  for(int i = 0;i<6;i++){
    if((float)id == id_value[i][0]){
       total = id_value[i][1]*(float)amt;
       achou = 1;
       break;
     }
  }

  if(achou == 0) printf("Nao existe esse codigo\n");
  else
    printf("Total = %.2f\n", total);

}

void program6(){
  unsigned int mes = 0;
  printf("\nProg 6 - Digite um mes:\n");
  scanf("%u", &mes);
  if(mes>12 || mes<=0) {printf("Esse mes n existe\n"); return;}

  char meses[12][20] ={"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
  printf("Mes escolhido %u(%s)\n", mes, meses[mes-1]);
}

int main(){
  //program1();
  //program2();
  //program3();
  //program4();
  //program5();
//  program6();


}
