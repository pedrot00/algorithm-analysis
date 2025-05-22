#ifndef SNAKE_H
#define SNAKE_H

#include "Screen.h"

class Snake {
private:
    struct Node {
        int row, col;
        Node* next;
        Node(int r, int c) : row(r), col(c), next(nullptr) {}
    };
    Node* head;     // cabeca -> final da lista
    Node* tail;     // cauda ->  inicio da lista
    int snakeSize;  // ordem -> tail -> no -> no -> head

public:
    Snake(int len);
    ~Snake();

    void draw(Screen& s, int state);
    void move(int dr, int dc, bool eating);  // dr/dc = direcao, eating = true se comeu cresce

    //---- getter essenciais para encontrar pos de cada node em Game
    int getLength() const;
    int getRow(int i) const;
    int getCol(int i) const;
    
    int getHeadRow() const;
    int getHeadCol() const;
    int getTailRow() const;
    int getTailCol() const;

    int getDr() const;
    int getDc() const;
};

#endif
