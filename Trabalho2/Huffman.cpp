#include "Huffman.h"
#include <exception>
#include <iostream>

HuffManTree:: HuffManTree(int freqs[256]){
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


//------------- Funcoes NodeComparator -------------//
bool NodeComparator::operator()(Node*a, Node*b){
    return a->freq > b->freq;
}