#include <stdio.h>
#include <unistd.h>
#include <omp.h>
int main(int argc, char **argv)
{
    int id;
   // omp_set_dynamic(0);
    #pragma omp parallel num_threads(10) private(id)
    {
        id = omp_get_thread_num();
        usleep(500);
        printf("Soy el hilo %d de %d hilos...\n", id, omp_get_num_threads());
        /*if(id==0){ //Como hay un unico hilo que tendra id=0 si pongo el if solo imprimira ese hilo
            printf("Cantidad de numeros de la region paralela: %d\n", omp_get_num_threads());
        }*/
    }
        if(id==0){ //Como hay un unico hilo que tendra id=0 si pongo el if solo imprimira ese hilo
            printf("Cantidad de numeros de la region paralela: %d\n", omp_get_num_threads());
        }

    return 0;
}
