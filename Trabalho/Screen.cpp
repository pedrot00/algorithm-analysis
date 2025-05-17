#include <iostream>
#include <stdexcept>
#include "Screen.h"

///----------- constutor
Screen::Screen(int width, int heigth)
    :largura(width), altura(heigth)         //inicializa com altura e largura definida nos param
{
    if(width <= 0 || heigth <= 0)           //valida simples parametros
        throw std::invalid_argument("Dimensões não positivas.");
    
    data = new int* [altura]();             //setta matriz com val interno nullptr
    dataHeight = new int [largura]();       //setta dh com val interno 0

    for(int i = 0; i < altura; i++)         //cada i linhas tem largura colunas
        data[i] = new int [largura];
}   

///----------- destrutor
Screen::~Screen(){
    for(int i= 0; i < altura; i++)
        delete[] data[i];               //desaloca col matriz

    delete[] data;                      //desaloca lin matriz
    delete[] dataHeight;                //desaloca vetor dh
}

//----------- getters
int Screen::getLargura() const {
    return largura;
}

int Screen::getAltura() const {
    return altura;
}

// r = linha, c = coluna
int Screen::get(int r, int c){      
    if(r < 0 || r >= altura ||c < 0 || c >= largura) 
        return WALL;   //valor acessador fora da matriz retorna WALL = 3

    return data[r][c];
}

//----------- setters
void Screen::set(int r, int c, int val){
    data[r][c] = val;
}