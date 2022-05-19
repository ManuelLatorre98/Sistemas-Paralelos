#include <stdio.h>
#include <omp.h>
void main () {
   long num_steps = 800000000;
   double step;
   int i;
   double x, pi, sum = 0.0;
   double array[omp_get_max_threads()];
   step = 1.0/(double) num_steps;
   double itPerThread= num_steps/omp_get_max_threads();
//   printf("MAX: %d \n",omp_get_max_threads());
   #pragma omp parallel private(i, x)
   {
 //   printf("NUM: %d \n",omp_get_num_threads());
      int numThread=omp_get_thread_num();
      for (i = numThread* itPerThread ; i < (numThread* itPerThread + itPerThread); i++){
         x = (i + 0.5) * step;
         array[numThread]+= 4.0 / (1.0 + x * x);
      }
   }
   for (i = 0; i < omp_get_max_threads(); i++){
      sum+= array[i];
   }
   pi = step * sum;
   printf("%f\n",pi);
}
