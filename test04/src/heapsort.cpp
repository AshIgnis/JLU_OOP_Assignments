#include "heapsort.h"
#include <algorithm>
#include <iostream>

void HeapAdjust(int *L, int s, int m){
    int temp,j;
    temp = L[s];
    for(j = 2*s; j <= m; j*=2){
        if(j < m && L[j] < L[j+1])
            ++j;
        if(temp >= L[j])
            break;
        L[s] = L[j];
        s = j;
    }
    L[s] = temp;
}

void HeapSort(int *L, int x){
    int i;
    for(i = x/2; i > 0; i--)
        HeapAdjust(L,i,x);
    for(i = x; i > 1; i--){
        std::swap(L[1], L[i]);
        HeapAdjust(L,1,i-1);
    }
}