#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#define NTESTS 4
#define NTHREADS 5
#define NINDTESTS 5

typedef struct
 {
   double *a;
   double *b;
   double c;
   int wsize;
   int repeat;
 } dotdata_t;

dotdata_t dotdata;

void dotprod_worker()
{
   int i, k, offset = omp_get_thread_num();
   double *a = dotdata.a;
   double *b = dotdata.b;
   int wsize = dotdata.wsize;
   int start = offset*wsize;
   int end = start + wsize;
   double mysum;

  #pragma omp parallel for
   for (k = 0; k < dotdata.repeat; k++) {
      mysum = 0.0;
      for (i = start; i < end ; i++)  {
         mysum += (a[i] * b[i]);
      }
   }

   #pragma omp atomic update
   dotdata.c += mysum;

}

void dotprod_threads(int nthreads)
{
  omp_set_dynamic(0);
  omp_set_num_threads(nthreads);
  #pragma omp parallel
  {
    dotprod_worker();
  }

}

long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}


void fill(double *a, int size, double value)
{
   int i;
   for (i = 0; i < size; i++) {
      a[i] = value;
   }
}

long int createAndTestThread(int nthreads, long int wsize, int repeat){

  long start_time, end_time;
  dotdata.a = (double *) malloc(wsize*nthreads*sizeof(double));
  fill(dotdata.a, wsize*nthreads, 0.01);
  dotdata.b = (double *) malloc(wsize*nthreads*sizeof(double));
  fill(dotdata.b, wsize*nthreads, 1.0);
  dotdata.c = 0.0;
  dotdata.wsize = wsize;
  dotdata.repeat = repeat;

  // Calcula c = a . b em nthreads, medindo o tempo
  start_time = wtime();
  dotprod_threads(nthreads);
  end_time = wtime();

  // Mostra resultado e estatisticas da execucao
  printf("%f\n", dotdata.c);
  printf("%d thread(s), wsize = %ld, repeat = %d, %ld usec\n", nthreads, wsize, repeat, (long) (end_time - start_time));
  fflush(stdout);

  free(dotdata.a);
  free(dotdata.b);

  return (long) (end_time - start_time);
}


void tests(){
  int nthreads[NTHREADS] = {1,2,4,8,16};
  long int initialSizes[NTESTS] = {1000000, 10000000, 10000000, 100000000};
  int initalRept[NTESTS] = {2000,2000,1000,100};
  for(int i =0;  i<NTESTS;i++){
    for(int j = 0;j<NTHREADS;j++){
        int avg = 0;
        for(int k = 0; k < NINDTESTS; k++){
          avg+=createAndTestThread(nthreads[j], (long int)initialSizes[i]/nthreads[j], initalRept[i]);
        }
        avg = avg/NINDTESTS;
        printf("Final time result %d thread(s), wsize = %ld, repeat = %d, %ld usec\n", nthreads[j], (long int)initialSizes[i]/nthreads[j], initalRept[i], (long) avg);
        printf("\n###################################\n");
    }
    printf("\n----------------------------------\n");

  }

}

int main(){
  tests();
}
