# Programação Paralela

#### Henrique Becker Brum


## Pthreads:

### 1.
    a)Particionamento: Acontece quando cada thread recebe um offest para tratar de uma parte individual do vetor.

      Em void dotprod_threads(int nthreads):

      ```
      for (i = 0; i < nthreads; i++) {
         pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
      }

      ```
      Em void* dotprod_worker(void* arg):

      ```
      int start = offset*wsize;
      int end = start + wsize;

      for (k = 0; k < dotdata.repeat; k++) {
        mysum = 0.0;
        for (i = start; i < end ; i++)  {
           mysum += (a[i] * b[i]);
        }
     }
      ```

    b)Comunicação: Ocorre quando todos as threads precisam fazer o calculo da multiplicação entre
    cada posição e a soma dessas multiplicações.

      Em void* dotprod_worker(void* arg):

      ```

      for (k = 0; k < dotdata.repeat; k++) {
         mysum = 0.0;
         for (i = start; i < end ; i++)  {
           //A comunicação é o '(a[i] * b[i])'
            mysum += (a[i] * b[i]);
         }
      }


      pthread_mutex_lock (&mutexsum);
      //A comunicação ocorre quando dotdata.c recebe dados de todas as threads
      dotdata.c += mysum;
      pthread_mutex_unlock (&mutexsum);

      ```
    c)Aglomeração: Ocorre quando é feito multiplas subsomas tanto no processo de multiplicação quanto
      no processo do somatório final.

      Em void* dotprod_worker(void* arg):

      ```

      for (k = 0; k < dotdata.repeat; k++) {
         mysum = 0.0;
         for (i = start; i < end ; i++)  {
           // A aglomeração é o 'mysum +='
            mysum += (a[i] * b[i]);
         }
      }

      pthread_mutex_lock (&mutexsum);
      //A comunicação é o 'dotdata.c +='
      dotdata.c += mysum;
      pthread_mutex_unlock (&mutexsum);

      ```

      d)Mapeamento: Acontece quando há divisão ou controle das threads.

        Em void dotprod_threads(int nthreads):

        ```

        for (i = 0; i < nthreads; i++) {
          pthread_join(threads[i], NULL);
        }

        ```


### 2.
    Speedup = 5227699/3832217 = 1,364144828

### 3.
  Sim, esse Speedup se mantém para diferentes tamanho de vetores e de repetições. No caso do aumento de threads
  para o mesmo número de iterações o Speedup começa a se estabilizar após 4 threads e em alguns casos piora.

### 4.

  | Tamanho Vetor    | Número de Repetições | Quantidade de Threads | Tempo (usec)(x-barra (5)) |
  |------------------|:--------------------:|-----------------------|---------------------------|
  | 10^6             | 2000                 | 1                     | 5227699                   |
  | 10^6 / 2         | 2000                 | 2                     | 3832217                   |
  | 10^6 / 4         | 2000                 | 4                     | 2349076                   |
  | 10^6 / 8         | 2000                 | 8                     | 2409288                   |
  | 10^6 / 16        | 2000                 | 16                    | 2069955                   |


  | Qnt Threads Inicial   | Qnt Threads Final  |    Speedup     |
  |-----------------------|:------------------:|----------------|
  | 1                     | 2                  | 1,364144828   |
  | 1                     | 8                  | 2,169810749    |
  | 2                     | 4                  | 1,63137208     |
  | 4                     | 8                  | 0,975008384    |
  | 4                     | 16                 | 1,134843994    |



  | Tamanho Vetor    | Número de Repetições | Quantidade de Threads | Tempo (usec)(x-barra (5))  |
  |------------------|:--------------------:|-----------------------|----------------------------|
  | 10^7             | 2000                 | 1                     | 56739979                   |
  | 10^7 / 2         | 2000                 | 2                     | 34666435                   |
  | 10^7 / 4         | 2000                 | 4                     | 27571100                   |
  | 10^7 / 8         | 2000                 | 8                     | 26091783                   |
  | 10^7 / 16        | 2000                 | 16                    | 25974455                   |

  | Qnt Threads Inicial   | Qnt Threads Final  |    Speedup     |
  |-----------------------|:------------------:|----------------|
  | 1                     | 2                  | 1,636741101    |
  | 1                     | 8                  | 2,174630189    |
  | 2                     | 4                  | 1,257346823    |
  | 4                     | 8                  | 1,056696662    |
  | 4                     | 16                 | 1,061469817    |



  | Tamanho Vetor    | Número de Repetições | Quantidade de Threads | Tempo (usec)(x-barra (5))  |
  |------------------|:--------------------:|-----------------------|----------------------------|
  | 10^7             | 1000                 | 1                     | 29538580                   |
  | 10^7 / 2         | 1000                 | 2                     | 17878511                   |
  | 10^7 / 4         | 1000                 | 4                     | 12010590                   |
  | 10^7 / 8         | 1000                 | 8                     | 11729442                   |
  | 10^7 / 16        | 1000                 | 16                    | 12091746                   |

  | Qnt Threads Inicial   | Qnt Threads Final  |    Speedup     |
  |-----------------------|:------------------:|----------------|
  | 1                     | 2                  | 1,652183451    |
  | 1                     | 8                  | 2,518327811    |
  | 2                     | 4                  | 1,48856226     |
  | 4                     | 8                  | 1,023969427    |
  | 4                     | 16                 | 0,993288314    |



  | Tamanho Vetor    | Número de Repetições | Quantidade de Threads | Tempo (usec)(x-barra (5))  |
  |------------------|:--------------------:|-----------------------|----------------------------|
  | 10^8             | 100                  | 1                     | 29780235                   |
  | 10^8 / 2         | 100                  | 2                     | 17366558                   |
  | 10^8 / 4         | 100                  | 4                     | 12930538                   |
  | 10^8 / 8         | 100                  | 8                     | 12129372                   |
  | 10^8 / 16        | 100                  | 16                    | 11955772                   |


  | Qnt Threads Inicial   | Qnt Threads Final  |    Speedup     |
  |-----------------------|:------------------:|----------------|
  | 1                     | 2                  | 1,714803532    |
  | 1                     | 8                  | 2,45392258     |
  | 2                     | 4                  | 1,343065385    |
  | 4                     | 8                  | 1,06605173     |
  | 4                     | 16                 | 1,081530996    |





### 5.
      O código pthreads_dotprod.c possui exclusão mutua na hora de acessar o dotdata.c, já o pthreads_dotprod2.code
    não.
      Nesse caso o resultado fica igual pois não importa a ordem de acesso à esse dado e nem o valor do mesmo.
    Pois se uma thread fossse incrementar dotdata.c e logo antes de fazer ADD X, Y, Z outra thread interrompesse
    e se somasse à dotdata.c o valor final de dotdata.c ficaria igual.




## OpenMP:

### 2.

  | Tamanho Vetor    | Número de Repetições | Quantidade de Threads | Tempo (usec)(x-barra (5)) |
  |------------------|:--------------------:|-----------------------|---------------------------|
  | 10^6             | 2000                 | 1                     | 6073905                   |
  | 10^6 / 2         | 2000                 | 2                     | 3767774                   |
  | 10^6 / 4         | 2000                 | 4                     | 2551462                   |
  | 10^6 / 8         | 2000                 | 8                     | 2475182                   |
  | 10^6 / 16        | 2000                 | 16                    | 2405596                   |


  | Qnt Threads Inicial   | Qnt Threads Final  |    Speedup     |
  |-----------------------|:------------------:|----------------|
  | 1                     | 2                  | 1,612067231    |
  | 1                     | 8                  | 2,45392258     |
  | 2                     | 4                  | 1,476711783    |
  | 4                     | 8                  | 1,030817936    |
  | 4                     | 16                 | 1,060636117    |



  | Tamanho Vetor    | Número de Repetições | Quantidade de Threads | Tempo (usec)(x-barra (5))  |
  |------------------|:--------------------:|-----------------------|----------------------------|
  | 10^7             | 2000                 | 1                     | 63050796                   |
  | 10^7 / 2         | 2000                 | 2                     | 37454408                   |
  | 10^7 / 4         | 2000                 | 4                     | 26147603                   |
  | 10^7 / 8         | 2000                 | 8                     | 25001558                   |
  | 10^7 / 16        | 2000                 | 16                    | 25519188                   |

  | Qnt Threads Inicial   | Qnt Threads Final  |    Speedup     |
  |-----------------------|:------------------:|----------------|
  | 1                     | 2                  | 1,683401217    |
  | 1                     | 8                  | 2,521874677    |
  | 2                     | 4                  | 1,432422238    |
  | 4                     | 8                  | 1,045838943    |
  | 4                     | 16                 | 1,024625196    |



  | Tamanho Vetor    | Número de Repetições | Quantidade de Threads | Tempo (usec)(x-barra (5))  |
  |------------------|:--------------------:|-----------------------|----------------------------|
  | 10^7             | 1000                 | 1                     | 31049526                   |
  | 10^7 / 2         | 1000                 | 2                     | 18579812                   |
  | 10^7 / 4         | 1000                 | 4                     | 12868222                   |
  | 10^7 / 8         | 1000                 | 8                     | 12697615                   |
  | 10^7 / 16        | 1000                 | 16                    | 12778299                   |

  | Qnt Threads Inicial   | Qnt Threads Final  |    Speedup     |
  |-----------------------|:------------------:|----------------|
  | 1                     | 2                  | 1,671143174    |
  | 1                     | 8                  | 2,445303783    |
  | 2                     | 4                  | 1,443852305    |
  | 4                     | 8                  | 1,013436145    |
  | 4                     | 16                 | 1,007037165    |



  | Tamanho Vetor    | Número de Repetições | Quantidade de Threads | Tempo (usec)(x-barra (5))  |
  |------------------|:--------------------:|-----------------------|----------------------------|
  | 10^8             | 100                  | 1                     | 32040686                   |
  | 10^8 / 2         | 100                  | 2                     | 20032086                   |
  | 10^8 / 4         | 100                  | 4                     | 12693318                   |
  | 10^8 / 8         | 100                  | 8                     | 12659686                   |
  | 10^8 / 16        | 100                  | 16                    | 12599757                   |


  | Qnt Threads Inicial   | Qnt Threads Final  |    Speedup     |
  |-----------------------|:------------------:|----------------|
  | 1                     | 2                  | 1,599468273    |
  | 1                     | 8                  | 2,530922647    |
  | 2                     | 4                  | 1,578159942    |
  | 4                     | 8                  | 1,002656622    |
  | 4                     | 16                 | 1,007425619    |





## Referências:

Microsoft. Microsoft OpenMP.  https://docs.microsoft.com/pt-br/cpp/parallel/openmp/openmp-in-visual-cpp?view=vs-2019

Joel Yliluoma. Guide into OpenMP. https://bisqwit.iki.fi/story/howto/openmp/#ExampleInitializingATableInParallelMultipleThreads
