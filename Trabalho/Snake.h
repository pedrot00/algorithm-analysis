#ifndef SNAKE_H
#define SNAKE_H
#include "Screen.h"


class Snake{
private:
    struct Node {
        int row, col;
        Node* next;
        Node(int r, int c): row(r), col(c), next(nullptr){}
    };
    Node* head;
    Node* tail;
    int length;

public:
    /*OK*/ Snake (int len);
    /*OK*/ ~Snake();

    void draw(Screen& s, int state);
    void move(int dr, int dc, bool eating);
    int getLength() const;
};

#endif