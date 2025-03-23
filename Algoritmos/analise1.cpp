
//Exemplo de analise de complexidade:
//Note que simplificamos ao máximo na notacao O (removendo o n, ja que O(n^2 +n) = O(n^2), pois a parte quadratica "pesa mais")
//Complexidade: O(n^2 + m + n) = O(n^2 + m)
void funcao1(int n, int m) {
	for(int i=0;i<n;i++) 
		for(int j=0;j<n;j++)
			ct *= j;
	
	for(int k=0;k<m;k++) 
		ct += 10;

	for(int k=0;k<n;k++) 
		ct += 10;
}	// N² + M


//	n² + m + n²  + n³ = O(n³ + m)
void funcao2(int n, int m) {
	for(int i=0;i<n;i++) 			//n²
		for(int j=0;j<n;j++)
			ct *= j;
	
	for(int k=0;k<m;k++) 		// n	
		funcao1(30,40);			// 30² + 40

	for(int k=0;k<n;k++) 		// n
		funcao1(n,200);			// n( n² + 200) = n³
}


// O (n * k + n/100000) = O(nk + n)
void funcao3(int n, int m, int k) {
	for(int i=0;i<n;i++) 		// n
		for(int j=0;j<k;j++)	// k
			ct *= m;			// 1

	for(int i=0;i<m/100000;i++) { // m/100000
		ct += k;				//1
	}
}

// O (N²) -> pior caso; O(1) -> melhor caso
void funcao4(int n, int m, int k, int v[]) {
	int ct = 0;
	for(int i=0;i<n;i++) {		//n
		if(v[i]%2==0) break;
		for(int j=0;j<n;j++) {	// n
			ct += v[i] + v[j];	// 1
		}
	}
}


//O(n)
void funcao5(int n, int m, int k, int v[]) {
	int ct = 0;
	for(int i=0;i<n;i++) {		//n
		for(int j=0;j<n;j++) {  //n
			ct++;
			if(ct%2==0) break;		//Essa condição breka na segunda execução, logo o for interno pode desconsiderar
		}
	}
}

// O(n²)
void funcao6(int n, int m, int k, int v[]) {
	int ct = 0;
	for(int i=0;i<n;i++) {			//n
		for(int j=0;j<n;j++) {		//n
			ct+= log(n);			//1
		}
	}
}

// 1 * n² = O(n²)
void funcao7(int n, int m, int k, int v[]) {
	int ct = 0;
	for(int i=1;i<n;i++) {			//1		
		for(int j=i;j<n;j++) {		// PA = O(n²)
			ct+= log(n);			//1
		}
	}
}

// n * Log m = O (n * log m)
void funcao8(int n, int m, int k, int v[]) {
	int ct = 0;
	for(int i=0;i<n;i++) {					//n
		for(int j=0;j<log(m);j++) {			//log m
			ct += sin(k);					//1
		}
	}
}

//Responda (alem de analisar a complexidade): o que essa funcao faz?
// Realiza a contagem dos digitos do valor n.

//1 + log(n) = O (log(n))
void funcao9(int n) {
	if(n==0) return 0;			//1
	return funcao9(n/10)+1;		// 
}


// O(log n + log m)
void funcao10(int n, int m, int k, int v[]) {
	if(n==0 && m==0) 
		return 1;
	if(n==0) 
		return funcao10(n,m/2,k,v);	//log n
	else 
		return funcao10(n/2,m,k,v); //log m
}


// Sendo s a soma dos elementos de v
// O(S + N)
void funcao11(int n, int m, int k, int v[]) {
	int ct = 0;
	for(int i=0;i<n;i++) {
		for(int j=0;j<v[i];j++) {
			ct += k;
		}
	}
}

//Para n significamente grande => O(n * n * 1) = O(n^2)
int funcao12(int n) {
    int ans = 0;
    for(int i=5;i<n;i++) 			//n-5 = O(n)
		for(int j=3;j<n;j++) 		//n-3 = O(n)
	          for(int k=1;k<n;k++) {	// n-1 = O(n) => quando brekado O(1)
	             ans += 2;
	             if(ans%10==0) break;	// faz a função interna rodar no maximo 5 vezes logo o for acimaeh O(1)
	          }
     return ans;
}

//O(u) * O(v) + O(f/2) * O(v/2) = O(uv + fv)
double funcao13(int v,int u, int f) {
	double ans = 0;
	for(int i=0;i<u;i++) {			//O(u)
	   for(int j=0;j<v;j++) 		//O(v)
	   		ans -= log(i*j);		//O(1)
	   ans += log(u+i);				
	   for(int j2=0;j2<f/2;j2++)	//O(f/2)
	   		for(int k=v/2;k<v;k++)		//O(v/2)
	   			ans += log(j2*k); 
	}
	return ans;
}


//Analise a complexidade de melhor e pior caso dessa função
//Diga não apenas a complexidade, mas também explique quando esses tempos ocorrem

//Resposta: A função é um algoritmo de busca, ele compara cada elemento do vetor com a chave
// passada como parametro.
// Melhor caso => chave encontrada no primeiro elemento do vetor => O(1)
// Pior caso => chave n encontrada no vetor/chave encontrada na ultima possicao do vetor => O(n)
void funcao14(int n, int m, int k, int v[]) {
	int ct = 0;
	for(int i=0;i<n;i++) {
		if(v[i]==m)
			return i;		
	}
	return -1;
}

//Analise a complexidade de melhor e pior caso dessa função
//Diga não apenas a complexidade, mas também explique quando esses tempos ocorrem

//Resposta: O algoritmo itera uma variavel em valores impares, brekando o ultimo laço quando divisivel por 10
// Como impares nao sao divisiveis por 10 a condicao de parada nao e atendida para w impar
// Melhor caso => w eh par O(n^2); Pior caso => w eh impar O(n^3)
int funcao15(int n, int w) {
    int ans = w;
    for(int i=5;i<n;i++) 			// O(n)
		for(int j=3;j<n;j++) 		// O(n)
	          for(int k=1;k<n;k++) {	// O(n)
	             ans += 2;
	             if(ans%10==0) break;
	          }
     return ans;
}

//O(n) * O(m) = O(nm)
int funcao16(int n, int w, int m) {
    double ans = w;
    for(int i=0;i<n;i++) 			//O(1) => O laco so eh executado 1 vez
    	for(int j=0;j<n;n--) 		//O(n)
    		for(int k=0;k<m;k++)	//O(m)
    			ans += 3.14;		//O(1)
    return ans;
}
