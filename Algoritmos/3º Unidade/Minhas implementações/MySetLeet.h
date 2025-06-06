#include <algorithm>
#include <utility>
#include <iostream>
#include "../MyQueue.h"

template <class T>
class MySetIterator;
template <class T>
class Node;

template <class T>
class Node{          //nao tem tanta importancia ser tudo public pq a class so eh usada aqui
public:
    T data;
    Node<T>* left;         //valores menores (esquerda da arvore)
    Node<T>* right;        //valores maiores (direita da arvore)

    Node<T>* parent;
    Node(T val): data(val), left(nullptr), right(nullptr), parent(nullptr){}
};

template <class T>
class MySet{  
private:
    typedef MySetIterator<T> iterator;
    Node<T>* root;          //raiz da arvore
    int size_;

    /*OK */ void imprimeDFS_in(Node<T>*root) const;
    /*OK */ void imprimeDFS_pre(Node<T>*root) const;
    /*OK */ void imprimeDFS_pos(Node<T>*root) const;
    /*OK */ void imprimeBFS(Node<T>*root) const;
    /*OK */ iterator find(const T&elem, Node<T>* root);     //metodo privado
    /*OK */ std::pair<iterator, bool> insert(const T&elem, Node<T>*root);

    //----------FUNCOES LEET--------//
    int somaPares();
    int contMenorElem(const T& elem);

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

    //----------FUNCOES LEET--------//
    /*OK */ int treeSum(Node<T>*root);
    /*OK */ int maxHeight(Node<T>*root);
    /*OK */ int countLeaf(Node<T>*root);
    /*OK */ bool findNode(Node<T>*root, const T&elem);
    /*OK */ bool equalTrees(Node<T>*t1, Node<T>*t2);
    /*OK */ void somaPares(Node<T>*root, int &cont);
            void contMenorElem(const T& elem, Node<T>*root, int &cont);
};

template <class T>
int contMenorElem(const T& elem){
    int cont = 0;
    contMenorElem(elem, cont);
    return cont;
}

template <class T>
void contMenorElem(const T& elem, Node<T>*root, int &cont){
    if(!root) return;
}

template <class T>
class MySetIterator {
friend class MySet<T>;
private:
    Node<T>*ptr;
public:
    MySetIterator(Node<T>*ptr_) : ptr(ptr_){}
    T& operator*(){ return ptr->data; }

    bool operator==(const MySetIterator &other)const {return ptr == other.ptr;}
    bool operator!=(const MySetIterator &other)const {return ptr != other.ptr;}

    MySetIterator operator++();         //pre e pos incremento
    MySetIterator operator++(int);

    MySetIterator operator--();         //pre e pos decremento
    MySetIterator operator--(int);

};

template <class T>
MySet<T>::~MySet() {
    deleteNode(root);
}

template <class T>
void MySet<T>::deleteNode(Node<T>*toDelete){
    if(!toDelete) return
    deleteNode(root->left)
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
    return insert(elem, root);
}
template <class T>
std::pair<typename MySet<T>::iterator, bool> insert(const T&elem, Node<T>*&root, Node<T>*&parent){
    if(!root){
        root = new Node<T>(elem);
        root->parent = parent;
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
    imprimeDFS_pos(root)
}

template<class T>
void MySet<T>::imprimeDFS_pos(Node<T>*root) const{
    if(!root) return;

    imprimeDFS_pos(root->left);     //left -> visita -> right
    imprimeDFS_pos(root->right);
    std::cout<<root->data;
}

template<class T>
void MySet<T>::imprimeDFS_in() const{
    imprimeDFS_in(root);
}

template<class T>
void MySet<T>::imprimeDFS_in(Node<T>*root) const{
    if(!root) return;

    imprimeDFS_in(root->left);     //left -> visita -> right 
    std::<<root->data;
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
        Node<T>*curret = q.front();
        q.pop();

        std::cout<<current->data << " ";

        if(current->left) q.push(current->left)
        if(current->right) q.push(current->left);
    }
}

template <class T>
int MySet<T>:: treeSum(Node<T>*root){
    if(!root) return 0;

    int cont = root->data;

    cont+= treeSum(root->left);
    cont+=treeSum(root->right);

    return cont;

}


template<class T>   // podemos implementar utilizando a BFS armazenando o nível utilizando dois while
int MySet<T>::maxHeight(Node<T>*root){
    if(!root) return -1;

    MyQueue<std::pair<Node<T>*,int>> queue;
    queue.push({root, 0});

    int maxNivel = 0;

    while(!queue.empty()){
        std::pair<Node<T>*, int> current = queue.front();
        queue.pop();

        maxNivel = std::max(maxNivel, current->second);

        if(current.first->left) 
            queue.push({current.first->left, nivel+1});
        if(current.first->right) 
            queue.push({current.first->right, nivel+1});
    }
    return maxNivel; 
}

template<class T>
int MySet<T>::countLeaf(Node<T>*root){
    if(!root) return 0;
    
    if(!root->left && !root->right)
        return 1;
    
    return countLeaf(root->left) + countLeaf(root->right);
}


template<class T>
bool MySet<T>::findNode(Node<T>*root, const T&elem){
    if(!root) return false;

    if(root->data == elem)
        return true;
    if(findNode(root->left, elem))
        return true;
    if(findNode(root->right, elem))
        return true;

     return false;
}

template<class T>
bool MySet<T>::equalTrees(Node<T>*t1, Node<T>*t2){
    if(!t1 && !t2)          //cassos bases
        return true;
    else if((t1 && !t2) || (!t1 && t2)) 
        return false;

    if(t1->data == t2->data && 
        equalTrees(t1->left, t2->left) && 
        equalTrees(t1->right, t2->right) 
    ) return true;
    
    return false;
}


template<class T>
int MySet<T>::somaPares(){
    int cont = 0;
    somaPares(root, cont);
    return cont;
}

template<class T>
void MySet<T>::somaPares(Node<T>*root, int &cont){
    if (!root) return 0;

    if(root->data%2 == 0)  cont++;
    somaPares(root->left, cont);
    somaPares(root->right, cont);
}


