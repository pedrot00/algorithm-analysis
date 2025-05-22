#include <iostream>
#include <stdexcept>
#include "Screen.h"

//----------- constutor
Screen::Screen(int width, int height)
    : largura(width), altura(height)
{
    if(width <= 0 || height <= 0)
        throw std::invalid_argument("Dimensões não positivas.");

    data = new int* [largura]();        // array de ponteiros para colunas
    dataHeight = new int [largura]();   // altura atual de cada coluna

    for(int i = 0; i < largura; i++){
        data[i] = nullptr;
        dataHeight[i] = 0;
    }
}

Screen::~Screen(){
    for(int i = 0; i < largura; i++)  // desaloca colunas
        delete[] data[i];

    delete[] data;
    delete[] dataHeight;
}


//----------- getters
int Screen::getWidth() const {
    return largura;
}

int Screen::getHeight() const {
    return altura;
}

// r = linha, c = coluna
int Screen::get(int r, int c) const {      
    if(r < 0 || r >= altura ||c < 0 || c >= largura)  return WALL;   //valor acessador fora da matriz retorna WALL = 3
    if(r >= dataHeight[c] || dataHeight[c] == 0) return EMPTY;

    return data[c][r];  //primeiro coluna depois linha, proposital
}

//----------- setters
void Screen::set(int r, int c, int val) {
    if (c < 0 || c >= largura) return;          //col invalido (nao eh necessario caso de teste/talvez apagar)
    if (r < 0) return;                          //lin invalido (nao eh necessario caso de teste/talvez apagar)

            
    if (data[c] == nullptr) {                   //coluna vazia cria array
        data[c] = new int[r + 1];
        for (int i = 0; i <= r; i++)
            data[c][i] = EMPTY;                 //comeca tudo EMPTY
        dataHeight[c] = r + 1;
    }
    
    else if (r >= dataHeight[c]) {              //caso necessario expandir col
        int* novaColuna = new int[r + 1];
        for (int i = 0; i < dataHeight[c]; i++)
            novaColuna[i] = data[c][i];
        for (int i = dataHeight[c]; i <= r; i++)
            novaColuna[i] = EMPTY;

        delete[] data[c];
        data[c] = novaColuna;
        dataHeight[c] = r + 1;
    }
    data[c][r] = val;                          //atribui valor no final
}
