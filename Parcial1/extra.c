#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>
int main() {

    int i, elementos = 1000005, cantElemReg=sizeof(__m256i)/sizeof(int), cantIteraciones=elementos/cantElemReg;
    int *v;
    __m256i vActual, v_2, v_2Neg,v_80, vComp1,vComp2, vMenor, vMayor, vAux, vResta,vMul,vActualAux,vResult;
    v = malloc(elementos * sizeof(int));
    if(posix_memalign((void**)&v, 32, sizeof(int)*elementos)!=0){//espacio para 8 elementos
            return 1;
        }

    // no vectorizar este for
    for (i = 0; i < elementos; i++)
        v[i] = rand() % 10000;

    printf("v[0]=%11d, ", v[0]);
    printf("v[11]=%11d, ", v[11]);
    printf("v[elementos-1]=%11d\n", v[elementos-1]);

    v_2= _mm256_set1_epi32 (2);//lleno vector con 2
    v_2Neg= _mm256_set1_epi32 (-2);//lleno vector con -2
    v_80= _mm256_set1_epi32 (80);//Los saltos entre comparaciones son de 80 esto es lo que le voy a sumar

    vComp2= _mm256_setr_epi32 (0,10,20,30,40,50,60,70);//i*10
    
    for(i=0; i < cantIteraciones; i++){
        vActual= _mm256_load_si256 ((__m256i const *) v+(i));
        vComp1= _mm256_mullo_epi32 (v_2, vActual); //2*v[i]
        vResta= _mm256_sub_epi32 (vActual, v_2);//v[i]-2
        vAux= _mm256_cmpgt_epi32 (vComp2, vComp1);//vComp2>vComp1=-1, vComp2<=vComp1=0
        vMenor= _mm256_and_si256 (vAux, v_2);//Si -1, es decir primer caso del if cargo 2
        vMayor= _mm256_andnot_si256 (vAux, v_2Neg);//Si 0, es decir segundo caso del if cargo -2
        vMul= _mm256_or_si256 (vMenor, vMayor);

        vActual= _mm256_and_si256 (vAux, vActual);//Array con los elementos de vActual para el caso del primer if
        vActualAux= _mm256_andnot_si256 (vAux, vResta);//Array con los elementos de vActual= v[i]-2 para segundoIf
        vActual= _mm256_or_si256 (vActual, vActualAux);//Junto todo en un vector para que no queden ceros
        
        vResult= _mm256_mullo_epi32 (vActual, vMul);

        _mm256_store_si256 ((__m256i *) v+(i), vResult);//Reemplazo valores por el resultado
        vComp2= _mm256_add_epi32 (vComp2, v_80);//Agrego 80 al vComp para siguiente iteracion
    }

    for (i = (cantElemReg*cantIteraciones); i < elementos; i++) {//Elementos fuera de la iteracion los resuelvo escalarmente
        if(2 * v[i] < i * 10)
            v[i] = v[i] * 2;
        else
            v[i] = (v[i] - 2) * -2;
    }

    printf("v[0]=%11d, ", v[0]);
    printf("v[11]=%11d, ", v[11]);
    printf("v[elementos-1]=%11d\n", v[elementos-1]);

    return 0;
}
