#include<iostream>

template <class T>
struct Node{
    T data;
    Node *next;
};

template <class T>
class MyList{
private:
    Node<T>* head;
    Node<T>* tail;
    int dataSize = 0;

public:
    /*ok */ MyList(T val);       //construtor com valor inicial
    /*ok */ MyList();             //construtor padrao
    /*ok */ ~MyList(){clear();}
    /*ok */ void clear();
    
    insert();     
    push_back(); 
    front_back();  
    /*ok */ void pop_back();   

    /*ok */ void imprimir();
    /*ok */ void imprimirRecursivo(Node<T>* ptr);
    /*ok */ void imprimirRecursivo();
    /*ok */ void imprimirInverso(Node<T> *ptr);
    /*ok */ void imprimirInverso();

    
    /*ok */ int size() const; 
    /*ok */ bool empty();
    /*ok */ void copy(Node<T>* other);
    /*ok */ Node<T>* find(Node<T>*ptr, T val);
    order();    //ordena com o merge
    
};

//Funcoes importantes -------------
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
//---------------------------------

//Construtores e destrutores -------------
template <class T>
MyList<T>::MyList(){
    Node<T>* ptr = new Node<T>;
    ptr->data = T();
    ptr->next = nullptr;
    head = ptr;
    tail = ptr;
}

template <class T>
MyList<T>::MyList(T val){
    Node<T>*ptr = new Node<T>;      //isso aqui eh a criacao padrao
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

//----------------------------------------

// Saida e impressoes -------------------
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

//----------------------------------------

// inserir e remover ---------------------
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
//----------------------------------------
