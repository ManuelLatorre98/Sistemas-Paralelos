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
   int base=10, primerMitad=n/2, segundaMitad=primerMitad;
   if(n<=base){
      vector_add(A, B, C, n);
   }else{
      rec_vector_add(A,B,C, primerMitad);
      if(n % 2 != 0){
         segundaMitad++;
      }
      rec_vector_add(A+primerMitad,B+primerMitad,C+primerMitad,segundaMitad);
   }
// sino, hacer la suma recursiva sobre la primera mitad de los arreglos, y luego la suma recursiva sobre la segunda mitad de los arreglos.
}

int main() {
   int a[N], b[N], c[N],i;
   for (i = 0; i < N; i++)
   {
      a[i]=i;
      b[i]=2;
   }
   
   rec_vector_add(a, b, c, N);
   for (i = 0; i < N; i++)
   {
      printf("c[%d]= %d \n", i, c[i]);
   }
   
}
