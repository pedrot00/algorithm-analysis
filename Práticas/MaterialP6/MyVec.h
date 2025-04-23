/*
TAD MyVec
- Representa uma lista implementada por contiguidade
- Interface similar a da classe Vector do STL
- Criado por Salles Magalhaes em 19/02/2018

*/

#ifndef MyVec_H__
#define MyVec_H__

#include <iostream>
#include <string>
#include <ostream>


//Excessao usada pela classe MyVec
class MyVecException {
private:
	std::string msg;
public:
	MyVecException (const std::string &msg0): msg(msg0) { }
	const std::string & what() const { return msg; }
};


template<class T>
class MyVec {
public:
	template<class T2>
	friend std::ostream& operator<<(std::ostream &, const MyVec<T2> &);

	//construtores/destrutures/etc
	MyVec();
	MyVec(int n, const T&init=T());

	//destrutor
	~MyVec() { destroy(); };

	//Construtor de copia
	MyVec(const MyVec &);
	MyVec & operator=(const MyVec &);

	//funcoes de acesso
	T &operator[](int pos) {return data[pos];}
	const T &operator[](int pos) const {return data[pos];}
	void push_back(const T&);
	void resize(int newSize);
	void insert(const T&,int pos);
	void clear();

	bool empty() const {return size() == 0;};
	int size() const {return dataSize;};
	int eraseMatchingElements(const T& elem);
	void sortedInsert(const T& elem);


private:
	T* data; //declare o membro de dados data, que devera armazenar os elementos da lista
	int dataSize; //quantos elementos ha na lista?
	int dataCapacity; //quantos elementos atualmente cabem na lista? 

	void create();
	void destroy();
	void resizeCapacity(int newCapacity);
	
};

template<class T>
void MyVec<T>::push_back(const T&elem) {
	if (dataSize == dataCapacity){
		if(dataSize == 0){
			resizeCapacity(1);
		}
		else{
			resizeCapacity(2*dataCapacity);
		}
	}
	data[dataSize++] = elem;
}

template<class T>
void MyVec<T>::resize(int newSize) {
	if(newSize >= dataCapacity) { //primeiro temos que realocar o vector...
		resizeCapacity(newSize); //para o resize vamos usar o tamanho exato caso seja necessario realocar o vector..
	}
	for(int i=dataSize;i<newSize;i++) { //preencha a parte "extra" do vector com valores "em branco"
		data[i] = T();
	}
	dataSize = newSize;
}

//insere o elemento na posicao pos e move os elementos ja presentes no vetor
// pos pode ser:
//   uma posicao apos o final do vetor (para inserir na ultima posicao) 
//   ou uma posicao ja existente (nesse caso os elementos nessa posicao e apos ela serao movidos "para a frente")
template<class T>
void MyVec<T>::insert(const T&elem,int pos) {
	if(pos > dataSize || pos < 0) {
		throw MyVecException("Erro na funcao insert: posicao invalida");
	}

	if(dataSize == dataCapacity) { //preciso redimensionar? Somente se dataCapacity for igual ao dataSize
		if(dataCapacity ==0) //Exercicio: Por que e' preciso testar isso?
		//se o dataCapacity for igual a dataSize e n redimensionar o for acessa posição que nao 
		//existe pra alocacao, perderiamos o ultimo elemento
			resizeCapacity(1);
		else
			resizeCapacity(dataCapacity*2);
	}	

	for(int i=dataSize;i>pos;i--)
		data[i] = data[i-1];
	data[pos] = elem;
	dataSize++;
}

template<class T>
void MyVec<T>::clear() {
	destroy();
	create();
}

template<class T>
void MyVec<T>::resizeCapacity(int newCapacity) {
	if(newCapacity <= dataCapacity){return;}
	dataCapacity = newCapacity;

	T* newData = new T[dataCapacity];
	
	for(int i = 0; i<dataSize; i++){
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	//delete[] new data -> talvez precise fazer isso
}

template<class T>
void MyVec<T>::destroy() {
	delete []data;
	dataSize = dataCapacity = 0;
}


template<class T>
void MyVec<T>::create() {
	data = NULL;
	dataSize = dataCapacity = 0;
}

template<class T>
MyVec<T>::MyVec() {
	create();
}

template<class T>
MyVec<T>::MyVec(int n, const T&init) {
	//Implemente esta funcao:
	//Cria um vetor de tamanho e capacidade n, onde todos os n elementos valem "init"
	create();
	data = new T[n];
	dataCapacity = dataSize = n; // dataSize igual a n pq o vetor vai estar todo preenchido com init
	for (int i = 0; i<n; i++){
		data[i] = init;
	}
}

//Construtor por copia
template<class T>
MyVec<T>::MyVec(const MyVec &other) {
	create();
	resizeCapacity(other.dataCapacity); // seta a capacidade como a capacidade do passado como a do vetor passado por parametro
	for(int i = 0; i<other.dataSize; i++){
		push_back(other.data[i]); // push elementos de other no novo vetor
	}
	
}	

template<class T>
MyVec<T> & MyVec<T>::operator=(const MyVec &other) {
	if(this==&other) return *this; 
	destroy(); //Exercicio: por que precisamos disso?
	dataCapacity = other.dataCapacity;
	dataSize = other.dataSize;
	//data = other.data; //por que nao podemos fazer isso? 
	//resposta: pq sao ponteiros, o data so iria apontar para o mesmo primeiro elemento do other
	data = new T[dataCapacity];
	for(int i=0;i<dataSize;i++) data[i] = other.data[i];
	return *this;
}

template<class T2>
std::ostream& operator<<(std::ostream &out, const MyVec<T2> &v) {
	out << "Size: " << v.size() << "\n";
	out << "Capacity: " << v.dataCapacity << "\n";
	for(int i=0;i<v.size();i++) out << v.data[i] << " ";
	out << "\n";
	return out;
}

/*
Adicione uma função chamada eraseMatchingElements à sua classe 
(essa função não está disponível nos vetores disponibilizados pela STL). 

Tal função deverá receber um argumento e remover do vetor todos os elementos 
iguais a esse argumento.

- O argumento deverá ser passado por referência constante 
  (para evitar cópia desnecessária e garantir que o valor não seja alterado).
  
- A função NÃO deve ser constante, pois ela modifica o conteúdo do vetor.

Ao final, deve-se retornar quantos elementos foram removidos.

Importante: a capacidade do vetor (dataCapacity) não deve ser alterada.

Sua implementação deverá ser o mais eficiente possível.
*/

template<class T>
int MyVec<T>::eraseMatchingElements(const T& elem) {
	int removedCont = 0;
	int tamanho = 0;

	// se o elemento n for igual ao passado por parametro ele escreve data[0] = data[i]
	//aumentando o valor de 0, no final esse valor tamanho sera nosso novo tamanho do vetor
	//a capacidade mantem a mesma n precisa realocar
	for(int i=0; i<dataSize; i++){
		if(data[i]!=elem){
			data[tamanho++] = data[i];
		}
		else{
			removedCont++;
		}
	}
	dataSize = tamanho;
	return removedCont;
}

template <class T>
void MyVec<T>::sortedInsert(const T& elem){
	if(dataSize == 0){	//p caso o vetor esteja vazio // deveria ser dataSize ou dataCapacity?
		resizeCapacity(1);	
	}
	else if(dataSize == dataCapacity){	//p caso o vetor esteja cheio
		resizeCapacity(dataCapacity*2);
	}

	// p acharmos a posicao onde inserir o elemento de forma mais eficiente
	int beg = 0, end = dataSize;
	while(beg < end){
		int meio = beg + (end - beg)/2 ;
		if(data[meio] < elem){
			beg = meio + 1;
		}
		else{
			end = meio;
		}
	}
	for(int i=dataSize-1; i>=beg; i--){
		data[i+1] = data[i];
	}
	data[beg] = elem;
	dataSize++;
}
#endif
