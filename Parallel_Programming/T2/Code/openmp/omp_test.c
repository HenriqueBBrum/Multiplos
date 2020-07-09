/*****************************************************************************
* FILE: omp_dotprod_openmp.c
* DESCRIPTION:
*   This simple program is the OpenMP version of a dot product and the
*   second of four codes used to show the progression from a serial program to a
*   hybrid MPI/OpenMP program.  The relevant codes are:
*      - omp_dotprod_serial.c  - Serial version
*      - omp_dotprod_openmp.c  - OpenMP only version
*      - omp_dotprod_mpi.c     - MPI only version
*      - omp_dotprod_hybrid.c  - Hybrid MPI and OpenMP version
* SOURCE: Blaise Barney
* LAST REVISED:  06/02/17 Blaise Barney
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

/* Define length of dot product vectors and number of OpenMP threads */
#define VECLEN 100
#define NUMTHREADS 1

int main (int argc, char* argv[])
  {
  int i, tid, len=VECLEN, threads=NUMTHREADS;
  double *a, *b;
  double sum, psum;

  printf("Starting omp_dotprod_openmp. Using %d threads\n",threads);

  /* Assign storage for dot product vectors */
  a = (double*) malloc (len*threads*sizeof(double));
  b = (double*) malloc (len*threads*sizeof(double));

  /* Initialize dot product vectors */
  for (i=0; i<len*threads; i++) {
    a[i]=1.0;
    b[i]=a[i];
  }
  /* Initialize global sum */
  sum = 0.0;

  /*
     Perform the dot product in an OpenMP parallel region for loop with a sum reduction
     For illustration purposes:
       - Explicitly sets number of threads
       - Each thread keeps track of its partial sum
  */
  long start_time, end_time;

  start_time = wtime();
  #pragma omp parallel private(i,tid,psum) num_threads(threads)
  {
  psum = 0.0;
  tid = omp_get_thread_num();

  #pragma omp for reduction(+:sum)
    for (i=0; i<len*threads; i++)
      {
        sum += (a[i] * b[i]);
        psum = sum;
      }
      printf("Thread %d partial sum = %f\n",tid, psum);
  }
  end_time = wtime();

  printf ("Done. OpenMP version: time  =  %ld \n",(long) (end_time - start_time));

  free (a);
  free (b);
}
