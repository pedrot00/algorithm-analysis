#include <iostream>
#include "MySet.h"

using namespace std;

void procura(MySet<int> &s, int elem) {
	cout << "Procurando " << elem << " : " << (s.find(elem)!=s.end()) << endl;
}

void insere(MySet<int> &s, int elem) {
	cout << "Inserindo " << elem << " : " << (s.insert(elem).second) << endl;
}

template<class T>
bool comparaArvore(const MySet<T>& tree1, const MySet<T>& tree2){
	if(tree1.size() !=tree2.size()) 
		return false;
	typename MySet<T>::iterator it1 = tree1.begin();
	typename MySet<T>::iterator it2 = tree2.begin();

	for(; it1!=tree1.end() && it2 != tree2.end(); it1++, it2++){
		if(*it1 != *it2) return false;
	}
	return it1 == tree1.end() && it2 == tree2.end();

}


int main() {
	MySet<int> s;
	insere(s,1);
	insere(s,2);
	insere(s,10);
	insere(s,10); //repetidos..
	insere(s,10); //repetidos..
	insere(s,1);

	s.imprimeBFS();
	cout << endl;

	//qual sera o formato dessa arvore?
	//desenhe-a!
	MySet<char> s2;
	s2.insert('k');
	s2.insert('d');
	s2.insert('s');
	s2.insert('a');
	s2.insert('m');
	s2.insert('w');
	s2.insert('b');
	s2.insert('z');
	s2.insert('t');
	s2.insert('r');
	s2.insert('c');

	cerr << "DFS in ordem: " << endl;
	s2.imprimeDFS_in();
	cerr << endl;

	cerr << "Usando iteradores: " << endl;	
	for(MySet<char>::iterator it = s2.begin();it!=s2.end();it++) {
		cerr << *it << " ";
	} cerr << endl;

	cerr << "De tras para a frente..." << endl;
	//por enquanto nao suportamos decremento de end()
	MySet<char>::iterator it = s2.begin();
	for(;*it!='z';it++);
	//coincidenetemente, ao decrementar um iterador para o ultimo elemento
	//chegamos a um iterador para end() (pode ser que seja melhor mudar isso...)
	for(;it!=s2.end();it--) cerr << *it << " ";
	cerr << endl;

	cerr << "Usando range-based for: " << endl;
	for(auto x:s2) {cerr << x << " ";
	} cerr << endl;


}