// primes.c
// Řešení IJC-DU1, příklad b), 20.3.2024
// Autor: Jan Hájek, FIT
// Přeloženo: gcc 13.2.0
// implementace maker a inline funkcí na Eratostenovém sítu

#include "bitset.h"

void Eratosthenes(bitset_t *pole);

int main(){
    double start = clock();
    bitset_alloc(pole, N);
    bitset_fill(pole,1);
    
    Eratosthenes(pole);

    int tmp=0;
    for(unsigned i=N;tmp<10;i--){
        if(bitset_getbit(pole,i) == 1){
            printf("%d\n", i);
            tmp++;            
        }
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    return 0;
}

void Eratosthenes(bitset_t *pole){
    for(unsigned i=2;i*i<N;i++){
        if(bitset_getbit(pole,i) == 1){
            for(unsigned j=i*i;j<=N;j+=i){
                bitset_setbit(pole,j,0);
            }
        }
    }
}