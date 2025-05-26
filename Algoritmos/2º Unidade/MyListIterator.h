#include<iostream>

// declaration forward
template<class T> class Node;
template<class T> class MyList;
template<class T> class MyListIterator;

template<class T>
class Node{
private:
    T data;
    Node<T>*next;
    friend class MyList<T>;
    friend class MyListInterator;
public:
    Node<T>(const T& elem): data(elem), next(nullptr){}
};

template <class T>
class MyList{
private:
    Node<T>* head;
    Node<T>* tail;
    int dataSize = 0;

public:
    typedef MyListIterator<T> iterator;
    typedef MyListIterator<const T> const_iterator;

    // ---------------- Construtores e destrutor ---------
    /*ok */ MyList(T val);                           // construtor com valor inicial
    /*ok */ MyList();                                // construtor padrao
    /*ok */ ~MyList(){clear();}                      // destrutor
    /*ok */ void clear();                            // limpa a lista
    
    // ---------------- Inserir e Remover ----------------
    /*ok */ void push_back(const T& val);            // insere elemento no final
    /*ok */ void push_front(const T& val);           // insere elemento no início
    /*ok */ void pop_back();                         // remove elemento do final
    /*ok */ void insert(const T&, int pos);          // insere elemento em posição específica

    //  ---------------- Impressoes ---------------------
    /*ok */ void imprimir();                         // imprime lista iterativamente
    /*ok */ void imprimirRecursivo(Node<T>* ptr);    // imprime lista recursivamente (ajudante)
    /*ok */ void imprimirRecursivo();                // imprime lista recursivamente (público)
    /*ok */ void imprimirInverso(Node<T> *ptr);      // imprime inversamente (ajudante)
    /*ok */ void imprimirInverso();                  // imprime inversamente (público)

    // ---------------- Funcoes importantes --------------
    /*ok */ int size() const;                        // retorna o tamanho da lista
    /*ok */ bool empty();                            // verifica se a lista está vazia
    /*ok */ void copy(Node<T>* other);               // copia outra lista
    /*ok */ Node<T>* find(Node<T>*ptr, T val);       // busca valor recursivamente(ajudante)
    /*ok */ Node<T>* buscar(T val);                  // busca valor recursivamente(publico)

    // ----------------- Funcoes iterator ----------------
    iterator erase(iterator pos);
    /*ok */ iterator begin(){ return iterator(head); }
    /*ok */ iterator end(){ return iterator(nullptr); }

    /*ok */ const_iterator begin() const { return const_iterator(head); }
    /*ok */ const_iterator end() const { return const_iterator(nullptr); }
};

template <class T>
class MyListIterator{
private:
    Node<T>* current;
public:
    friend class MyList<T>;
    MyListIterator(Node<T>*ptr = nullptr): current(ptr){}

    T& operator*(){
        if(current == nullptr) throw std::runtime_error("Erro: tentativa de derreferenciar um iterator nulo.");
        else{
            return current->data;
        }
    }
    T& operator->(){
        if(current == nullptr) throw std::runtime_error("Erro: tentativa de acessar membro de um iterator nulo.");
        return &(current->data);
    }

    //pre incremento
    MyListIterator operator++(){
        if(current) current = current->next; 
        return *this;
    }

    //pos incremento
    MyListIterator operator++(int){
        MyListIterator temp = *this;
        ++(*this);
        return temp;
    }
    
    bool operator==(const MyListIterator& other) const{
        return current == other.current;
    }
    
    bool operator!= (const MyListIterator& other) const{
        return !(current == other.current);
    }

};
// ---------------- Construtores e destrutor ----------------
template<class T>
MyList<T>::MyList() {
    head = nullptr;
    tail = nullptr;
    dataSize = 0;
}

template <class T>
MyList<T>::MyList(T val){
    Node<T>*ptr = new Node<T>(val);      //isso aqui eh a criacao padrao
    ptr->data = val;
    ptr->next = nullptr;
    head = ptr;
    tail = ptr;
    dataSize++;
}

template<class T>
void MyList<T>::clear(){
   Node* current = head;
   while(current){
        Node *toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = nullptr; dataSize = 0;
}

// ---------------- Inserir e Remover ----------------
template <class T>
void MyList<T>::push_back(const T& val){
    Node<T>* newNode = new Node<T>(val);
    if(empty()) head = tail = newNode;
    else{
       tail->next = newNode;
       tail = newNode; 
    }
    dataSize++;
}

template<class T>
void MyList<T>::push_front(const T& val){
    Node<T>*newNode = new Node<T>(val);
    
    if(empty()) head =tail = newNode;
    else {   
        newNode->next = head;
        head = newNode;
    } dataSize++;
}

template <class T>
void MyList<T>::pop_back(){
    if(empty()) return;
    if (head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else{
        Node<T> *current = head;
        while(current->next != tail){
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    dataSize--;
}

template<class T>
void MyList<T>::insert(const T& val, int pos){
    if(pos < 0 || pos > dataSize){
        std::cout << "Posicao invalida." << std::endl; 
        return;
    }
    else if(pos == 0){
        push_front(val);
    }
    else if(pos == dataSize){
        push_back(val);
    }
    else{
        Node<T>* newNode = new Node<T>(val);
        Node<T>* aux = head;

        for(int i = 0; i < pos-1; i++){
            aux = aux->next;
        }
        newNode->next = aux->next;
        aux->next = newNode;
        dataSize++;
    }
}

//  ---------------- Impressoes ----------------
template<class T>
void MyList<T>::imprimir(){
    if(empty()) return;

    Node<T>* current = head;
    while(current != nullptr){
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <class T>
void MyList<T>::imprimirRecursivo(Node<T>* ptr){
    if (!ptr) return;       //!ptr é igual a ptr == nullptr, mesma verificação
    std::cout << ptr->data << " ";
    imprimirRecursivo(ptr->next);
}

template <class T>
void MyList<T>::imprimirRecursivo(){
    imprimirRecursivo(head);
}

template <class T>
void MyList<T>::imprimirInverso(Node<T>*ptr){
    if(empty()) return;

    imprimirInverso(ptr->next);
    std::cout<< ptr->data << " ";
}

template <class T>  
void MyList<T>::imprimirInverso(){
    imprimirInverso(head);
}

// ---------------- Funcoes importantes ----------------
template<class T>
int MyList<T>::size() const{
    return dataSize;
}

template <class T>
bool MyList<T>::empty(){
  return head == nullptr;
}

template<class T>
void MyList<T>::copy(Node<T>* other){
    clear();
    if (!other) return;

    while(other){
        push_back(other->data);
        other = other->next;
    }
}

template <class T>
Node<T>* MyList<T>::find(Node<T>*ptr, T elem){
    if (!ptr) return nullptr;

    if(ptr->data == elem) return ptr;
    return find(ptr->next, elem);
}

template <class T>
Node<T>* MyList<T>::buscar(T val) {
    return find(head, val);
}

template<class T>
typename MyList<T>::iterator MyList<T>::erase(iterator pos){
    if(pos->current == nullptr) 
        throw std::invalid_argument("O valor inserido nao pertence a lista.");

    //nao eh necessario implementar caso a lista seja vazia -> culpa do usuario
    if(pos == begin()){
        Node<T>*nodeNext = head->next;
        delete head;
        head = nodeNext;
        dataSize--;

        if(head == nullptr) 
            tail =nullptr;
        return iterator(head);
    }

    Node<T>* prev = head;
    while(prev != nullptr && prev->next != pos.current) {
        prev = prev->next;
    }
  
    if(prev == nullptr || prev->next != pos.current) throw std::invalid_argument("Iterator não pertence a esta lista");

    Node<T>* nextNode = pos.current->next;

    if(pos->current == tail){
        tail = prev;
    }
    prev->next = nextNode;

    delete pos->current;
    dataSize--;

    return iterator(nextNode);
}

