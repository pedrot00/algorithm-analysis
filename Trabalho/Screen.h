#ifndef SCREEN_H
#define SCREEN_H

class Screen{
private:
    int largura;
    int altura;

    int** data;
    int* dataHeight; 
public:
    const static int EMPTY = 0, SNAKE = 1, FOOD = 2, WALL = 3;

    int getWidth() const;
    int getHeight() const;
    Screen(int width, int heigth);  
    ~Screen();  
    int get(int r, int c) const;          //retorna estado “pixel”  lin r, col c da tela
    void set (int r, int c, int val);     //guarda em lin r, col c o estado val ( FOOD, SNAKE, EMPTY, WALL)
    
};

#endif
