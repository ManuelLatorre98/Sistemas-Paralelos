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
    
    //Static tambien
    #pragma omp parallel for shchedule (guided) private(j)
    for(i = 0; i< 100000000; i++)
        if(rand() % 2 == 0)
            for(int j=0; j<100; j++);
        else
            for(int j=0; j < 1000;j++);

    //Guided
    int t= omp_get_thread_num();
    #pragma omp parallel for shchedule (guided) private(j)
    for(i = 0; i< 100000000; i++)
        if(rand() % 2 == 0)
            for(int j=0; j<100; j++);
        else
            for(int j=0; j < 1000;j++);
}