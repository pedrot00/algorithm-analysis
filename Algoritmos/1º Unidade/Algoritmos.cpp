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

/* T(n) = Top * C(n)
   C(n) = 0 + 1 + 2 + 3 + 4 + ... = somatorio i de 0 ate n-1 = n(n-1)/2 = (n^2 - n)/2 = n^2 para valores grandes
    T.op* [((n-1) * n)/2]
*/
void fun3_Slide1(int *n){
    int soma = 0;

    for(int i=1;i<=*n;i++)          // para os dois for = n(n-1)/2 
	    for(int j=0;j<i;j++)
		    soma++;                 // ??? o tempo depende do compilador
}

// O(n-1) = O(n)
int maxElement(int v[],int n) {     //fun1_slide2
	int mx = v[0];
	for(int i=1;i<n;i++)        //executa n-1 vezes
		if (v[i] > mx)          //execua n-1 vezes -> op. basica comparacao
			mx = v[i];          //execua somente quando v[i] > mx
	return mx;
}

//O(n)
// pior caso => a chave nao esta no vetor ou a chave esta no ultimo elemento => O(n)
// caso medio => a chave esta no vetor, nem no primeiro nem no ultimo => O(n)
// caso otimo => a chave esta no primeiro elemento do vetor, 1 interacao => O(1)
int find(int v[],int n,int elem) {  //fun2_slide2
	for(int i=0;i<n;i++)            //Executa n vezes O(n)
		if (v[i] == elem)           //Executa n vezes -> op. basica comparacao
			return i;
	return -1; 
}

// o nivel de complexidade de um while depende da sua condicao de parada tambem
// a funcao calcula o numero de digitos, o contador aumenta para cada divisao inteira por 10, quando 0<n<1 ele para
// O (log(n) + 1) = O (log (n))
int numDigitos(int n) { //suponha que n>0       //fun3_slide2
	int ct  = 0;
	while( n != 0) {                         
		n/=10;
		ct++;          //O(1)
	}
	return ct;
}

//tam entrada = v[0] pois n eh irrelevante para o algoritmo e so eh utilizado o primeiro elemento do vetor
//op.basica = divisao
//O(log(v[0]))
int numDigitosPrimElemento(int v[], int n) {  ///func4_slide_2
	int x = v[0];       //unico elemento utilizado dos parametros              
	int ct  = 0;

	while( x != 0) {   //executa v[0]/10 != 0 vezes 
		x/=10;          //op.basica
		ct++;
	}
	return ct;
}

//O(n^3)
int matrixMult(int **a, int **b, int **c, int n) { //suponha que n>0  ///func5_slide_2
	for(int i=0;i<n;i++)                //O(n)
		for(int j=0;j<n;j++) {          //O(n)
			int resp = 0;               //O(1)
			for(int k=0;k<n;k++)            //O(n)    
				resp += a[i][k]*b[k][j];    //op.basica => esta no loop mais interno
			c[i][j] = resp;                 
		}
}

//--------------------------  ///func6_slide_2
//O(n)
int find(int v[],int n,int elem) {
	for(int i=0;i<n;i++)        //O(n)
		if (v[i] == elem)       //op.basica comparacao
			return i;
	return -1; 
}

//O(m * n) = O(mn)
int f(int n, int m) {
         int v[n] = {2, 4 };
         int consultas[m] = {2, 4};
	for(int i=0;i<m;i++)                //O(m)
        cout << find(v,n, consultas[i]);    //saida tem complexidade O(1), find = 0(n)
}
//-------------------------- // fim func6_slide_2

//-------------------------- // fun1_slide3
 //O(n)
int busca(int v[],int n, int k) {
	for(int i=0;i<n;i++)           
		if(v[i]==k) return i;
	return -1;
}

//O(n^2)
int funcao2(int v[],int n) {       
	int ct = 0;
	for(int i=0;i<n;i++)            //O(n)
		for(int j=0;j<n;j++)        //O(n)
			ct+=v[j];               //O(1)
	return ct;
}

// O(n) + O(n^2) + O(m)= O(n^2 + m)
int f() {
	int v[] = {2,3,4,5}, n, k, m;
	busca(v,n,k);       //O(n)
	funcao2(v,n);       //O(n^2)
    busca(v,m,k);      //O(m)  
}
//--------------------------

//-------------------------- // fun2_slide3
int busca2(int v[],int n, int k) {   //O(n)
	for(int i=0;i<n;i++)           
		if(v[i]==k) return i;
	return -1;
}

 //O(m)
int f2() {
	int v[] = {2,3,4,5}, n, k, m;
	cin >> m;
	busca(v,m,k);   
}
//--------------------------

//--------------------------    // fun3_slide3
int busca3(int v[],int n, int k) {   //O(n)
	for(int i=0;i<n;i++) 
		if(v[i]==k) return i;
	return -1;
}

//O(n *m^2)
int f3() {
    int ans;                
    int v[] = {2,3,4,5}, n, k, m;
	for(int i=0;i<n;i++)     //O(n)
		for(int j=0;j<m;j++)     //O(m)
			ans += busca(v,m,k);    //O(m) //op.basica
}

//--------------------------    // fun4_slide3
//O(n)
int busca4(int v[],int n, int k) {
	for(int i=0;i<n;i++)             //O(n)
		if(v[i]==k) return i;
	return -1;
}

//O(n^2)
int funcao3(int v[],int n) {
    
	int ct = 0;
	for(int i=0;i<n;i++)        //O(n)
		for(int j=0;j<n;j++)      //O(n)
			ct+=v[j];
	return ct;
}

//O(n) * O(m * m) + O(n* n^2) = O(nm^2 + n^3)
//pior caso => O(n^3)
int f4() {
    int v[] = {2,3,4,5}, n, k, m;
    int ans=0;
	for(int i=0;i<n;i++) {      //O(n)
		for(int j=0;j<m;j++)    //O(m)  
			ans += busca(v,m,k);     //O(m)  
	funcao2(v,n);                    //O(n^2)  
} 
}
//--------------------------    // fun5_slide3          // REVISAR!!
//O(n) * O(n -i-1) = O(n^2)
bool todosIguais(int v[], int n) {
	for(int i=0;i<n;i++)        //0(n)
		for(int j=i+1;j<n;j++)  //O(n-i-1)
			if(v[i]==v[j]) return false;
	return true;
}
//--------------------------     // fun6_slide3  
//O(n^3)
int matrixMult(int **a, int **b, int **c, int n) { //suponha que n>0
	for(int i=0;i<n;i++)            //O(n)
		for(int j=0;j<n;j++) {      //O(n)
			int resp = 0;
			for(int k=0;k<n;k++)    //O(n)
				resp += a[i][k]*b[k][j];        //O(1)
			c[i][j] = resp;         //O(1)
		}
}

//--------------------------     // fun7_slide3  
//O(n/2) * O(n/2) * O(1) = O(n^2)
double f(int n) {
    double  x = 0;
    for(int i=0;i<n/2;i++)      //O(n/2)
       for(int j= n/2; j>=0;j--)     //O(n/2)
            x+= log(2*i*j);           //O(1)
        return x;
}

//--------------------------     // fun8_slide3  
// O(n) * O(n) + O(n/2) *O(n/2) = O(n^2) + O(n^2/4) = O(n^2)
double f(int n) {
	double ans = 0;
	for(int i=0;i<n;i++) {      //O(n)
		for(int j=0;j<n;j++)    //O(n)
			ans -= log(i*j);       //O(1)
		ans += log(n+i);             //O(1)
		for(int j2=0;j2<n/2;j2++)   //O(n/2)
			for(int k=0;k<n/2;k++)  //O(n/2)
				ans += log(j2*k);   //O(1)
	}
	return ans;
} 
//--------------------------     // fun9_slide3  
//O(n^2) + O(n^2/4) = O(n^2)
double f(int n) {
	double ans = 0;
	for(int i=0;i<n;i++) {          //O(n)
		for(int j=0;j<n;j++)        //O(n)
			ans -= log(i*j);
		ans += log(n+i);
		for(int j2=0;j2<n/2;j2++)      //O(n/2)
			for(int k=n/2;k<n;k++)      //O(n - n/2) = O(n/2)
				ans += log(j2*k); 
	}
	return ans;
} 
//--------------------------


int main(){

    return 0;
}