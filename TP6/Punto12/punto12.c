#include <stdio.h>
#include <math.h>
#include <omp.h> 
#define N 1000
#define PASOS 1000
 
int main()
{
   double A[N][N], b[N], x[N], x2[N];
   double max=-1.0, q=0, s, e;
   int i, j, k, n=N, pasos=PASOS;
 
   //inicialización
   for (i=0;i<n;i++)
      b[i] = 0.5;
   for (i=0;i<n;i++)
      x[i] = 0.5+(double)i/n;
   for (i=0;i<n;i++)
      for (j=0;j<n;j++)
         A[i][j] = 0.6*(sin(i+j)+1)/2;
   //fin inicialización
   #pragma omp parallel
   {  
      #pragma omp for private (x2, q)//x2 private asi evita dependencia en 4to for
      for (k=0;k<pasos;k++) {
         q=1;
         #pragma omp for nowait
         for (i=0;i<n;i++) {
            s = b[i];

            #pragma omp for nowait private(e) //Elimino dependencia poniendo a e como privada para cada iteracion
            for (j=0;j<n;j++) {
               e = sin(A[i][j] * x[j]);
               s+= e * e * e + 2 * e * e + 5 * e;
            }
            x2[i] = s;
            q *= sin(s);
         }

         #pragma omp for nowait
         for (i=0;i<n;i++)
            x[i] = x2[i];

         #pragma omp for nowait
         for (i=0;i<n/2;i++)
            b[i] = b[i] + 0.00002;

         if (max<q) {
            max = q;
            printf("max: %.10e\n", max);
         }
      }
   }
   printf("max final: %.10e\n", max);
   return max;
}

