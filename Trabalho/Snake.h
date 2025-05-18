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
    int length =0;;

public:
    /*OK*/ Snake (int len);
    /*OK*/ ~Snake();

    /*OK*/ void draw(Screen& s, int state);
    /*OK*/ void move(int dr, int dc, bool eating);
    /*OK*/ int getLength() const;
};

#endif