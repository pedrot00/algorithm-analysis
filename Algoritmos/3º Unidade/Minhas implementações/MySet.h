#include <algorithm>
#include <utility>

template <class T>
class MySetIterator;

template <class T>
class Node{          //nao tem tanta importancia ser tudo public pq a class so eh usada aqui
public:
    T data;
    Node* left;         //valores menores (esquerda da arvore)
    Node* right;        //valores maiores (direita da arvore)
    Node(T val): data(val), left(nullptr), right(nullptr){}
};

template <class T>
class MySet{  
private:
    typedef MySetIterator<T> iterator;
    Node<T>* root;          //raiz da arvore
    int size_;

    /*OK */ iterator find(const T&elem, Node<T>* root);     //metodo privado
    std::pair<iterator, bool> insert(const T&elem, Node<T>*root);

public:
    typedef MySetIterator<T> iterator;
    
    /*OK */ MySet() : size_(0), root(nullptr) {}          //construtor destrutor
    /*OK */ ~MySet();
    /*OK */ int size() const {return size_;} 

    std::pair<iterator, bool> insert(const T&elem);
    /*OK */ iterator find(const T&elem);
    
    void imprimeDFS_in() const;     //left -> root -> right
    void imprimeDFS_pre() const;    //root -> left -> rigth
    void imprimeDFS_pos() const;    //left -> right -> root


    /*OK */ void deleteNode(Node<T>*toDelete);
    /*OK */ Node<T>* copyNode(Node<T>*root) const;
};

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

    if(root->data == elem) 
        return iterator(root);
    else if(elem < root->data)
        return find(root->left);
    else
        return find(root->right);
}

template <class T>
std::pair<typename MySet<T>::iterator, bool>MySet<T>::insert(const T&elem){
    return insert(elem, root);
}
template <class T>
std::pair<typename MySet<T>::iterator, bool> insert(const T&elem, Node<T>*root){
    if(!root){
        Node<T>* newNode = new Node<T>(elem);
        size_++;
        return make_pair(iterator(root), true);

    }
}