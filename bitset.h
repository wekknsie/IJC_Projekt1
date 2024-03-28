// bitset.h
// Řešení IJC-DU1, příklad a), 20.3.2024
// Autor: Jan Hájek, FIT
// Přeloženo: gcc 13.2.0
// hlavičkový soubor s makrama a inline funkcema, omezení při překladu s argumentem "-pedantic", kdy makro bitset_getbit není zcela dle normy jazyka C 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "error.h"

typedef unsigned long bitset_index_t;

typedef struct {
    unsigned long bits;
} bitset_t;

#define N 666000000

#define bitset_create(jmeno_pole,velikost) \
    bitset_t jmeno_pole[(velikost/((sizeof(unsigned long) * 8))) + 2]; \
    jmeno_pole[0].bits = velikost; \
    for(unsigned i=1;i<(jmeno_pole[0].bits)/((sizeof(unsigned long) * 8))+2;i++){ \
        jmeno_pole[i].bits = 0; \
    }
    

#define bitset_alloc(jmeno_pole,velikost) \
    bitset_t* jmeno_pole = malloc(sizeof(bitset_t) * ((velikost/((sizeof(unsigned long) * 8))) + 2)); \
    if(jmeno_pole == NULL){ \
        error_exit("Can't allocate memory"); \
    } \
    jmeno_pole[0].bits = velikost; \
    for(unsigned i=1;i<(jmeno_pole[0].bits)/((sizeof(unsigned long) * 8))+2;i++){ \
        jmeno_pole[i].bits = 0; \
    }

#ifdef USE_INLINE

extern inline void bitset_free(bitset_t* jmeno_pole){
    free(jmeno_pole);
}

extern inline int bitset_size(bitset_t *jmeno_pole){
    return jmeno_pole[0].bits;
}

extern inline void bitset_fill(bitset_t *jmeno_pole, int bool_vyraz){
    for(unsigned i=1;i<(jmeno_pole[0].bits)/((sizeof(unsigned long) * 8))+2;i++){
        if(bool_vyraz){
            jmeno_pole[i].bits = -1;
        }else{
            jmeno_pole[i].bits = 0;
        }
    }
}

extern inline unsigned long bitset_setbit(bitset_t *jmeno_pole, unsigned long index, int bool_vyraz){
    if(jmeno_pole[0].bits < index){
        error_exit("Used wrong index");
    }
    int idx = index / (sizeof(unsigned long) * 8);
    int bitIdx = index % (sizeof(unsigned long) * 8);
    if(bitIdx == 0){
        bitIdx = sizeof(unsigned long) * 8 - 1;
        idx--;
    }else{
        bitIdx--;
    }
    if(bool_vyraz){
        return jmeno_pole[idx+1].bits |= (1UL << bitIdx);
    }else{
        return jmeno_pole[idx+1].bits &= ~(1UL << bitIdx);
    }
}

extern inline unsigned long bitset_getbit(bitset_t *jmeno_pole, unsigned long index){
    if(jmeno_pole[0].bits < index){
        error_exit("Used wrong index");
    }
    int idx = index / (sizeof(unsigned long) * 8);
    int bitIdx = index % (sizeof(unsigned long) * 8);
    if(bitIdx == 0){
        bitIdx = sizeof(unsigned long) * 8 - 1;
        idx--;
    }else{
        bitIdx--;
    }
    return jmeno_pole[idx+1].bits >> bitIdx & 1UL;
}

#else

#define bitset_free(jmeno_pole) free(jmeno_pole);

#define bitset_size(jmeno_pole) jmeno_pole[0]

#define bitset_fill(jmeno_pole,bool_vyraz) \
    for(unsigned i=1;i<(jmeno_pole[0].bits)/((sizeof(unsigned long) * 8))+2;i++){ \
        if(bool_vyraz){ \
            jmeno_pole[i].bits = -1; \
        }else{ \
            jmeno_pole[i].bits = 0; \
        } \
    }

#define bitset_setbit(jmeno_pole,index,bool_vyraz) \
    if(jmeno_pole[0].bits < index){ \
        error_exit("Used wrong index"); \
    } \
    int idx = index / (sizeof(unsigned long) * 8); \
    int bitIdx = index % (sizeof(unsigned long) * 8); \
    if(bitIdx == 0){ \
        bitIdx = sizeof(unsigned long) * 8 - 1; \
        idx--; \
    }else{ \
        bitIdx--; \
    } \
    if(bool_vyraz){ \
        jmeno_pole[idx+1].bits |= (1UL << bitIdx); \
    }else{ \
        jmeno_pole[idx+1].bits &= ~(1UL << bitIdx); \
    }

#define bitset_getbit(jmeno_pole,index) ({\
    if(jmeno_pole[0].bits < index){ \
        error_exit("Used wrong index"); \
    } \
    int idx = index / (sizeof(unsigned long) * 8); \
    int bitIdx = index % (sizeof(unsigned long) * 8); \
    if(bitIdx == 0){ \
        bitIdx = sizeof(unsigned long) * 8 - 1; \
        idx--; \
    }else{ \
        bitIdx--; \
    } \
    (jmeno_pole[idx+1].bits >> bitIdx) & 1UL;\
})

#endif