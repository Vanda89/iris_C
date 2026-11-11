#include <stdlib.h>
#include <stdio.h>
#include "recursion.h"

long fast_power(long x, int n) {
    // condition d'arret
    if(n == 0) return 1;

    // appel récursif descente
    long half = fast_power(x, n/2);

    // remontée
    if (n % 2 == 0) {
        return half * half;
    } else{
        return x * half * half;
    }
}

void print_binary(unsigned int n) {
    // condition d'arrêt
    if(n==0) {
        printf("0");
        return;
    }

    if(n == 1) {
       printf("1");
        return; 
    }

    // appel récursif descente
    print_binary( n / 2);
    // remontée
    printf("%d", n % 2);    
}

