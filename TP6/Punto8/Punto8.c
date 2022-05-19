#include <omp.h>
int main()
{
    int i,j;

    //Static ya que se realiza siempre la misma iteracion y los bloques seran iguales
    #pragma omp parallel for shchedule (static) private(j)
    for(i = 0; i< 100000000; i++)
        for(j=0; j<100;j++);

    //Static sola o n par
    #pragma omp parallel for shchedule (guided) private(j)
    for(i = 0; i< 100000000; i++)
        if(i % 2 == 0)
            for(int j=0; j<100; j++);
        else
            for(int j=0; j < 1000;j++);
    
    //Static tambien, al tener muchas iteraciones tenemos 50% de posibilidades
    //de que toque par o impar
    #pragma omp parallel for shchedule (guided) private(j)
    for(i = 0; i< 100000000; i++)
        if(rand() % 2 == 0)
            for(int j=0; j<100; j++);
        else
            for(int j=0; j < 1000;j++);

    //Guided, ya que hay procesos que llegan primero por lo tanto van 
    //a obtener una pieza mas grande, el resto tendra piezas mas pequeñas 
    //progresivamente y asi se lograria un mejor balance de hilos
    //Con el tamaño de la pieza correcto podria ser dynamic
    int t= omp_get_thread_num();
    #pragma omp parallel for shchedule (guided) private(j)
    for(i = 0; i< 100000000; i++)
        if(rand() % 2 == 0)
            for(int j=0; j<100; j++);
        else
            for(int j=0; j < 1000;j++);
}