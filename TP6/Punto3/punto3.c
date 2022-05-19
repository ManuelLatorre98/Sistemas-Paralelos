#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int inc(int var){
        usleep(1000);
        return var + 1;
}

int main(int argc, char **argv){
        int var;

        var = 10;
// 	#pragma omp parallel num_threads(4) private(var)
//  #pragma omp parallel num_threads(4) firstprivate(var)
//  #pragma omp parallel num_threads(4) shared(var)
	#pragma omp parallel num_threads(4) shared(var)
        { //región paralela
                #pragma omp critical
                  var = inc(var);
                printf("var (in): %d\n", var);
        }
        printf("var (out): %d\n", var);
        return 0;
}
