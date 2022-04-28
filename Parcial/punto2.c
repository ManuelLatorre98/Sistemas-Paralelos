#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>
int main(){
    int i, elementos= 1000000,cantElemReg=(sizeof(__m256i)/sizeof(int)), nroIteraciones=elementos/cantElemReg ;//registros de 8 porque los vectores son de 256
    int *v,*resultado;
    __m256i vActual,v_2, v_2Neg, vComp, v_80,vAux, vMenor,vMayor,vMul,vResult;
    //v = malloc(elementos * sizeof(int));
    if(posix_memalign((void**)&v, 32, sizeof(int)*elementos)!=0){//espacio para 8 elementos
        return 1;
    }

    /*if(posix_memalign((void**)&resultado, 32, sizeof(int)* elementos)!=0){//Espacio para almacenar el resultado
        return 1;
    }*/

    for (i = 0; i < elementos; i++)
        v[i] = rand() % 10000;

    printf("v[0]=%11d, ", v[0]);
    printf("v[11]=%11d, ", v[11]);
    printf("v[elementos-1]=%11d\n", v[elementos-1]);

    v_2= _mm256_set1_epi32 (2);
    v_2Neg= _mm256_set1_epi32 (-2);
    v_80= _mm256_set1_epi32 (80);//Comparo i*10 por iteracion es decir que luego saltaran de 80 en 80

    vComp= _mm256_setr_epi32 (0,10,20,30,40,50,60,70);//Compara i*10 como hago 8 elem de una contemplo los 8 i*10
    for (i = 0; i < nroIteraciones; i++){
        vActual = _mm256_load_si256((__m256i const *)v+(i));//cargo en vActual con lo que entre desde la pos v+i
        vAux = _mm256_cmpgt_epi32 (vComp, vActual);//vComp>vActual=-1 vComp<=vActual=0
        vMenor= _mm256_and_si256 (vAux, v_2);//pone un 2 donde hay -1
        vMayor= _mm256_andnot_si256 (vAux, v_2Neg);//pone un -2 donde hay 0
        vMul= _mm256_or_si256 (vMenor, vMayor);//junto vMenor con vMayor
        vResult= _mm256_mullo_epi32 (vActual, vMul);//multiplico vActual con vMul
        _mm256_store_si256 ((__m256i *) v+(i), vResult);//Reemplazo valores por el resultado
        _mm256_add_epi32 (vComp, v_80);//Agrego 80 al vComp para siguiente iteracion
    }



   for (i = (nroIteraciones*cantElemReg); i < elementos; i++) {
        if(v[i] < i*10)
            v[i] = v[i] * 2;
        else
            v[i] = v[i] * -2;
    }

    printf("v[0]=%11d, ", v[0]);
    printf("v[11]=%11d, ", v[11]);
    printf("v[elementos-1]=%11d\n", v[elementos-1]);

    return 0;
}