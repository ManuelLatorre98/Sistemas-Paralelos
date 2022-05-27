#include <stdio.h>
#include <omp.h>
#define N 800000000
#define step 1.0/(double)N

double pi(int inicio,int fin){
   double sum=0.0,x;
   int i;
   for(i=inicio;i<fin;i++){
      x = (i + 0.5) * step;
      sum = sum +( 4.0 / (1.0 + x * x));
   }
   return sum;
}

double rec_pi(int inicio,int fin,int n){
   double sum=0.0,sum1=0.0,sum2=0.0;
   int mitad=n/2;
   if(n<1000){//caso base
      sum=pi(inicio,fin);
   }else{
      #pragma omp task shared(sum1)
      sum1=rec_pi(inicio,inicio+mitad,mitad);
      #pragma omp task shared(sum2)
      sum2=rec_pi(inicio+mitad,fin,mitad);
      #pragma omp taskwait
      sum=sum1+sum2;
   }
   return sum;
}


void main () {
        //long num_steps=10000;
        double sum=0.0,pi=0.0;
        #pragma omp parallel
        {
         #pragma omp single
           sum=rec_pi(0,N,N);
        }
        pi=step *sum;
        printf("%f \n",pi);
}
