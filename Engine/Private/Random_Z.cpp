/*
ran1(long *)	__text	000B7484	000001BA	0000002C	00000004	R	.	.	.	.	.	B	T	.
InitRandom(long)	__text	000B763E	00000024	0000001C	00000004	R	.	.	.	.	.	B	T	.
Alea(long,long)	__text	000B7662	0000005A	0000002C	00000008	R	.	.	.	.	.	B	T	.
Random(void)	__text	000B76BC	00000014	0000001C		R	.	.	.	.	.	B	T	.
*/

#include <Random_Z.h>

//Note the .f suffixes for floats
#define IA 16807
#define IM 2147483647
#define AM (1.0f/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7f
#define RNMX (1.0f-EPS)

float ran1(long *idum){
    int j;
    long k;
    static long iy=0;
    static long iv[NTAB];
    float temp;

    if(*idum <= 0 || !iy){
        if(-(*idum) < 1) *idum=1;
        else *idum = -(*idum);
        for(j=NTAB+7;j>=0;j--) {
            k=(*idum)/IQ;
            *idum=IA*(*idum-k*IQ)-IR*k;
            if(*idum < 0) *idum += IM;
            if(j < NTAB) iv[j] = *idum;
        }
        iy = iv[0];
    }
    k=(*idum)/IQ;
    *idum=IA*(*idum-k*IQ)-IR*k;
    if (*idum < 0) *idum += IM;
    j=iy/NDIV;
    iy=iv[j];
    iv[j] = *idum;
    if((temp=AM*iy) > RNMX) return RNMX;
    else return temp;
}

long SEED; //not externally defined from InitRandom and co.

void InitRandom(long seed){
    if(seed < 0){
        SEED = seed;
    }else{
        SEED = -seed;
    }
    ran1(&SEED);
}

long Alea(long i_Min, long i_Max) {
    int l_AddValue;
    float l_Rand = ((0.9999f + (i_Max - i_Min)) * ran1(&SEED));
    if (l_Rand >= 0.0f) {
        l_AddValue = l_Rand;
    }
    else {
        l_AddValue = 1.f - l_Rand;
        l_AddValue = -l_AddValue;
    }
    return i_Min + l_AddValue;
}

float Random() {
    return ran1(&SEED);
}