#include "Snake.h"
#include "Screen.h"
#include <iostream>
#include <exception>

//----------- constutor
Snake::Snake(int len)
    : head(nullptr), tail(nullptr), length(len)
{ 
    //perceba que a cobra comeca sempre na cauda: calda -> no -> no -> no -> cabeca

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


void Snake::draw(Screen& s, int state){
  
}