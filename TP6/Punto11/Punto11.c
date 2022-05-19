#include <stdio.h>
#include <omp.h> 
int primo(int n) {
   int i,res,mitad;
   i = 2;
   res = 1;
   mitad = n / 2;
   while(res != 0 && i <= mitad) {
      res = n % i;
         i++;
   }  
   return res;
}

int main(){
    int i,min=10, max=31, cantPrimos=0;
    double start;
    double end;
    #pragma omp parallel
    {
        start=omp_get_wtime();
        #pragma omp for schedule(static)//Testeado que es el optimo comparando >
        for(i=min; i<=max; i++){
          //Agregar critical o mejor reduction para no comprometer cantPrimos
            cantPrimos+=primo(i);
            
        }
        end= omp_get_wtime();
        printf("tiempo de hilo: %f\n", end-start);
        }
    
    printf("cantPrimos: %d\n", cantPrimos);
    return cantPrimos;
}

