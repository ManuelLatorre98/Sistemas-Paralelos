#include <stdio.h>
#include <omp.h>
#define N 800000000
#define step 1.0/(float)N
float pi(long inicio, long final){
   long i;
   float x, sum=0.0;
   for (i = inicio ; i < final; i++){
      x = (i + 0.5) * step;
      sum+= 4.0 / (1.0 + x * x);
   }
   return sum;
}

float sumPi(long inicio,long final, long n){
   long mitad= n/2, segundaMitad=mitad;
   float sum,sum1,sum2;
   if(n<1000){//Caso base
      sum= pi(inicio, final);
   }else{
      #pragma omp task shared(sum1)
      sum1= sumPi(inicio, inicio+mitad, mitad);
      if(n%2!=0){
         segundaMitad++;
      }
      #pragma omp task shared(sum2)
      sum2= sumPi(inicio+mitad, final, segundaMitad);
      #pragma omp taskwait
      sum=sum1+sum2;
   }
   return sum;
}

void main(){
   float sum, pi;
   #pragma omp parallel
   { 
      #pragma omp single
      sum=sumPi(0,N,N);
   }

   pi = step * sum;
   printf("%f\n",pi);
}