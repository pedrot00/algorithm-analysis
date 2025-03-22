#include<iostream>
#include<cmath>
#include<stdlib.h>
using namespace std;


/* Perceba que a soma de inteiros eh uma das operacoes mais baratas no processamento, mesmo assim, como ele executa
10.000 * 10.0000 vezes ele acaba sendo a OB, se o for mais interna interasse so 1 ou menos elementos, obviamente
a operacao basica seria a declaracao da variavel y */
void func1_Slide1(){
    double x = 3.14*5.2*sqrt(10.5)*pow(23.2,44.2);
    int soma = 0;
    for(int i=0;i<10000;i++) {
        double y = 3.14*5.2*sqrt(10.5)*pow(23.2,44.2) + sin(12.2*i);
        for(int j=0;j<10000;j++)
            soma += y*j;        //operacao mais interna, operacao basica do algoritmo
    }
}

/* A operacao dentro do for triplo gasta apx. 18s pra compilar, o do for duplo apx.24ms 
A primeira op. eh realizado (2.000 * 2.000) vezes e a segunda op. eh realizada (2.000 * 2.000 * 2.000)
se o for mais interno da op. 2 fosse menor o tempo seria bem menor */
void fun2_Slide1(){
    int soma = 0;
    long long t0;

    t0 = clock();
    for(int i=0;i<2000;i++) 
        for(int j=0;j<2000;j++)
            soma += 3.14*5.2*sqrt(soma)*pow(soma/100,44.2);
        
    cout << "Tempo 1 (ms): " << ((clock()-t0)*1.0/CLOCKS_PER_SEC)*1000 << endl;	//temporiza o clock
    
    soma = 0;
    t0 = clock();
    for(int i=0;i<2000;i++) 
        for(int j=0;j<2000;j++)
            for(int k=0;k<2000;k++)
                soma++;             //operacao mais interna, operacao basica do algoritmo
    
    cout << "Tempo 2 (ms): " << ((clock()-t0)*1.0/CLOCKS_PER_SEC)*1000 << endl;
}

/* T(n) = Top . C(n)
   C(n) = 0 + 1 + 2 + 3 + 4 + ... = somatorio i de 0 ate n-1 = n(n-1)/2
    0.1 * [((n-1) * n)/2]
*/
void fun3_Slide1(int *n){
    int soma = 0;
    for(int i=1;i<=*n;i++)
	    for(int j=0;j<i;j++)
		    soma++;
}

int main(){

    return 0;
}