#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Screen.h"

class Game {
private:
    Snake* snake;
    Screen* screen;
    int** food;         //[ttl, row, col] - mais facil armazenar toda a estrutura de food de uma vez -> struct funcionaria tmb
    int numFoodAtivas;  //var q controla as comidas ativas no mapa

    int prevRow;  //auxiliares
    int prevCol;  

public:
    Game(int linha, int coluna, int snakeSize);
    ~Game();

    Screen& getScreen() { return *screen; }
    int getNumFood() const { return numFoodAtivas; }

    void addFood(int r, int c, int ttl);
    void removeFood(int r, int c);
    bool step(int dr, int dc);
};

#endif
