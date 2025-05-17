#ifndef SCREEN_H
#define SCREEN_H

class Screen{
private:
    int largura;
    int altura;

    int** data;
    int* dataHeight; 
public:
    const int EMPTY = 0, SNAKE = 1, FOOD = 2, WALL = 3;

    /*OK*/ Screen(int width, int heigth);  
    /*OK*/ ~Screen();

    /*OK*/ int getLargura() const;
    /*OK*/ int getAltura() const;       //talvez possa ser excluidos se n forem usados
    /*OK*/ int get(int r, int c);                //retorna estado “pixel”  lin r, col c da tela
    /*OK*/ void set (int r, int c, int val);     //guarda em lin r, col c o estado val ( FOOD, SNAKE ou EMPTY)

};

#endif

