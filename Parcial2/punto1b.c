#include<stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 25000000

int getCant(int inicio, int fin, int *datos){
    int k,n1,n2,limite,divisor_comun=0;
    int i,cant_coprimos=0;
    for(k=inicio;k<fin;k=k+2){
    	 n1 = datos[k];
    	 n2 = datos[k+1];
   	 
    	 if(n1>n2)
         limite = n2/2;
    	 else
         limite = n1/2;
      i=2;
      do{
         divisor_comun = n1%i==0 && n2%i==0;
         i++;
    	 } while (!divisor_comun && i<=limite);
    
    	 if(!divisor_comun)
         cant_coprimos++;
   }
   return cant_coprimos;
}

int calcularPrimos(int inicio, int fin, int n,int *datos){
    int sum=0,sum1=0,sum2=0;
    int mitadMenor=n/2, mitadMayor=mitadMenor;
    if(n<1000){//caso base
        sum= getCant(inicio,fin,datos);
    }else{
        #pragma omp task shared(sum1)
        sum1= calcularPrimos(inicio,inicio+mitadMenor,mitadMenor,datos);
        
        if(n%2==1){//si da impar añade uno al mayor
            mitadMayor++;
        }

        #pragma omp task shared(sum2)
        sum2= calcularPrimos(inicio+mitadMenor,fin, mitadMayor, datos);
        
        #pragma omp taskwait
        sum=sum1+sum2;
    }
    return sum;
}

void main(){
    int k;
    int* datos = malloc(N*sizeof(int));
    int cant_coprimos;
    
    #pragma omp parallel 
    {
        #pragma omp single
        {
            for(k=0;k<N;k++)
                datos[k]=rand()%10000;
            cant_coprimos= calcularPrimos(0,N,N,datos);
        }
    }
    printf("Cantidad de coprimos: %d\n",cant_coprimos); 
}