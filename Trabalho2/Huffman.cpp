#include "Huffman.h"
#include <exception>
#include <iostream>

// NOTA: ao longo da implementacao adicionei alguns tratamentos de excessao pois alem de ser util para debug acredito
// que seja uma boa pratica p/ evitar fonte de erros
//---------- funcoes Node ------------// constutores

Node::Node(char simbolo, int frequencia) 
    : symbol(simbolo), freq(frequencia), left(nullptr), right(nullptr), isLeaf(true) {}

Node::Node(Node* esquerda, Node* direita, int frequencia)
    : symbol('\0'), freq(frequencia), left(esquerda), right(direita), isLeaf(false) {}

//---------- funcoes NodeInfo ------------// construtores e operador >

NodeInfo::NodeInfo() : symbol('\0'), freq(0), isLeaf(false), nodePtr(nullptr) {}

NodeInfo::NodeInfo(char s, int f, Node* ptr) : symbol(s), freq(f), isLeaf(true), nodePtr(ptr) {}

NodeInfo::NodeInfo(int f, Node* ptr) : symbol('\0'), freq(f), isLeaf(false), nodePtr(ptr) {}

// note que aqui precisamos definir algun criterios, respectivamente,
//prioridade menor freq -> no folha tem prioridade sobre no interno -> menor ascii tem prioridade nas folhas
bool NodeInfo::operator>(const NodeInfo& other) const {
    if (freq != other.freq) {
        return freq < other.freq;  // menor frequencia = maior prioridade
    }
    if (isLeaf != other.isLeaf) {
        return isLeaf && !other.isLeaf;  // folhas tem prioridade
    }
    if (isLeaf && other.isLeaf) {
        return symbol < other.symbol;  // menor ascii tem prioridade
    }
    return false;
}

//---------- funcoes HuffManTree ------------//

HuffManTree::HuffManTree(int freqs[256]) {  // apenas constroi arvore e gera codigos
    try {
        root = buildTree(freqs);
    } catch(std::exception &e) {
        throw std::runtime_error("erro construtor");
    }
    
    if (!root) return;  //p/ nao gerar codigo se n houver arvore
    
    MyVec<bool> currentCode;
    generateCodes(root, currentCode);
}

HuffManTree::~HuffManTree() {
    destroyTree(root);
}

// gera codigos percorrendo arvore
// left = 0 ; right = 1
void HuffManTree::generateCodes(Node* node, MyVec<bool>& currentCode) {
    if(!node) return;

    // se chegou folha salva codigo atual pro caracter
    if(node->isLeaf) {
        codes[(unsigned char)node->symbol] = currentCode;
        return;
    }

    // percorre subarvore left colocando bit 0
    if(node->left) {
        currentCode.push_back(false);
        generateCodes(node->left, currentCode);
        currentCode.pop_back();  // remove bit ao voltar da recursao
    }
    
    // percorre subarvore right colocando bit 1
    if(node->right) {
        currentCode.push_back(true);
        generateCodes(node->right, currentCode);
        currentCode.pop_back();  // logica igual
    }
}

void HuffManTree::destroyTree(Node* node) { // aux do destrutor, destroi arvore recursivamente 
    if(!node) return;
    destroyTree(node->left);   
    destroyTree(node->right);  
    delete node;               // so deleta ao final
}

// constroi arvore de huffman usando fila de prioridade
// aqui achei interessante implementar casos especiais para 0 e 1 caracter
Node* HuffManTree::buildTree(int freqs[256]) {
    MyPriorityQueue<NodeInfo> queue;

    // adiciona todos os caracteres com freq > 0 na fila
    for(int i = 0; i < 256; i++) {
        if(freqs[i] > 0) {
            Node* leafNode = new Node((char)i, freqs[i]);
            queue.push(NodeInfo((char)i, freqs[i], leafNode));
        }
    }
    
    // nenhum caracter entao arvore vazia, caso especial
    if(queue.size() == 0) return nullptr;
    
    // apenas um caracter entao cria arvore com um nivel, caso esepecial
    if(queue.size() == 1) {     // achei necessario para evitar codigo vazio
        NodeInfo leafInfo = queue.top();
        queue.pop();
        
        Node* newRoot = new Node(leafInfo.nodePtr, nullptr, leafInfo.freq);
        return newRoot;
    }

    while(queue.size() > 1) {    // combina os dois nos de menor frequencia
        NodeInfo first = queue.top(); queue.pop();  
        NodeInfo second = queue.top(); queue.pop();
        
        // cria no interno conectando os dois nos
        Node* mergedNode = new Node(first.nodePtr, second.nodePtr, first.freq + second.freq);
        
        // adiciona no combinado de volta na fila
        queue.push(NodeInfo(first.freq + second.freq, mergedNode));
    }
    return queue.top().nodePtr;
}

// comprime texto usando os codigos gerados
void HuffManTree::comprimir(MyVec<bool>& out, const MyVec<char>& in) const {
    if(!root) return;
    out.clear();

    // para cada caracter do texto original
    for(size_t i = 0; i < in.size(); i++) {
        unsigned char symbol = (unsigned char)in[i];
        const MyVec<bool>& code = codes[symbol];
        
        // verifica se caracter tem codigo valido
        if(code.size() == 0) {
            std::cerr << "Erro: simbolo sem codigo: " << (int)symbol << std::endl;
            continue;
        }
        
        // adiciona cada bit do codigo ao resultado
        for(size_t j = 0; j < code.size(); j++) {
            out.push_back(code[j]);
        }
    }
}

// descomprime bits navegando pela arvore
void HuffManTree::descomprimir(MyVec<char>& out, const MyVec<bool>& in) const {
    if(!root || in.empty()) return;
    out.clear();
    
    Node* current = root;
    
    // arvore com apenas um caracter, caso especial
    // achei necessario tratar separadamente pois nao ha navegacao
    if(root->left && !root->right && root->left->isLeaf) {
        for(size_t i = 0; i < in.size(); i++) {
            out.push_back(root->left->symbol);
        }
        return;
    }
    
    // navega pela arvore seguindo os bits
    for(size_t i = 0; i < in.size(); i++) {
        // bit 1 = direita, bit 0 = esquerda
        if(in[i]) {
            current = current->right;
        } else {
            current = current->left;
        }
        
        // verifica se caminho e valido
        if(!current) {
            std::cerr << "Erro: caminho invalido na arvore no bit " << i << std::endl;
            return;
        }
        
        // se chegou folha adiciona caracter e volta para raiz
        if(current->isLeaf) {
            out.push_back(current->symbol);
            current = root;
        }
    }
    
    // avisa se sequencia ficou incompleta
    if(current != root && !current->isLeaf) {
        std::cerr << "Aviso: sequencia de bits incompleta" << std::endl;
    }
}
