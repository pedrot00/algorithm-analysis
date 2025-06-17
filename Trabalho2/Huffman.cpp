#include "Huffman.h"
#include <exception>
#include <utility>
#include <iostream>

HuffManTree::HuffManTree(int freqs[256]){
     try{
        root = buildTree(freqs);
    } catch(std::exception &e){
        throw std::runtime_error("error construtor");
    }
    
    if (!root) return;
    MyVec<bool> currentCode;
    generateCodes(root, currentCode);
}

void HuffManTree::generateCodes(Node* node, MyVec<bool>&currentCode){
    if(!node)return;

    if(!node->left && !node->right){        //se folha adiciona o simbolo dele
        codes[node->symbol] = currentCode;
        return;
    }

    // percorre recursivamente  até econtrar folhas
    if(node->left){
        currentCode.push_back(0);       
        generateCodes(node->left, currentCode);
        currentCode.pop_back();
    }
    if(node->right){
        currentCode.push_back(1);
        generateCodes(node->right, currentCode);
        currentCode.pop_back();
    }

}
HuffManTree:: ~HuffManTree(){
    destroyTree(root);
}

void HuffManTree::destroyTree(Node* node){
    if(!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

Node* HuffManTree::buildTree(int freqs[256]){
    MyPriorityQueue<Node*> queue; 

    for(int i = 0; i < 256; i++){       //transf. do array elementos com freq > 0 em folha
        if(freqs[i] > 0){
            Node* leaf = new Node((char)i, freqs[i]);
            queue.push(leaf);  
        }
    }
    if (!queue.size()) return nullptr;
    
    if(queue.size() == 1){      //setta um unico no com 1 bit de profundidade
        Node * current = queue.top();
        queue.pop();
        Node *root = new Node(nullptr, current, current->freq);
        return root;
    }

    // combina todos os nos -> conecta menores -> maior elemento fica mais perto da raiz
    while(queue.size() > 1) {
        Node* right = queue.top(); queue.pop();
        Node* left = queue.top(); queue.pop();
        
        Node* inside = new Node(left, right, left->freq + right->freq);
        queue.push(inside);
    } 
    return queue.top();     //retorna a raiz ao final com a arvore ja montada
}


void HuffManTree::comprimir(MyVec<bool> &out, const MyVec<char> &in) const {
    if (!root) return;
    
}

//------------- Funcoes NodeComparator -------------//
bool NodeComparator::operator()(Node*a, Node*b){
    return a->freq < b->freq;
}