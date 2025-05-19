#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Screen.h"

class Game{     
private:
    Snake* snake;              //cobra do jogo
    Screen* screen;            // estado atual tela do jogo (gerenciada pela class Game)

    struct Food{
        int foodRow;
        int foodCol;
        int ttl;
    };
    Food food[10];
    int numFoodAtivas=0 ;      //quantidade de comida ativa no mapa

public:
    /*OK*/ Game(int linha, int coluna, int snakeSize);
    /*OK*/ ~Game();

    /*OK*/ Screen getScreen() const;
    /*OK*/ int getNumFood() const;

    void addFood(int r,int c, int ttl);
    /*OK*/ bool step(int dr, int dc);
  
};

#endif