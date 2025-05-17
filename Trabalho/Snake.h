#ifndef SNAKE_H
#define SNAKE_H

#include "Screen.h"


class Snake{
private:
    struct Node {
        int row, col;
        Node* next;
    };
    Node* head;
    Node* tail;
    int length;

public:
    Snake (int len);
    ~Snake();

    void draw(Screen& s, int state);
    void move(int dr, int dc, bool eating);
    int getLength() const;
};

#endif