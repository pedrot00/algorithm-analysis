#include <iostream>
#include <string>
#include "MyListStruct.h"


void testarInicio() {
    std::cout << "\n===== TESTE DOS CONSTRUTORES =====\n";
    
    std::cout << "Criando lista com construtor padrao: ";
    MyList<int> lista1;
    std::cout << "Tamanho: " << lista1.size() << ", Conteudo: ";
    lista1.imprimir();
    
    std::cout << "Criando lista com valor inicial 42: ";
    MyList<int> lista2(42);
    std::cout << "Tamanho: " << lista2.size() << ", Conteudo: ";
    lista2.imprimir();
}

void testarInsercao() {
    std::cout << "\n===== TESTE DE INSERCAO =====\n";
    
    MyList<int> lista;
    std::cout << "Lista vazia criada. Tamanho: " << lista.size() << std::endl;
    
    std::cout << "Inserindo elementos com push_back: ";
    for (int i = 1; i <= 5; i++) {
        lista.push_back(i * 10);
    }
    std::cout << "Tamanho: " << lista.size() << ", Conteudo: ";
    lista.imprimir();
    
    std::cout << "Inserindo elementos com push_front: ";
    for (int i = 1; i <= 3; i++) {
        lista.push_front(i);
    }
    std::cout << "Tamanho: " << lista.size() << ", Conteudo: ";
    lista.imprimir();
    
    std::cout << "Inserindo valor 999 na posicao 4: ";
    lista.insert(999, 4);
    std::cout << "Tamanho: " << lista.size() << ", Conteudo: ";
    lista.imprimir();
    
    std::cout << "Inserindo valor 888 na posicao 0: ";
    lista.insert(888, 0);
    std::cout << "Tamanho: " << lista.size() << ", Conteudo: ";
    lista.imprimir();
    
    std::cout << "Inserindo valor 777 na ultima posicao: ";
    lista.insert(777, lista.size());
    std::cout << "Tamanho: " << lista.size() << ", Conteudo: ";
    lista.imprimir();
    
    std::cout << "Tentando inserir em posicao invalida (-1): ";
    lista.insert(123, -1);
    
    std::cout << "Tentando inserir em posicao invalida (tamanho+1): ";
    lista.insert(123, lista.size() + 1);
}

void testarRemocao() {
    std::cout << "\n===== TESTE DE REMOCAO =====\n";
    
    MyList<int> lista;
    for (int i = 1; i <= 5; i++) {
        lista.push_back(i);
    }
    
    std::cout << "Lista inicial: ";
    lista.imprimir();
    
    std::cout << "Removendo elemento do final: ";
    lista.pop_back();
    std::cout << "Conteudo: ";
    lista.imprimir();
    
    std::cout << "Removendo outro elemento do final: ";
    lista.pop_back();
    std::cout << "Conteudo: ";
    lista.imprimir();
    
    std::cout << "Removendo todos os elementos restantes: ";
    while (!lista.empty()) {
        lista.pop_back();
    }
    std::cout << "Tamanho: " << lista.size() << ", Conteudo: ";
    lista.imprimir();
    
    std::cout << "Tentando remover de lista vazia: ";
    lista.pop_back();
    std::cout << "Tamanho: " << lista.size() << std::endl;
}

void testarImpressao() {
    std::cout << "\n===== TESTE DE IMPRESSAO =====\n";
    
    MyList<char> lista;
    std::string palavra = "ALGORITMOS";
    
    for (char c : palavra) {
        lista.push_back(c);
    }
    
    std::cout << "Lista normal: ";
    lista.imprimir();
    
    std::cout << "Lista recursiva: ";
    lista.imprimirRecursivo();
    std::cout << std::endl;
    
    std::cout << "Lista inversa: ";
    lista.imprimirInverso();
    std::cout << std::endl;
}

void testarBusca() {
    std::cout << "\n===== TESTE DE BUSCA =====\n";
        
    MyList<int> lista;
    for (int i = 10; i <= 50; i += 10) {
        lista.push_back(i);
    }
        
    std::cout << "Lista: ";
    lista.imprimir();
        
    int valoresBusca[] = {20, 40, 99};
    for (int val : valoresBusca) {
        Node<int>* resultado = lista.buscar(val);  // Usando a nova função
        std::cout << "Buscando valor " << val << ": ";
        if (resultado) {
            std::cout << "Encontrado (" << resultado->data << ")" << std::endl;
        } else {
            std::cout << "Nao encontrado" << std::endl;
        }
    }
}

void testarCopy() {
    std::cout << "\n===== TESTE DE COPIA =====\n";
    
    MyList<int> listaOriginal;
    for (int i = 1; i <= 5; i++) {
        listaOriginal.push_back(i);
    }
    
    std::cout << "Lista original: ";
    listaOriginal.imprimir();
    
    MyList<int> listaCopia;
    std::cout << "Lista copia antes: ";
    listaCopia.imprimir();
    
    // NOTA: Este teste nao funciona assim diretamente,
    // pois copy recebe um Node*, nao uma lista inteira
    // Este eh apenas um exemplo conceitual!!!
    std::cout << "Apos copia (conceitual - precisa ajuste): " << std::endl;
    std::cout << "Para testar a funcao copy corretamente, ela precisa ser modificada" << std::endl;
    std::cout << "ou voce precisa acessar o head da lista original diretamente." << std::endl;
}

int main() {
    std::cout << "TESTES DA CLASSE MyList<T>\n";
    std::cout << "=========================\n";
    
    testarInicio();
    testarInsercao();
    testarRemocao();
    testarImpressao();
    testarBusca();
    testarCopy();
    
    std::cout << "\nTodos os testes foram executados.\n";
    
    return 0;
}