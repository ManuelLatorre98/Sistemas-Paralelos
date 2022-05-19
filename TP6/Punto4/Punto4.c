#include <stdio.h>
#include <omp.h> 

int main(){
    int id;
    #pragma omp parallel num_threads(10) private(id)
    {
        id  = omp_get_thread_num();
        printf("%d: Hola!\n", id);
        printf("%d: Adios!\n", id);
    }
    return 0;
}
