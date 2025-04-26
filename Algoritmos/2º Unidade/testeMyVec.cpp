#include <iostream>
#include "MyVec.h" // Assume que o codigo acima esta salvo em um arquivo chamado MyVec.h

int main() {
    std::cout << "\n--- Testando MyVec com inteiros ---\n";
    
    // Teste construtor vazio
    MyVec<int> vec1;
    std::cout << "Vec1 inicializado (vazio): " << vec1 << std::endl;
    std::cout << "Vec1 esta vazio? " << (vec1.empty() ? "Sim" : "Nao") << std::endl;
    
    // Teste push_back
    std::cout << "\n--- Testando push_back ---\n";
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    vec1.push_back(40);
    vec1.push_back(15);
    std::cout << "Vec1 apos push_back: " << vec1 << std::endl;
    std::cout << "Tamanho de Vec1: " << vec1.size() << std::endl;
    
    // Teste operator[]
    std::cout << "\n--- Testando operator[] ---\n";
    std::cout << "Vec1[2] = " << vec1[2] << std::endl;
    vec1[2] = 25;
    std::cout << "Vec1 apos modificar Vec1[2]: " << vec1 << std::endl;
    
    // Teste construtor com n elementos
    std::cout << "\n--- Testando construtor com n elementos ---\n";
    MyVec<int> vec2(5, 7);
    std::cout << "Vec2 inicializado com 5 elementos de valor 7: " << vec2 << std::endl;
    
    // Teste insert
    std::cout << "\n--- Testando insert ---\n";
    vec2.insert(99, 2);
    std::cout << "Vec2 apos inserir 99 na posicao 2: " << vec2 << std::endl;
    
    // Teste pop_back
    std::cout << "\n--- Testando pop_back ---\n";
    vec2.pop_back();
    std::cout << "Vec2 apos pop_back: " << vec2 << std::endl;
    
    // Teste find
    std::cout << "\n--- Testando find ---\n";
    int pos = vec2.find(99);
    std::cout << "Posicao do elemento 99 em Vec2: " << pos << std::endl;
    pos = vec2.find(42);
    std::cout << "Posicao do elemento 42 em Vec2 (nao existe): " << pos << std::endl;
    
    // Teste imprimir e imprimirInverso
    std::cout << "\n--- Testando imprimir e imprimirInverso ---\n";
    std::cout << "Vec1 usando metodo imprimir: ";
    vec1.imprimir();
    std::cout << "Vec1 usando metodo imprimirInverso: ";
    vec1.imprimirInverso();
    
    // Teste ordenar
    std::cout << "\n--- Testando ordenar ---\n";
    MyVec<int> vec3;
    vec3.push_back(42);
    vec3.push_back(17);
    vec3.push_back(9);
    vec3.push_back(36);
    vec3.push_back(25);
    vec3.push_back(8);
    vec3.push_back(13);
    
    std::cout << "Vec3 antes de ordenar: " << vec3 << std::endl;
    vec3.ordenar();
    std::cout << "Vec3 apos ordenar: " << vec3 << std::endl;
    
    // Teste com strings
    std::cout << "\n--- Testando MyVec com strings ---\n";
    MyVec<std::string> vecStr;
    vecStr.push_back("banana");
    vecStr.push_back("maca");
    vecStr.push_back("laranja");
    vecStr.push_back("abacaxi");
    
    std::cout << "VecStr antes de ordenar: " << vecStr << std::endl;
    vecStr.ordenar();
    std::cout << "VecStr apos ordenar: " << vecStr << std::endl;
    
    return 0;
}