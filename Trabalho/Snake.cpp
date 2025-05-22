#include "Snake.h"
#include <stdexcept>

Snake::Snake(int len)
    : head(nullptr), tail(nullptr), snakeSize(len)
{
    if (len < 1)                    
        throw std::invalid_argument("Comprimento da cobra deve ser >= 1");

    tail = new Node(0, 0);
    Node* current = tail;

    for (int c = 1; c < len; ++c) {
        Node* newNode = new Node(0, c);
        current->next = newNode;
        current = newNode;
    }
    head = current;
}

Snake::~Snake() {
    Node* current = tail;
    while (current) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

void Snake::draw(Screen& s, int state) {
    Node* current = tail;
    while (current) {
        s.set(current->row, current->col, state);
        current = current->next;
    }
}

void Snake::move(int dr, int dc, bool eating) {
    int newRow = head->row + dr;
    int newCol = head->col + dc;

    if (eating) {
        // criando cabeca
        Node* newHead = new Node(newRow, newCol);
        newHead->next = head;
        head = newHead;
        snakeSize++;
    } else {
        // reutilizando cauda como nova cabeca
        Node* oldTail = tail;
        tail = tail->next;

        oldTail->row = newRow;
        oldTail->col = newCol;
        oldTail->next = nullptr;

        head->next = oldTail;  
        head = oldTail;
    }
}

int Snake::getLength() const {
    return snakeSize;
}

int Snake::getHeadRow() const {
    return head->row;
}

int Snake::getHeadCol() const {
    return  head->col;
}

int Snake::getRow(int i) const {
    Node* current = tail;
    int count = 0;
    while (current && count < i) {
        current = current->next;
        ++count;
    }
    return current ? current->row : -1;
}

int Snake::getCol(int i) const {
    Node* current = tail;
    int count = 0;
    while (current && count < i) {
        current = current->next;
        ++count;
    }
    return current ? current->col : -1;
}

int Snake::getDr() const {
    if (!head || !head->next) return 0;
    return head->row - head->next->row;
}

int Snake::getDc() const {
    if (!head || !head->next) return 0;
    return head->col - head->next->col;
}
