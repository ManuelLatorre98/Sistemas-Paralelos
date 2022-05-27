#include <stdio.h>
#include <math.h>
#include <omp.h>
#define N 1000
#define PASOS 500

int main()
{
   double A[N][N], b[N], x[N], x2[N];
   double max=-1.0, q=0, e;
   int s;
   int i, j, k, n=N, pasos=PASOS;
   double start;
   double end;
   start= omp_get_wtime();
      
   //inicialización
   #pragma omp parallel
   {  
      #pragma omp for nowait
      for (i=0;i<n;i++)
         b[i] = 0.5;
      
      #pragma omp for nowait
      for (i=0;i<n;i++)
         x[i] = 0.5+(double)i/n;

      #pragma omp for nowait
      for (i=0;i<n;i++)
         for (j=0;j<n;j++)
               A[i][j] = 0.6*(sin(i+j)+1)/2;
   }
   //fin inicialización
   
   for (k=0;k<pasos;k++) { //Existe una dependencia en b
      q=1;
         for (i=0;i<n;i++) {//Existe dependencia en x2
            s = b[i];
            #pragma omp parallel reduction (*:q)
            {
               #pragma omp for reduction (+:s) private (e)
               for (j=0;j<n;j++) {
                  e = sin(A[i][j] * x[j]);//independiente
                  s+= (int) (e * e * e + 2 * e * e + 5 * e);//reduction
               }
            }
               x2[i] = x2[i-1] + s;//dependencia de iteracion anterior
               q *= sin(s);
            
         }
      #pragma omp parallel
      {
         #pragma omp for //no uso nowait porque necesito los valores x[i] luego
         for (i=0;i<n;i++)
            x[i] = x2[i];

         #pragma omp for
         for (i=0;i<n/2;i++)
            b[i] = b[i] + x[i] + 0.00002;
      }

      if (max<q) {
         max = q;
         printf("max: %.10e\n", max);
      }
   }
   end = omp_get_wtime();
   printf("Tiempo de ejecucion %f seconds\n", end-start);
   printf("max final: %.10e\n", max);
   return max;
}
