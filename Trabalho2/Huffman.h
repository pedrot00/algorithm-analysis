#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "MyPriorityQueue.h"
#include "MyVec.h"


class Node {   
public:
    char symbol;     // caracter armazenado no no folha
    int freq;        // frequencia do caracter ou da soma  das frequencias dos filhos
    Node* left;   
    Node* right; 
    bool isLeaf;     // sera utilizado para verificar se o no eh ou nao uma folha

    Node(char simbolo, int frequencia); // construtor folha
    Node(Node* esquerda, Node* direita, int frequencia);    // construtor no inteerno
};

// estrutura aux. p/ organizacao na fila de prioridade
struct NodeInfo {       // NOTA: para manter mais legivel optei por implementar os construtores tambem no huffman.cpp
    char symbol;     
    int freq;        
    bool isLeaf;     
    Node* nodePtr;   

    NodeInfo();  // construtor padrao
    NodeInfo(char s, int f, Node* ptr); // construtor folha
    NodeInfo(int f, Node* ptr);  // construtor node interno
    
    bool operator>(const NodeInfo& other) const;    // importante para fila de prioridade
};

class HuffManTree {
private:
    Node* root;                   
    MyVec<bool> codes[256];        // tabela de codigos 

    Node* buildTree(int freqs[256]); // construtor 
    void destroyTree(Node* node); // destrutor
    void generateCodes(Node* node, MyVec<bool>& currentCode); // gera codigos que serao armazenados

public:
    HuffManTree(int freqs[256]);
    ~HuffManTree();

    //metodos principais
    void comprimir(MyVec<bool>& out, const MyVec<char>& in) const;
    void descomprimir(MyVec<char>& out, const MyVec<bool>& in) const;
    
};

#endif