#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "MyPriorityQueue.h"
#include "MyVec.h"

class Node; // prev declaration para nao haver problema no node interno da classe

class Node{ //atributos: simbolo, frequencia, pont. esquerda, pont. direita
public:
    char symbol;
    int freq;
    Node* left;
    Node *right;

    Node(char simbolo, int frequencia): symbol(simbolo), freq(frequencia), 
        left(nullptr), right(nullptr) {}    //construtor folha

    Node(int frequencia): symbol('\0'),freq(frequencia), 
        left(nullptr), right(nullptr){}     //construtor transbordo
    
    Node(Node* esquerda, Node* direita, int frequencia): 
    symbol('\0'), freq(frequencia), left(esquerda), right(direita) {} //construtor padrao
};

class NodeComparator{
public:
    /*OK*/ bool operator()(Node*a, Node*b);
};

class HuffManTree{
private:
    Node* root;
    MyVec<bool> codes[256];      //guarda codigo dos simbolos

    //-------- metodos auxiliares --------//

    Node* buildTree(int freqs[256]);
    /*OK*/ void destroyTree(Node* node);
    /*OK*/  void generateCodes( Node* node, MyVec<bool>&currentCode);   //gerador de codigos

public:
    HuffManTree(int freqs[256]);
    /*OK*/ ~HuffManTree();

    void comprimir(MyVec<bool> &out, const MyVec<char> &in) const;
    void descomprimir(MyVec<char> &out, const MyVec<bool> &in) const;
};


#endif