#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>
int main() {
    int i, elementos = 100000000, nroElemReg=sizeof(__m256i)/sizeof(int);
    int nroIteraciones=elementos/nroElemReg;
    int *v;
    __m256i vActual,v_5,v_5Neg,vMayor,vMenor,vAux,vComp,vOp,vResOp;
    //v = malloc(elementos * sizeof(int));

    //Libero espacio para registro de elementos
    if(posix_memalign((void**)&v,32, sizeof(int)*elementos)!=0){
        return 1;
    }

    //no vectorizar este for
    for (i = 0; i < elementos; i++)
        v[i] = i;

    v_5= _mm256_set1_epi32(5);//Vector con cincos
    v_5Neg= _mm256_set1_epi32(-5);//Vector con menos cincos

    vComp= _mm256_set1_epi32(50000000);//Vector para comprar

    for (i = 0; i < nroIteraciones; i++){
        vActual= _mm256_load_si256 ((__m256i const *)v +(i));
        vAux= _mm256_cmpgt_epi32 (vActual, vComp);//-1 si vActual>vComp 0 caso contrario
        vMayor= _mm256_and_si256 (vAux, v_5Neg);//si -1 pone -5, caso contrario pone 0
        vMenor= _mm256_andnot_si256 (vAux, v_5);//si 0 pone 5, caso contrario pone 0
        vOp= _mm256_or_si256 (vMayor, vMenor);//Junto -5 y 5 en un solo vector
        vResOp= _mm256_add_epi32 (vActual, vOp);//Opero
        _mm256_store_si256 ((__m256i *) v+(i), vResOp);//Almaceno en el inicio del v de la iteracion actual
    }

    for (i = (nroElemReg*nroIteraciones); i < elementos; i++)//Contemplo elem fuera de iteraciones
        if (v[i] > 50000000)
            v[i] = v[i] - 5;
        else
            v[i] = v[i] + 5;

    printf("elemento 0: %d\n",v[0]);
    printf("elemento 499999999: %d\n",v[49999999]);
    printf("elemento 500000000: %d\n",v[50000000]);
    printf("elemento 999999999: %d\n",v[99999999]);
    return 0;
}
