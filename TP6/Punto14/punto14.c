#include <omp.h>
#include <stdio.h>
int main()
{
   #pragma omp parallel num_threads (2)
   {
      int x;
      int id = omp_get_thread_num();
      for (x = 0; x < 10; x++) {
         #pragma omp task
            printf("hola %d\n", id);
      }
      #pragma omp taskwait
      printf("chau %d\n", id);
   }
}
