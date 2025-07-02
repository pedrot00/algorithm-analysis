Eu li as regras
Pedro Santos Teixeira - 116224

Este programa implementa o algoritmo de Huffman para compactar e descompactar arquivos. Ele funciona criando códigos de tamanho variável para cada caractere, onde os mais frequentes recebem códigos menores.

Como fonte foi utilizado a bibliografia recomendada na ementa do curso:
 P. Deitel and H. Deitel, C++ How to Program, 10th Edition, Prentice Hall, 2016

 Ela foi fundamental para conseguir implementar a lógica da árvore de Huffman

 Recomendações de compilação do trabalho. Rode no terminal:

 1. g++ -o huffman main.cpp Huffman.cpp
 2. ./huffman c teste.txt teste_comprimido.huf
 3. ./huffman d teste_comprimido.huf teste_descomprimido.txt
 4. diff teste.txt teste_descomprimido.txt