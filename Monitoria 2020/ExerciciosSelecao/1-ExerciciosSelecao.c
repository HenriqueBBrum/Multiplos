#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void program1(){
  int a = 0, b = 0;
  printf("Prog 1 - Digite dois numeros:\n");
  scanf("%d %d", &a, &b);
  printf("Diferenca do maior pro menor %d\n", abs(a-b));
}

void program2(){
  int a = 0;
  printf("\nProg 2 -  Digite um numero:\n");
  scanf("%d", &a);
  printf("Numero eh par? %s. Eh negativo? %s.\n", a%2 == 0? "Sim" : "Nao", a<0?"Sim":"Nao");
}

void program3(){
  int a = 0, b = 0;
  printf("\nProg 3 - Digite dois numeros:\n");
  scanf("%d %d", &a, &b);
  if(a==b) printf("Numeros iguais\n");
  else printf("%d eh o maior\n", a>b?a:b);
}

void program4(){
  int a = 0, b = 0, c = 0;
  printf("\nProg 4 - Digite tres numeros:\n");
  scanf("%d %d %d", &a, &b, &c);
  if(a > 0) printf("a -> Sqrt = %f\n", sqrt(a));
  else printf("a - Pow2 = %f\n", pow(a, 2));

  if(b > 10 && b<100) printf("b -> Numero esta entre 10 e 100 -  Intervalo permitido\n");

  if(c < b) printf("c -> Diferenca entre c e b = %d\n", abs(c-b));
  else printf("c -> C + 1 = %d\n", c+1);
}

void program5(){
  float alt = 0;
  char sexo;
  printf("\nProg 5 - Digitea a altura(m) e o sexo (M ou F) da pessoa:\n");
  scanf("%f %c", &alt, &sexo);
  if(sexo == 'M' || sexo == 'm') printf("Peso ideal homems = %f\n", 72.7*alt - 58);
  else if(sexo == 'F' || sexo == 'f') printf("Peso ideal mulheres = %f\n", 62.1*alt - 44.7);
  else printf("Caracter errado\n");
}

void program6(){
  unsigned int age = 0;
  printf("\nProg 6 -  Digite a idade do nadador:\n");
  scanf("%u", &age);
  if(age>=5 && age<=7) printf("Infantil A\n");
  else if(age>=8 && age<=10) printf("Infantil B\n");
  else if(age>=11 && age <=13) printf("Juvenil A\n");
  else if(age>=14 && age<=18) printf("Juvenil B\n");
  else printf("Senior\n");

}

void program7(){
  float nota1, nota2;
  unsigned int aulas_t, aulas_a;
  printf("Prog 7 - Digite duas notas, o numero de aulas totais e assistidas:\n");
  scanf("%f %f %d %d", &nota1, &nota2, &aulas_t, &aulas_a);
  float md = (nota1+nota2)/2;
  float freq = (aulas_a/(float)aulas_t)*100;

  printf("Nota final = %.2f, Frequencia = %.2f\n", md, freq);
  if(md<6.0) printf("Reprovado por nota\n");
  else if(freq<75) printf("Reprovado por frequencia\n");
  else printf("Aprovado\n");


}

int main(){
  /*program1();
  program2();
  program3();
  program4();
  program5();
  program6();*/
  program7();


}
