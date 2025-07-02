#include <list>
#include <iostream>
#include "MyHashMap.h"
using namespace std;

#include <string>
using namespace std;

//functor que calcula o hash de uma string
class MyStringHash1 {
public:
	unsigned operator()(const string &s) const { //nesse exemplo, o hash sera o codigo ASCII do primeiro caractere da string
		return (int)s[0];
	}
};

class MyStringHash2 {
public:
	unsigned operator()(const string &s) const { // Hash ruim: soma simples dos códigos ASCII
		unsigned hash = 0;
		for (char c : s) {
			hash += (unsigned)c;
		}
		return hash;
	}
};

class MyStringHash3 {
public:
	unsigned operator()(const string &s) const { // Hash bom: algoritmo djb2
		unsigned hash = 5381;
		for (char c : s) {
			hash = ((hash << 5) + hash) + (unsigned)c;
		}
		return hash;
	}
};

class MyStringHash4 {
public:
	unsigned operator()(const string &s) const { // Hash ruim: apenas o comprimento da string
		return s.length();
	}
};

class MyStringHash5 {
public:
	unsigned operator()(const string &s) const { // Hash bom: FNV-1a hash
		unsigned hash = 2166136261u;
		for (char c : s) {
			hash ^= (unsigned)c;
			hash *= 16777619u;
		}
		return hash;
	}
};




//conta a frequencia de cada string (usando uma tabela hash) no vetor chaves..
//entao, imprime o tamanho dos baldes na tabela hash.
template<class HashFunctor>
void testaHash(const MyVec<string> &chaves) {
	MyHashMap<string,int,HashFunctor > map;

	int sz = chaves.size();
	for(int i=0;i<sz;i++) {  //vamos contar a frequencia de cada chave...
		if(map.count(chaves[i])==0)
			map.set(chaves[i],1);
		else 
			map.set(chaves[i],map.getValue(chaves[i])+1);
	}
	map.imprimeTamanhoBaldes();
}




//Exercicio: crie outras funcoes hash e teste-as!
int main(int argc, char **argv) {
	MyVec<string> chaves;
	string st;
	while(cin >> st) {
		chaves.push_back(st);
	}

	int qualFunctorUsar = atoi(argv[1]);
	switch(qualFunctorUsar) {
		case 1:
			cout << "Testando com o functor 1 (usando o codigo ASCII do primeiro caractere de cada string como hash)" << endl;
			testaHash<MyStringHash1>(chaves); //realiza o teste usando o functor MyStringHash1
			break;
		case 2:
			cout << "Testando com o functor 2 (soma dos códigos ASCII - hash ruim)" << endl;
			testaHash<MyStringHash2>(chaves);
			break;
	case 3:
		cout << "Testando com o functor 3 (algoritmo djb2 - hash bom)" << endl;
		testaHash<MyStringHash3>(chaves);
		break;
	case 4:
		cout << "Testando com o functor 4 (comprimento da string - hash muito ruim)" << endl;
		testaHash<MyStringHash4>(chaves);
		break;
	case 5:
		cout << "Testando com o functor 5 (FNV-1a hash - hash bom)" << endl;
		testaHash<MyStringHash5>(chaves);
		break;

	return 0;
}