#include <iostream>
#include <string>
#include "MyVecNewIterator.h"
#include "MySet.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Use: " << argv[0] << " myvec|myset\n";
        return 1;
    }

    std::string arg = argv[1];
    std::string word;
    int total = 0;

    if (arg == "myvec") {
        MyVec<std::string> uniqueWords;

        while (std::cin >> word) {
            total++;
            // verifica se word está no uniqueWords
            bool found = false;
            for (MyVec<std::string>::iterator it = uniqueWords.begin(); it != uniqueWords.end(); ++it) {
                if (*it == word) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                uniqueWords.push_back(word);
            }
        }

        std::cout << total << " " << uniqueWords.size() << "\n";
    }

    else if (arg == "myset") {
        MySet<std::string> uniqueWords;

        while (std::cin >> word) {
            total++;
            uniqueWords.insert(word);
        }

        std::cout << total << " " << uniqueWords.size() << "\n";
    }

    else {
        std::cerr << "Argumento nao eh valido use 'myvec' ou 'myset'.\n";
        return 1;
    }

    return 0;
}



/* ANALISE
- Sobre tempo:
O MyVec o cresce consideravelmente com a quantidade de palavras, especialmente se forem muitas palavras iguais, tempo linear O(n) pra busca
O MySet o tempo de busca e insercao eh, de modo geral, O(log n) mas depende de quao balanceada a arvore esteja, no pior caso a arvore eh degenerada e o custo eh O(n)

- Sobre otimizacao
Poderiamos manter o myvec ordenado e fazer busca binaria para verificar se o elemento esta no vetor, teriamos um custo O(log n) + custo de insercao

O problema da ABP ocorre no seu pior caso quando a arvore eh degenerada, devemos achar uma solucao para manter a arvore balanceada, asim o custo achar e inserir sera O(log n)




*/
