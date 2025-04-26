#include<iostream>

template <class T>
struct Node{
    T data;
    Node *next;
    Node(T val) : data(val), next(nullptr) {} //construtor ja com o valor data
};

template <class T>
class MyList{
private:
    Node<T>* head;
    Node<T>* tail;
    int dataSize = 0;

public:
    /*ok */ MyList(T val);                           //construtor com valor inicial
    /*ok */ MyList();                                //construtor padrao
    /*ok */ ~MyList(){clear();}                      //destrutor
    /*ok */ void clear();                            // limpa a lista
        
    /*ok */ void push_back(T val);                   // insere elemento no final
    /*ok */ void push_front(T val);                  // insere elemento no início
    /*ok */ void pop_back();                         // remove elemento do final
    /*ok */ void insert(T val, int pos);             // insere elemento em posição específica

    /*ok */ void imprimir();                         // imprime lista iterativamente
    /*ok */ void imprimirRecursivo(Node<T>* ptr);    // imprime lista recursivamente (ajudante)
    /*ok */ void imprimirRecursivo();                // imprime lista recursivamente (público)
    /*ok */ void imprimirInverso(Node<T> *ptr);      // imprime inversamente (ajudante)
    /*ok */ void imprimirInverso();                  // imprime inversamente (público)

    // ---------------- Funçoes importantes ----------------
    /*ok */ int size() const;                        // retorna o tamanho da lista
    /*ok */ bool empty();                            // verifica se a lista está vazia
    /*ok */ void copy(Node<T>* other);               // copia outra lista
    /*ok */ Node<T>* find(Node<T>*ptr, T val);       // busca valor recursivamente(ajudante)
    /*ok */ Node<T>* buscar(T val);                  // busca valor recursivamente(publico)
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
    Node<T>* current = head;
    while(current){
        Node<T>* nextptr = current->next;
        delete current;
        current = nextptr;
    }
    head = nullptr;
    tail = nullptr;
    dataSize = 0;
}

// ---------------- Inserir e Remover ----------------
template <class T>
void MyList<T>::push_back(T val){
    Node<T>* newNode = new Node<T>(val);
    newNode->next = nullptr;

    if(empty()){
        head = newNode;
        tail= newNode;
    }
    else{
       tail->next = newNode;
       tail = newNode; 
    }
    dataSize++;
}

template<class T>
void MyList<T>::push_front(T val){
    Node<T>*newNode = new Node<T>(val);
    
    if(empty()){
        head = newNode;
        tail = newNode;
    }
    else{   
        newNode->next = head;
        head = newNode;
    }
    dataSize++;
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
void MyList<T>::insert(T val, int pos){
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

        for(int i = 0; i < pos; i++){
            aux = aux->next;
        }
        newNode->next = aux->next;
        aux = newNode;
        dataSize++;
    }
}

//  ---------------- Impressões ----------------
template<class T>
void MyList<T>::imprimir(){
    if(dataSize == 0)return;
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
    if(dataSize == 0) return;
    if(!ptr) return;

    imprimirInverso(ptr->next);
    std::cout<< ptr->data << " ";
}

template <class T>  
void MyList<T>::imprimirInverso(){
    imprimirInverso(head);
}

// ---------------- Funções importantes ----------------
template<class T>
int MyList<T>::size() const{
    return dataSize;
}

template <class T>
bool MyList<T>::empty(){
  return dataSize == 0;
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