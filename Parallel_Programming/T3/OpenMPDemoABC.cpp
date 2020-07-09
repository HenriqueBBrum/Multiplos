#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include<omp.h>


#define NUM_SCHEDS 4


class SharedArray {

private:

   char* array;
   int index;
   int size;
   bool usemutex;

public:

   SharedArray(int n, bool use) : size(n), index(0), usemutex(use) {
      array = new char[size];
      std::fill(array, array+size, '-');
   }

   ~SharedArray() {
      delete[] array;
   }

   void addChar(char c) {
      if (usemutex){
        #pragma omp critical (AddChar)
        {
          critical(c);
        }
      }else critical(c);
   }

   int countOccurrences(char c) {
      return std::count(array, array+size, c);
   }

   std::string toString() {
      return std::string(array, size);
   }

private:

  void spendSomeTime() {
     for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 100; j++) {
           // These loops shouldn't be removed by the compiler
        }
     }
  }

  void critical(char c){
    array[index] = c;
    spendSomeTime();
    index++;
  }

};


class ArrayFiller {

  private:

    static const int nThreads = 3;
    static const int nTimes = 20;
    static const int arrSize = nTimes*nThreads;
    SharedArray* array;
    int chunk;
    omp_sched_t schedule;
    bool runtime;



  public:

    ArrayFiller(bool usemutex, bool run, omp_sched_t sched, int ck) :
      schedule(sched), chunk(ck), runtime(run){

      array = new SharedArray(nThreads * nTimes, usemutex);
      if(!runtime)
        omp_set_schedule(schedule, ck);

    }

    void fillArrayConcurrently() {
      omp_set_dynamic(0);
      omp_set_num_threads(nThreads);

      #pragma omp parallel for schedule(runtime)
      for(int i = 0;i<arrSize; i++)
          array->addChar('A' + omp_get_thread_num());

   }

    void printStats(std::fstream& file) {
      file<< array->toString() << std::endl;
      for (int i = 0; i < nThreads; ++i)
         file << (char) ('A'+i) << "="
                   << array->countOccurrences('A'+i) << " ";
      file << std::endl;
    }

    ~ArrayFiller() {
      delete array;
    }

    std::string returnSchedStr(){
      switch(schedule){
        case omp_sched_static: return "STATIC";
        case omp_sched_dynamic: return "DYNAMIC";
        case omp_sched_guided: return "GUIDED";
        case omp_sched_auto: return "AUTO";
        default: return "RUNTIME";
      }
      return "RUNTIME";
    }
};


void test(std::fstream& file, bool runtime, omp_sched_t sched, int ck){
  ArrayFiller testA(true, runtime, sched, ck);
  testA.fillArrayConcurrently();
  file << "\nTest  A , SCHED = "<<testA.returnSchedStr()<<", chunk "<<ck<<" : using mutex (expecting correct results)" << std::endl;
  testA.printStats(file);

  ArrayFiller testB(false, runtime, sched, ck);
  testB.fillArrayConcurrently();
  file << "\nTest B , SCHED = "<<testB.returnSchedStr()<<", chunk "<<ck<<" : no mutex (expecting wrong results)" << std::endl;
  testB.printStats(file);
  file << " \n ------------------------------------------------------------------------------------------------ \n\n";

}


int main() {
  std::fstream file;
  file.open("results.txt", std::ios::out);
  int chunk = 15;

  test(file, true, static_cast<omp_sched_t>(0), 0);

  for(int i =0,  j= 0; i<NUM_SCHEDS;i+=(j%2), j++){
    int ck = (j%2)*chunk*((i==4)? 0 : 1);
    test(file, false, static_cast<omp_sched_t>(i+1), ck);
    j+= (i==(NUM_SCHEDS-1)? 1:0);
  }

  file.close();
}
