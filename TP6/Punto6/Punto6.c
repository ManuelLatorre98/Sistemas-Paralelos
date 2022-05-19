#include <stdio.h>
#include <unistd.h>
#include <omp.h>
void trabajo(int id){
    printf("%d: Trabajo muy duro...\n", id);
    sleep(1);
    printf("%d: como un esclavo!\n", id);
    sleep(1);
}

int main(){
    int i;
    double start;
    double end;
    start= omp_get_wtime();
    /*trabajo(0);
    trabajo(1);
    trabajo(2);
    trabajo(3);
    trabajo(4);
    trabajo(5);
    trabajo(6);
    trabajo(7);*/
    #pragma omp parallel for
    for(i=0;i<8; i= i + 1)
        trabajo(i);
    end = omp_get_wtime();
    printf("Tiempo de ejecucion %f seconds\n", end-start);
    return 0;
}
