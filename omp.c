#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>

int main( int argc, char *argv[]) {
   int rank; 
   char hostname[128];
   gethostname(hostname, sizeof(hostname));

   char* s = getenv("OMP_NUM_THREADS");
   printf("OMP_NUM_THREADS: %s\n",(s!=NULL)? s : "sin definir");

   #pragma omp parallel
   {
      printf("El thread %d ejecuta en el core %d del nodo %s\n", omp_get_thread_num(), sched_getcpu(), hostname);
   }
   return 0;
}
