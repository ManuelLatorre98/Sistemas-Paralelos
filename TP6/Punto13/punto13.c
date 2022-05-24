#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
void tarea_uno() {
   sleep(2);
}
void tarea_dos() {
   sleep(3);
}
void tarea_tres() {
   sleep(2);
}
int main () {
   double tiempoIni, tiempoFin;
   tiempoIni = omp_get_wtime();
   #pragma omp parallel
   {
      #pragma omp sections nowait
      {
         #pragma omp section
         {
            printf("Ejecutando tarea 1, por thread %d \n", omp_get_thread_num());
            tarea_uno();
         }
         
         #pragma omp section
         {
            printf("Ejecutando tarea 2 por thread %d \n", omp_get_thread_num());
            tarea_dos();
         }
         #pragma omp section
         {
            printf("Ejecutando tarea 3 por thread %d \n", omp_get_thread_num());
            tarea_tres();
         }
      }
      tiempoFin = omp_get_wtime();
      printf("Tiempo: %f segundos de thread %d\n", tiempoFin - tiempoIni, omp_get_thread_num());
   }
   return 0;
}
