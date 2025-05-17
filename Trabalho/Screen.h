#ifndef SCREEN_H
#define SCREEN_H

class Screen{
private:

public:
    const int FOOD;
    const int SNAKE;
    const int EMPTY;
    const int WALL;
   
private:
    int largura;
    int altura;

    int** data;
    int dataHeight[100];

    Screen(int largura, int altura);
    int get(int r, int c);
    void set (int r, int c, int val);
    
};

#endif

