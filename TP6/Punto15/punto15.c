#include <stdio.h>
#include <omp.h>
#define N 10//2000000000
void vector_add(int *A, int *B, int *C, int n) {
   int i;
   for (i = 0; i < n; i++)
      C[i] = A[i] + B[i];
}

void rec_vector_add(int *A, int *B, int *C, int n) {
// si es el caso base, llamar a vector_add
   int base=10;
   int mitad;
   int mitadMayor;
   if(n<=base){
      vector_add(A, B, C, n);
   }else{
      mitad=n/2;
      mitadMayor=mitad;
      #pragma omp task
      {
         printf("menor --> id: %d \n",omp_get_thread_num());
         rec_vector_add(A,B,C,mitad);
      }
      if(n%2 ==1){//Si la division daba imapar añade uno al mayor
         mitadMayor++;
      }
      #pragma omp task
      {
         printf("mayor --> id: %d \n",omp_get_thread_num());
         rec_vector_add(A+mitad,B+mitad,C+mitad,mitadMayor);
      }
   }
// sino, hacer la suma recursiva sobre la primera mitad de los arreglos, y luego la suma recursiva sobre la segunda mitad de los arreglos.
}

int main() {
   int a[N], b[N] , c[N];
   int i;
   for (i = 0; i < N; i++){//inicializa a y b
      a[i]=i;//a va de 0 a N
      b[i]=2;//cargo b con 2
   }
   
   #pragma omp parallel
   {
      #pragma omp single
      rec_vector_add(a,b,c,N);
   }
}
