#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Screen.h"
#include <string.h>

class Game{
private:
    Snake snake;              //cobra do jogo
    Screen screen;           // estado atual tela do jogo (gerenciada pela class Game)
    int food [10];

public:
    Game(int altura, int largura, int snakeSize);

    Screen getScreen() const;
    int getNumFood() const;

    void addFood(int r,int c, int ttl);
    bool step(int dr, int dc);
  

};

#endif