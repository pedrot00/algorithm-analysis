#include "Huffman.h"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
    // verifica se foram passados exatamente 3 argumentos alem do nome do programa
    if(argc != 4) {
        cerr << "uso: " << argv[0] << " <c|d> <entrada> <saida>" << endl;   //ajuda se saida indevida
        return 1;
    }

    // extrai argumentos da linha de comando
    string op = argv[1];    // operacao comprimir ou descomprimir
    string in = argv[2];    // arquivo de entrada
    string out = argv[3];   // arquivo de saida

    // branch de compressao
    if(op == "c" || op == "comprimir") {
        // abre arquivo de entrada em modo binario
        ifstream fin(in, ios::binary);
        if(!fin) {
            cerr << "erro ao abrir arquivo: " << in << endl;
            return 1;
        }

        MyVec<char> dados;
        int freq[256] = {0};  // tabela de frequencias inicializada com zeros
        
        // achei interessante calcular tamanho antes de ler, talvez otimize melhor
        fin.seekg(0, ios::end);
        size_t fileSize = fin.tellg();
        fin.seekg(0, ios::beg);
        
        // verifica se arquivo nao esta vazio
        if(fileSize == 0) {
            cerr << "arquivo vazio!" << endl;
            return 1;
        }
        
        // le todo o arquivo de uma vez para melhor performance
        dados.resize(fileSize);
        fin.read(&dados[0], fileSize);
        fin.close();
        
        // conta frequencia de cada caracter
        for(size_t i = 0; i < dados.size(); i++) {
            freq[(unsigned char)dados[i]]++;
        }

        // constroi arvore de huffman e comprime dados
        HuffManTree huff(freq);
        MyVec<bool> bits;
        huff.comprimir(bits, dados);

        // cria arquivo de saida
        ofstream fout(out, ios::binary);
        if(!fout) {
            cerr << "erro ao criar arquivo: " << out << endl;
            return 1;
        }

        // escreve tabela de freqs no inicio do arquivo
        //  necessario para poder reconstruir arvore na descompressao
        fout.write(reinterpret_cast<char*>(freq), sizeof(freq));
        
        // escreve num  bits para saber exatamente quantos bits ler
        int num_bits = bits.size();
        fout.write(reinterpret_cast<char*>(&num_bits), sizeof(num_bits));

        unsigned char byte_atual = 0;     // converte bits para bytes para armazenamento
        int bit_pos = 0;
        
        for(size_t i = 0; i < bits.size(); i++) {
            if(bits[i]) {
                byte_atual |= (1 << (7 - bit_pos));  // setta bit na posicao correta
            }
            bit_pos++;
            
            // quando completa um byte escreve no arquivo
            if(bit_pos == 8) {
                fout.put(byte_atual);
                byte_atual = 0;
                bit_pos = 0;
            }
        }
        
        // escreve ultimo byte parcial (se necessario)
        if(bit_pos > 0) {
            fout.put(byte_atual);
        }
        
        fout.close();
        
        // exibe estatisticas de compress
        cout << "Arquivo comprimido com sucesso!" << endl;
        cout << "Tamanho original: " << dados.size() << " bytes" << endl;
        cout << "Tamanho comprimido: " << (bits.size() + 7) / 8 + sizeof(freq) + sizeof(num_bits) << " bytes" << endl;
    }
    // branch de descompressao
    else if(op == "d" || op == "descomprimir") {
        // abre arquivo comprimido
        ifstream fin(in, ios::binary);
        if(!fin) {
            cerr << "erro ao abrir arquivo: " << in << endl;
            return 1;
        }

        // le tabela de frequencias para reconstruir arvore
        int freq[256];
        fin.read(reinterpret_cast<char*>(freq), sizeof(freq));
        
        // le num  bits que foram armazenados
        int num_bits;
        fin.read(reinterpret_cast<char*>(&num_bits), sizeof(num_bits));

        // valida se num de bits e valido
        if(num_bits <= 0) {
            cerr << "Arquivo comprimido invalido!" << endl;
            return 1;
        }

        // le bytes e converte de volta para bits
        MyVec<bool> bits;
        bits.reserve(num_bits);  // otimizacao para evitar realocacoes
        
        unsigned char byte;
        int bits_lidos = 0;
        
        // le byte por byte e extrai bits individuais
        while(bits_lidos < num_bits && fin.read(reinterpret_cast<char*>(&byte), 1)) {
            // extrai bits do byte da esquerda para direita
            for(int i = 7; i >= 0 && bits_lidos < num_bits; i--) {
                bits.push_back((byte >> i) & 1);
                bits_lidos++;
            }
        }
        fin.close();

        // verifica se conseguiu ler todos os bits esperados
        if(bits_lidos != num_bits) {
            cerr << "Erro: nao foi possivel ler todos os bits do arquivo!" << endl;
            return 1;
        }

        // reconstroi arvore e descomprime dados
        HuffManTree huff(freq);
        MyVec<char> dados;
        huff.descomprimir(dados, bits);

        // escreve dados descomprimidos
        ofstream fout(out, ios::binary);
        if(!fout) {
            cerr << "erro ao criar arquivo: " << out << endl;
            return 1;
        }
        
        // achei necessario verificar se ha dados antes de escrever
        if(dados.size() > 0) {
            fout.write(&dados[0], dados.size());
        }
        fout.close();
        
        cout << "Arquivo descomprimido com sucesso!" << endl;
        cout << "Tamanho descomprimido: " << dados.size() << " bytes" << endl;
    }
    else {
        cerr << "opcao invalida! use 'c' ou 'd'" << endl;
        return 1;
    }
    
    return 0;
}