#include <list>
#include <iostream>
#include "MyHashMap.h"
using namespace std;

#include <string>
using namespace std;

class MyStringHash {
public:
	unsigned operator()(const string &s) const { //nesse exemplo, temos que hash(i) = i
		const unsigned base = 257;
		unsigned long long hash;
		
		for(int i =0; i<s.length(); i++){
			hash = hash* base + (unsigned char) i;
		}
		return static_cast<unsigned>(hash);
	}
};

class MySringHash2{
	public:
	unsigned char operator()(const string &s) const{
		return (int)s[0];
	}
};


//Exercicio: crie outras funcoes hash e teste-as!

int main() {
	MyHashMap<string,int,MyStringHash> map;
	map.set("Jose da Silva",1230);
	map.set("Joaquim",1391);
	map.set("Maria Silva",9211);
	map.set("Fernando Ferreira",79);
	map.set("Arthur Bernardes",98);
	map.set("Salles Magalhaes",96);
	map.set("Abc da Silva",6);
	map.set("Renata Gomes",22);
	map.set("Patricia Sousa",123);
	map.set("Ligia Soares",1234);
	map.imprime();

	std::cout<<'\n' << "MUDANDO O FUCNTOR: "<<std::endl;

	MyHashMap<string, int, MySringHash2> map2;
	map2.set("Jose da Silva",1230);
	map2.set("Joaquim",1391);
	map2.set("Maria Silva",9211);
	map2.set("Fernando Ferreira",79);
	map2.set("Arthur Bernardes",98);
	map2.set("Salles Magalhaes",96);
	map2.set("Abc da Silva",6);
	map2.set("Renata Gomes",22);
	map2.set("Patricia Sousa",123);
	map2.set("Ligia Soares",1234);
	map2.imprime();

}