#include <algorithm>
#include <utility>
#include <iostream>
#include<exception>
#include "../MyQueue.h"

template <class T>
class MySetIterator;
template <class T>
class Node;

template <class T>
class Node{          //nao tem tanta importancia ser tudo public pq a class so eh usada aqui
public:
    typedef MySetIterator<T> iterator;
    T data;
    Node<T>* left;         //valores menores (esquerda da arvore)
    Node<T>* right;        //valores maiores (direita da arvore)

    Node<T>* parent;
    Node(T val): data(val), left(nullptr), right(nullptr), parent(nullptr){}
};

template <class T>
class MySet{ 
public:
    typedef MySetIterator<T> iterator;
    /*OK */ MySet() : size_(0), root(nullptr) {}          //construtor destrutor
    /*OK */ ~MySet();
    /*OK */ int size() const {return size_;} 

    /*OK */ std::pair<iterator, bool> insert(const T&elem);
    /*OK */ iterator find(const T&elem);
    
    /*OK */ void imprimeDFS_in() const;     //left -> visita ->right
    /*OK */ void imprimeDFS_pre() const;    //visita -> left -> rigth
    /*OK */ void imprimeDFS_pos() const;    //left -> right -> visita
    /*OK */ void imprimeBFS() const;


    /*OK */ void deleteNode(Node<T>*toDelete);
    /*OK */ Node<T>* copyNode(Node<T>*root) const;
    //-----------FUNCOES ITERADORES----------//
    iterator begin();
    iterator end(){return iterator(nullptr);}
    //----------FUNCOES OPERADORES--------//
    T& operator[](const int n);

private:
    
    Node<T>* root;          //raiz da arvore
    int size_;

    /*OK */ void imprimeDFS_in(Node<T>*root) const;
    /*OK */ void imprimeDFS_pre(Node<T>*root) const;
    /*OK */ void imprimeDFS_pos(Node<T>*root) const;
    /*OK */ void imprimeBFS(Node<T>*root) const;
    /*OK */ iterator find(const T&elem, Node<T>* root);     //metodo privado
    /*OK */ std::pair<iterator, bool> insert(const T& elem, Node<T>*& root, Node<T>* parent);
};

template <class T>
class MySetIterator {
friend class MySet<T>;
private:
    Node<T>*ptr;
public:
    MySetIterator(Node<T>*ptr_) : ptr(ptr_){}   //construtor com argumento
    MySetIterator(): ptr(nullptr){}             //construtor padrao

    T& operator*(){ return ptr->data; }

    bool operator==(const MySetIterator &other)const {return ptr == other.ptr;}
    bool operator!=(const MySetIterator &other)const {return ptr != other.ptr;}

    MySetIterator operator++();         //pre e pos incremento
    MySetIterator operator++(int);

    MySetIterator operator--();         //pre e pos decremento
    MySetIterator operator--(int);

};

template <class T>
MySetIterator<T> MySetIterator<T>::operator--(){
    if(!ptr) return *this;   //derreferencia o objeto -> temos o ponteiro -> retorna o ponteiro nptr
    
    if(ptr->left){
        ptr = ptr->left;
        while(ptr->right){
            ptr = ptr->right;
        }
    } else{
        while(ptr->parent && ptr == ptr->parent->left){
            ptr = ptr->parent;
        }
        ptr = ptr->parent;
    }
    return *this;
}



template<class T>
MySetIterator<T> MySetIterator<T>::operator++(){
    if(!ptr) return *this;
    
    if(ptr->right){
        ptr = ptr->right;
        while(ptr->left){
            ptr = ptr->left;
        }
    }
    else{
        while(ptr->parent && ptr == ptr->parent->right){
            ptr = ptr->parent;
        }
        ptr = ptr->parent;
    }
    return *this;
}

template<class T>
MySetIterator<T> MySetIterator<T>::operator++(int){
    MySetIterator<T> aux = *this;
    ++(*this);
    return aux;
}

template<class T>
MySetIterator<T> MySetIterator<T>::operator--(int){
    MySetIterator<T> aux = *this;
    --(*this);
    return aux;
}

template <class T>
MySet<T>::~MySet() {
    deleteNode(root);
}

template <class T>
void MySet<T>::deleteNode(Node<T>*toDelete){
    if(!toDelete) return;
    deleteNode(root->left);
    deleteNode(root->right);
    delete toDelete;
}

template <class T>
Node<T>* MySet<T>::copyNode(Node<T>*root) const{
    if(!root) return nullptr;

    Node<T>* current = new Node<T>(root->data);
    current->left = copyNode(root->left);
    current->right = copyNode(root->right);

    return current;
}

template<class T>
typename MySet<T>::iterator MySet<T>::find(const T&elem){
    return find(elem, root);
}

template<class T>
typename MySet<T>::iterator MySet<T>::find(const T&elem, Node<T>* root) {
    if(!root) return iterator(nullptr);

    if(elem < root->data)
        return find(elem, root->left);
    if(elem > root->data)
        return find(elem, root->right);
    else
        return iterator(root);
}

template <class T>
std::pair<typename MySet<T>::iterator, bool>MySet<T>::insert(const T&elem){
    return insert(elem, root, nullptr);
}

template <class T>
std::pair<typename MySet<T>::iterator, bool> MySet<T>::insert(const T& elem, Node<T>*& root, Node<T>* parent) {
    if(!root){
        root = new Node<T>(elem);
        root->parent = parent;  // Aqui está usando o parent corretamente
        size_++;
        return std::make_pair(iterator(root), true);
    }
    if(elem < root->data)
        return insert(elem, root->left, root);
    else if(elem > root->data)
        return insert(elem, root->right, root);
    else
        return std::make_pair(iterator(root), false);
}


template<class T>
void MySet<T>::imprimeDFS_pre() const{
    imprimeDFS_pre(root);
}

template<class T>
void MySet<T>::imprimeDFS_pre(Node<T>*root) const{
    if (!root) return;

    std::cout<< root->data << " ";  //visita -> left -> right
    imprimeDFS_pre(root->left);     
    imprimeDFS_pre(root->right); 
 
}

template<class T>
void MySet<T>::imprimeDFS_pos() const{
    imprimeDFS_pos(root);
}

template<class T>
void MySet<T>::imprimeDFS_pos(Node<T>*root) const{
    if(!root) return;

    imprimeDFS_pos(root->left);     //left -> visita -> right
    imprimeDFS_pos(root->right);
    std::cout<<root->data<< " ";
}

template<class T>
void MySet<T>::imprimeDFS_in() const{
    imprimeDFS_in(root);
}

template<class T>
void MySet<T>::imprimeDFS_in(Node<T>*root) const{
    if(!root) return;

    imprimeDFS_in(root->left);     //left -> visita -> right 
    std::cout<<root->data<< " ";
    imprimeDFS_in(root->right);
}

template <class T>
void MySet<T>::imprimeBFS() const{
    imprimeBFS(root);
}
template<class T>
void MySet<T>::imprimeBFS(Node<T>*root) const{
    if (!root) return;

    MyQueue<Node<T>*> q;
    q.push(root);

    while(!q.empty()){
        Node<T>*current = q.front();
        q.pop();

        std::cout<< current->data << " ";

        if(current->left) q.push(current->left);
        if(current->right) q.push(current->right);
    }
}

template <class T>
typename MySet<T>::iterator MySet<T>::begin(){
    if (!root) return end();

    Node<T>*ptr = root;
    while(ptr->left)
        ptr = ptr->left;  
    
    return iterator(ptr);     
} 


template <class T>
T& MySet<T>::operator[](const int n){
    if(n<0 || n>size_)  throw std::out_of_range("Erro de indice.");

    MySet<T>::iterator it = begin();
    for(int i=0; i<n; i++) it++;

    return *it;
}