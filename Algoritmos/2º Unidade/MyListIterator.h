#include <iostream>

template<class T> class MyListIterator;
template<class T> class Node;

template<class T>
class Node{
    public:
        T data;
        Node<T> *next;
        Node(const T& elem): data(elem), next(nullptr){}
};



template <class T>
class MyList{
private:
    Node<T> *head;
    Node<T> *tail;
    size_t dataSize;

    void create();          //implementa o construtor padrao
    void destroy(Node<T>*ptr);         //implementa o destrutor 
        
public:
    typedef MyListIterator<T> iterator;

    /*ok */ MyList();       //constutor padrao
    /*ok */ MyList(int tam, const T& init); //construtor que preenche a lista ate tam com init
    /*ok */ MyList(Node<T>& other); // construtor por copia
    /*ok */ ~MyList();      // destrutor 
    /*ok */ void destroy(); 

    /*ok */ void push_back(const T& elem);
    /*ok */ void push_front(const T& elem);
    /*ok */ void pop_back();
    /*not */ void insert (size_t pos, const T& elem);

    /*ok */ bool empty() const;     //todo metodo que nao altera o estado tem que ser const
    /*ok */ size_t size() const;

    iterator begin() {
        return iterator(head);
    };
    iterator end(){
        return iterator(nullptr);
    }
};

template<class T>
size_t MyList<T>::size() const{
    return dataSize;
}

template <class T>
bool MyList<T>::empty() const{
    return head == nullptr;
}

template <class T>
void MyList<T>::create(){
    dataSize = 0;
    head = tail = nullptr;
}

template<class T>
void MyList<T>::destroy(Node<T>* ptr){
    if(!ptr) return;
    destroy(ptr->next);
    delete ptr;

}
template<class T>
void MyList<T>::destroy(){
    destroy(head);
    head = tail = nullptr;
    dataSize = 0;
}

template <class T>
MyList<T>::MyList(){
    create();
}

template <class T>
MyList<T>::MyList(int tam, const T& init):head(nullptr), tail(nullptr), dataSize(0){
    for(int i=0; i<tam; i++){
        push_back(init);
    }
    //eh bom reutilizar o push_back pois ele:
    //cuida da alocacao, conecta os nos, atualiza head, atualiza tail e atualiza datasize
}

template <class T>
MyList<T>::~MyList(){
    destroy();
}

template <class T>
void MyList<T>::push_back(const T& elem){
    Node<T>* newNode = new Node<T>(elem);
    if(empty()){
        tail = head = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
    newNode->next = nullptr;
    dataSize++;
}

template <class T>
void MyList<T>::push_front(const T& elem){
    Node<T> *newNode = new Node<T>(elem);

    if(empty()){
        head = tail = newNode;
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
    
    if(head == tail){
        delete head;
        head = tail = nullptr;
    }
    else{
        Node<T>* current = head;
        while(current->next != tail){
            current = current->next;
        }
        delete tail; // ou delete current->next que sera o tail, mesma coisa
        tail = current;
        tail->next = nullptr;
    }
    dataSize--;
}

template <class T>
void MyList<T>::insert(size_t pos, const T& elem){
    if(pos < 0 || pos > size()) throw std::out_of_range("Posicao invalida");

    else if(pos == 0){ push_front(elem); }
    else if(pos == size()){ push_back(elem);}
    else{
        auto it = begin();
        std::advance(it, pos);  // avanca ate posicao
        insert(it, elem);       // reutiliza a versao com interador
    }
}

template<class T>
class MyListIterator{
private:
    Node<T>*current;

public:
    MyListIterator(Node<T>*node): current(node){}

    //operadores
    T& operator*(){ return current->data; }  //* operador de derreferenciacao 

    MyListIterator operator++(){
        current = current->next;
        return *this;
    }
    bool operator!=(const MyListIterator &other) const{
        return !(*this == other);
    }
    bool operator == (const MyListIterator &other) const{
        return current == other.current;
    }
};