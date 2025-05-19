#include "Snake.h"
#include "Screen.h"
#include <iostream>
#include <exception>

//----------- constutor
Snake::Snake(int len)
    : head(nullptr), tail(nullptr), length(len)
{ 
    //perceba que a cobra comeca sempre na cauda: cauda -> no -> no -> no -> cabeca

    if (len < 1)                //validacao para possiveis casos de teste
    throw std::invalid_argument("Comprimento da cobra deve ser >= 1") ;

    tail = new Node(0,0);       //setta cauda sempre no pixel (0,0)
    Node* current = tail;

     for(int c=1; c<length; c++){
        Node* newNode = new Node(0,c);

        current->next = newNode;
        current = newNode;
    }
    head = current;             //setta cabeca sempre no pixel (0, len -1)
}

//----------- destrutor
Snake::~Snake(){
    Node* current = tail;

    while(current){                    //mesmo que current != nullptr
        Node* toDelete = current;
        current = current->next;
        delete toDelete;               //desaloca cada nodulo sem perder o proximo
    }
}

//setta pixels com const SNAKE onde cobra deveria estar 
void Snake::draw(Screen& s, int state){
   Node* current = tail;
   while(current){
        s.set(current->row, current->col, state);
        current = current->next;
   }
}

//length eh atributo fundamental p funcionalidade O(1) exigida
void Snake::move(int dr, int dc, bool eating) {
    int newRow = head->row + dr;
    int newCol = head->col + dc;

    if (eating) {
        Node* newHead = new Node(newRow,newCol);
        newHead->next = head;
        head = newHead;
        length++;
    } else {
        Node* oldTail = tail;
        tail = tail->next;

        oldTail->row = newRow;
        oldTail->col = newCol;
        oldTail->next = head;
        head = oldTail;
    }
}

int Snake::getSize() const{
    return length;
}
int Snake::getRow(int i) const {
    Node* current = head;
    int count = 0;
    while (current != nullptr && count < i) {
        current = current->next;
        count++;
    }
    if (current != nullptr) return current->row;
    return -1;
}

int Snake::getCol(int i) const {
    Node* current = head;
    int count = 0;
    while (current != nullptr && count < i) {
        current = current->next;
        count++;
    }
    if (current != nullptr) return current->col;
    return -1;
}

int Snake::getDr() const {
    if (head->next == nullptr) return 0; // Cobra tem um único nó, direção neutra
    return head->row - head->next->row;
}

int Snake::getDc() const {
    if (head->next == nullptr) return 0;
    return head->col - head->next->col;
}