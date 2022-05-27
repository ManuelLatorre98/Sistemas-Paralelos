#include <stdio.h>
#include <omp.h>
#define N 50
void vector_add(int *A, int *B, int *C, int n) {
   int i;
   for (i = 0; i < n; i++)
      C[i] = A[i] + B[i];
}

void rec_vector_add(int *A, int *B, int *C, int n) {
// si es el caso base, llamar a vector_add
   int base=10, primerMitad= n/2, segundaMitad= primerMitad;
   if (n<=10){
      vector_add(A,B,C,n);
   }else{
      #pragma omp task
      {//Cada llamada equivale a una tarea que realiza un thread
         printf("menor --> id: %d \n",omp_get_thread_num());
         rec_vector_add(A,B,C,primerMitad);
      }
      if(n%2 !=0){//Si numero impar, la segunda mitad es la mayor
         segundaMitad++;
      }
      #pragma omp task
      {
         printf("mayor --> id: %d \n",omp_get_thread_num());
         rec_vector_add(A+primerMitad, B+primerMitad, C+primerMitad, segundaMitad);//los vectores apuntan despues de la mitad trabajada en primer llamado
      }
   }
// sino, hacer la suma recursiva sobre la primera mitad de los arreglos, y luego la suma recursiva sobre la segunda mitad de los arreglos.
}

int main() {
   int a[N],b[N],c[N],i;
   //Inicializo a y b
   for (i = 0; i < N; i++)
   {
      a[i]=i;
      b[i]=2;
   }
   #pragma omp parallel
   { 
      #pragma omp single //Se va a ejecutar por un unico hilo
      rec_vector_add(a, b, c, N);
   }
   
   for (i = 0; i < N; i++)
   {
      printf("c[%d]= %d\n", i, c[i]);
   }
   
}
