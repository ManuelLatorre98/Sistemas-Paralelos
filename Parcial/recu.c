#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <immintrin.h>

int main() {

   int i, elementos = 1000005, cantElemReg= sizeof(__m128)/sizeof(float), cantIteraciones= elementos/cantElemReg;
   float *v;
   __m128 vActual,v_250,v_750, vComp1, vComp2,vMayor_250,vMenor_250,vMayor_750,vMenor_750,vEnRango,vFueraRango,vRaiz,vMult,vResult;

   //v = malloc(elementos * sizeof(float));
    //Libero espacio para registro de elementos
    if(posix_memalign((void**)&v,16, sizeof(float)*elementos)!=0){
        return 1;
    }

    //Inicializa con valores del rango [0,1000]
    for (i = 0; i < elementos; i++)
        v[i] = rand() % 1000;

    printf("v[0]=%11.2f, ", v[0]);
    printf("v[3]=%11.2f, ", v[3]);
    printf("v[11]=%11.2f, ", v[11]);
    printf("v[elementos-1]=%11.2f\n", v[elementos-1]);


    v_250= _mm_set_ps1 (250); //conjunto: sse, lleno vector con 250
    v_750= _mm_set_ps1 (750);

    for(i=0; i<cantIteraciones; i++){
        vActual=  _mm_load_ps((float const*) v+(i*4));//sse
        vRaiz= _mm_sqrt_ps (vActual);//Calcula la raiz de cada vActual
        vMult= _mm_mul_ps (vActual, vActual);//Multiplica por si mismo todos los vActual
        
        vComp2= _mm_cmpgt_ps (v_750, vActual);//vActual < 750 --> -1, vActual >= 750 --> 0;
        vMenor_750= _mm_and_ps (vActual, vComp2);//Contiene los elementos: vActual < 750, las pos que contenian >=750 y estan en 0


        vComp1= _mm_cmpgt_ps (vMenor_750, v_250);//vActual>250 --> -1, vActual<=250 --> 0
        vEnRango = _mm_and_ps (vMenor_750, vComp1);//Pone las raices en las posiciones que cumplen el rango
        
        //vEnRango= _mm_and_ps (vMenor_750, vComp1);//Contiene los elementos 750>elem>250, las pos que contenian 750<=elem<=250 estan en 0
        
        vFueraRango= _mm_andnot_ps (vComp1,vMult);//Ubica las mult de fuera del rango en las posiciones en 0

        vResult= _mm_or_ps (vEnRango, vFueraRango);//Junto lo operado

        _mm_store_ps ((float*) v+(i*4), vResult);//Almaceno lo operado

    }



    for (i = (cantElemReg*cantIteraciones); i < elementos; i++) {//Los elementos que quedaron fuera de las iteraciones los opero escalarmente
        if(v[i] > 250 && v[i] < 750 )
            v[i] = sqrt(v[i]);
        else
            v[i] = v[i] * v[i];
    }

    printf("v[0]=%11.2f, ", v[0]);
    printf("v[3]=%11.2f, ", v[3]);
    printf("v[11]=%11.2f, ", v[11]);
    printf("v[elementos-1]=%11.2f\n", v[elementos-1]);

    return 0;
}
