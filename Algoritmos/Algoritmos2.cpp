#include<iostream>
#include<cmath>
#include<stdlib.h>
using namespace std;

//implementacao busca sequencial
// O(n)
int buscaSeq(int *v[], int end, int chave){
	for(int i = 0; i < end-1; i++){
		if(*v[i] == chave ){
			return i;
		}
	}
	return -1;
}
//implementacao busca binaria recursiva
//O (log n)
int buscaBinRecursiva(int beg, int end, int v[], int chave){
	if(beg > end) return -1;
	int meio = (end-beg)/2 + beg;
	
	if(chave == v[meio]) 
		return meio;
	else if(chave > v[meio])
		return buscaBinRecursiva(meio+1, end, v, chave);
	
	else
		return buscaBinRecursiva(beg, meio-1, v, chave);
}

//implementacao busca binaria iterativa
int buscaBinIterativa(int beg, int end, int v[], int chave){	//se a passagem de parametros for correta
	do{
		int meio = (end - beg)/2 + beg;
		
		if(chave == v[meio]) return meio;
		else if (chave > v[meio]){
			beg = meio +1;
		}
		else{
			end = meio - 1;
		}
	} while(beg <= end);
	return -1;
}

//implementacao busca binaria iterativa
int buscaBinIterativa2(int beg, int end, int v[], int chave){	//verifica passagem de parametros
	while(beg <= end){
		int meio = (end - beg)/2 + beg;
		
		if(chave == v[meio]) return meio;
		else if (chave > v[meio]){
			beg = meio +1;
		}
		else{
			end = meio - 1;
		}
	}
	return -1;
}

//implementacao busca binaria que acha o menor valor apos a chave
int buscaBinaria(int v[], int beg, int end, int chave) {
    if (beg > end) {
        if (beg <= end + 1 && beg < (end + 2)) {
            return beg;
        }
        return -1; 
    }
    int meio = beg + (end - beg) / 2;
    
    if (v[meio] <= chave) {
        return buscaBinaria(v, meio + 1, end, chave);
    } else {
        int resultado = buscaBinaria(v, beg, meio - 1, chave);
        
        if (resultado == -1)
            return meio;
        return resultado;
    }
}


int main(){

	return 0;
}