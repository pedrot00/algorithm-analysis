#include<iostream>
#include<cmath>
#include<stdlib.h>
using namespace std;

//O(n^2)
void bubbleSort(int v[], int n){
    bool troca;
    for(int i=0; i<n-1; i++){
        troca = false;
        for(int j=0; j<n-1-i; j++){
            if(v[j] > v[j+1]){
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                troca = true;
            }
        }
        if(!troca) break;
    }
}


int main(){


    return 0;
}