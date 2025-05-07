/*
TAD MyList
- Representa uma lista implementada por encadeamento simples
- Criado por Salles Magalhaes em 19/02/2018

*/

#ifndef MyList_H__
#define MyList_H__

#include <iostream>
#include <string>
#include <ostream>


//Excessao usada pela classe MyList
class MyListException {
private:
	std::string msg;
public:
	MyListException (const std::string &msg0): msg(msg0) { }
	const std::string & what() const { return msg; }
};



template<class T>
class Node;

template<class T>
class Node { //a classe Node sera "escondida" quando trabalharmos com iteradores
	public: //classe basicamente utilizada apenas aqui...
					//usada apenas para armazenar dados --> ok deixar tudo public

		Node(const T&elem): data(elem), next(NULL) {}
		T data;
		Node<T> *next;
};

template<class T>
class MyListIterator; //precisamos declarar essa classe antes da MyList para que o typedef abaixo nao de erro
		      //por outro lado, so podemos implementar o iterador apos a classe MyList (visto que precisaremos acessar
		      //dados da classe)


template<class T>
class MyList {
public:
	//decidimos utilizar o typedef com o objetivo de "abstrair" o conceito de iterador (a utilidade disso sera vista posteriormente)
	typedef MyListIterator<T> iterator; //define um iterador, um tipo utilizado para percorrer uma estrutura de dados e "apontar" para os items armazenados nela


	template<class T2>
	friend std::ostream& operator<<(std::ostream &, const MyList<T2> &);

	//construtores/destrutures/etc
	MyList();
	MyList(int n, const T&init=T());

	//destrutor
	~MyList() { destroy(); };

	//Construtor de copia
	MyList(const MyList &);
	MyList & operator=(const MyList &);

	//funcoes de acesso
	void push_back(const T&);
	void push_front(const T&);
	void insert(const T&,iterator nodeBefore); //insere o primeiro argumento APOS o nodo apontado pelo segundo elemento
																					//isso sera melhorado no futuro (quando estudarmos iteradores)
	iterator erase(iterator elem); //remove o elemento apontado por Elem
														//retorna o (apontador) para o elemento apos o removido

	iterator begin() {return iterator(dataFirst);} //Exercicio: e se tivermos uma lista constante, como itera-la para, por exemplo, imprimir os elementos?
	iterator end() {return iterator(NULL);} //retorna um apontador para um nodo que estaria APOS o final da lista
	

	void clear();

	//Exercicio: implementar as duas funcoes abaixo supondo que nao ha um membro de dados dataSize (o calculo do tamanho da lista seria dinamico)
	bool empty() const {return size() == 0;};
	int size() const {return dataSize;}; // na STL List, a funcao size() calcula o tamanho da lista dinamicamente (exercicio: qual a ordem de complexidade?)
	void reverse();
	void reverse(Node<T>*current, Node<T> *prev, Node<T>*&newHead);
	int eraseMatchingElements(const T& value);
private:
	Node<T> *dataFirst, * dataLast;
	int dataSize; //quantos elementos ha na lista?

	void create();
	void destroy();
	void destroy(Node<T> *ptr);
};

/*
template<class T>
void MyList<T>::destroy(Node<T> *ptr) { 
	if(!ptr) return;
	destroy(ptr->next);
	delete ptr;
}

template <class T>
void MyList<T>::destroy(){
	destroy(dataFirst);
	dataSize = 0;
	dataFirst = dataSize = nullptr;
}
*/

template <class T>
void MyList<T>::destroy(){
	Node<T> * current = dataFirst;
	
	while(!current->next){
		Node<T> *aux = current->next;
		delete current;
		current = aux;
	}
	dataSize = 0;
	dataFirst = dataLast = 0;

}


template<class T>
void MyList<T>::create() {
	dataFirst = dataLast = nullptr;
	dataSize = 0;
}

template<class T>
void MyList<T>::push_front(const T&elem) {
	Node<T> *newNode = new Node<T>(elem);

	if(empty()){
		dataLast = dataFirst = newNode;
	}
	else{
		newNode->next = dataFirst;
		dataFirst = newNode;
	}
	dataSize++;
}

template <class T>
void MyList<T>::reverse(Node<T>* current, Node<T>* prev, Node<T>*& newHead) {
    if (current == nullptr) {
        newHead = prev; 
        return;
    }
    Node<T>* next = current->next;
    current->next = prev;          
    
    reverse(next, current, newHead);
}

template <class T>
void MyList<T>::reverse(){
	if(empty() || !dataFirst->next) return;
	reverse(dataFirst, nullptr, dataFirst);
}

template <class T>
int MyList<T>::eraseMatchingElements(const T& value) {
    int count = 0;
    Node<T>* current = dataFirst;
    Node<T>* prev = nullptr;

    while (current != nullptr) {
        if (current->data == value) {
            Node<T>* temp = current;
            
            if (prev == nullptr) {
                // Caso 1: Remoção do primeiro nó (dataFirst)
                dataFirst = current->next;
                current = dataFirst; // Atualiza current para o novo primeiro nó
            } else {
                // Caso 2: Remoção de um nó no meio/fim
                prev->next = current->next;
                current = current->next;
            }

            delete temp;
            count++;
            if (dataSize > 0) dataSize--; // Atualiza o tamanho, se dataSize existir
        } else {
            // Avança para o próximo nó (sem remoção)
            prev = current;
            current = current->next;
        }
    }

    // Atualiza dataLast se o último nó foi removido
    if (dataLast != nullptr && dataLast->data == value) {
        dataLast = prev; // prev agora é o novo último nó
    }

    return count;
}

template<class T>
class MyListIterator {
	friend class MyList<T>;
public:
	MyListIterator(Node<T> *ptr_): ptr(ptr_) {}
	T &operator*() {return ptr->data;}
	const T &operator*() const {return ptr->data;} //versao constante do operador de derreferencia

	bool operator==(const MyListIterator &other) const {return ptr==other.ptr;}
	bool operator!=(const MyListIterator &other) const {return ptr!=other.ptr;}

	//exercicio: faz sentido ter operatores <, > , <=, etc?
	//           faz sentido termos operadores +, =+ (para "pularmos" n elementos em vez de 
	//                                                avancarmos de um em um) , etc?

	//exercicio: armazenamos um ponteiro nesta classe. Deveriamos ter destrutor, constr. de copia, etc?

	//pre incremento
	MyListIterator<T> operator++();

	//pos incremento
	//o argumento (int) eh uma convencao do C++ usada para diferenciar a implementacao
	// do operador de pos e pre incremento
	MyListIterator<T> operator++(int);

private:
	Node<T> *ptr;
};


//pre incremento/decremento
template<class T>
MyListIterator<T> MyListIterator<T>::operator++() {
	ptr = ptr->next;
	return *this;
}


//pos incremento/decremento
//o argumento (int) eh uma convencao do C++ usada para diferenciar a implementacao
// do operador de pos e pre incremento
template<class T>
MyListIterator<T> MyListIterator<T>::operator++(int) {
	MyListIterator<T> oldIt= *this;
	ptr = ptr->next;
	return oldIt;
}

template<class T>
MyList<T>::MyList() {
	create();
}

template<class T>
MyList<T>::MyList(int n, const T&init) {
	create();
	for(int i=0;i<n;i++) push_back(init); //implementacao pode ser mais eficiente se evitar atualizar o apontador "dataLast" em cada iteracao
}


//Construtor de copia
template<class T>
MyList<T>::MyList(const MyList &other) {
	create(); //Crie um vetor vazio
	*this = other; 
}

template<class T>
MyList<T> & MyList<T>::operator=(const MyList &other) {
	if(this==&other) return *this; 
	clear(); //Exercicio: por que precisamos disso?

	if(other.dataFirst == NULL) {
		dataFirst = dataLast = NULL;
	} else {
		Node<T> *curr = other.dataFirst;
		while(curr!=NULL) { //equivalente a "while(curr)"
			push_back(curr->data);
			curr = curr->next; //avance para o proximo nodo
		}
	}
	return *this;
}


//---------------------------------------------------------------------------------------
//Funcoes de acesso

template<class T>
void MyList<T>::push_back(const T&elem) {
	if(dataFirst==NULL) { //caso especial: lista inicialmente vazia
		dataFirst = dataLast = new Node<T>(elem);
	} else {
		dataLast->next = new Node<T>(elem);
		dataLast = dataLast->next;
	}
	dataSize++;
}



//insere o elemento na posicao APOS a posicao nodeBefore
template<class T>
void MyList<T>::insert(const T&elem, iterator nodeBefore) {
	Node<T> * nodeBeforePtr = nodeBefore.ptr;

	if(nodeBefore == NULL) {
		throw MyListException("Erro, insercao em posicao invalida da lista");
	}

	Node<T> *newNode = new Node<T>(elem);
	newNode->next = nodeBeforePtr->next;
	nodeBeforePtr->next = newNode;

	if(nodeBeforePtr == dataLast) { //caso especial
		dataLast = newNode;
	}
	dataSize++;
}


template<class T>
void MyList<T>::clear() {
	destroy();
	create();
}

//assumimos que elem seja um ponteiro valido para um nodo da lista
template<class T>
typename MyList<T>::iterator MyList<T>::erase(iterator elem) { //remove o elemento apontado por Elem
	Node<T> *elemPtr = elem.ptr;
												       //retorna o (apontador) para o elemento apos o removido
	dataSize--;
	if(elemPtr==dataFirst && elemPtr==dataLast) { //exercicio: por que precisamos desse caso especial?
		//so ha um elemento na lista
		delete elemPtr;
		dataFirst = dataLast = NULL;
		return NULL;
	} else if(elemPtr==dataFirst) {		
		dataFirst = dataFirst->next;
		delete elemPtr;
		return dataFirst;
	} else {
		//o elemento a ser removido nao e' o primeiro.
		Node<T>* beforeElem = dataFirst;
		Node<T>* curr = dataFirst->next;

		while(curr != elemPtr) {
			beforeElem = curr;
			curr = curr->next;
		}

		//agora curr aponta para elem e beforeElem aponta para um elemento antes de curr
		beforeElem->next = curr->next; 
		delete curr;
		if(curr==dataLast) {
			dataLast = beforeElem;
		}
		return beforeElem->next;
	}
}



template<class T2>
std::ostream& operator<<(std::ostream &out, const MyList<T2> &v) {
	out << "Size: " << v.size() << "\n";
	/* //usando iteradores para abstrairem a iteracao
	MyList<T2>::iterator it = v.begin();
	while(it!=v.end()) {
		 out << *it << " ";
		 it++
	}
	*/
	Node<T2> *curr = v.dataFirst;
	while(curr!=NULL) { // equivalente a while(curr)
		 out << curr->data << " ";
		 curr = curr->next;
	}

	out << "\n";

	return out;
}


#endif
