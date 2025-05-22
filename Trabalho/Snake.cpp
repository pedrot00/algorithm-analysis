#include "Snake.h"
#include <stdexcept>

Snake::Snake(int len)
    : head(nullptr), tail(nullptr), snakeSize(len)
{
    if (len < 1)                    
        throw std::invalid_argument("Comprimento da cobra deve ser >= 1");

    tail = new Node(0, 0);          //primeiro node = cauda
    Node* current = tail;

    for (int c = 1; c < len; ++c) { //cria resto da cobra em linha
        Node* newNode = new Node(0, c);
        current->next = newNode;
        current = newNode;
    }
    head = current;                 //utimo node criado = cabeça
}

//liberacao para evitar leak
Snake::~Snake() {
    Node* current = tail;
    while (current) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

//desenha cobra inteira no screen com estado especificado
void Snake::draw(Screen& s, int state) {
    Node* current = tail;
    while (current) {
        s.set(current->row, current->col, state);
        current = current->next;
    }
}

//movimenta cobra na direção (dr,dc)
void Snake::move(int dr, int dc, bool eating) {
    int newRow = head->row + dr;
    int newCol = head->col + dc;

    if (eating) {                       // comeu-> cria nova cabeça (cobra cresce)
        Node* newHead = new Node(newRow, newCol);
        newHead->next = nullptr;
        head->next = newHead;
        head = newHead;
        snakeSize++;
    } else {
        
        if (tail == head) {             // cobra de tamanho 1 - caso especial (importante)
            head->row = newRow;
            head->col = newCol;
            return;
        }
        
        //n comeu-> reutiliza cauda como nova cabeça
        Node* oldTail = tail;
        tail = tail->next;          //nova cauda = próximo node
        
        oldTail->row = newRow;      //reposiciona antiga cauda
        oldTail->col = newCol;
        oldTail->next = nullptr;
        
        head->next = oldTail;       //conecta como nova cabeça
        head = oldTail;
    }
}

//getters simples
int Snake::getLength() const { return snakeSize; }
int Snake::getHeadRow() const { return head->row; }
int Snake::getHeadCol() const { return head->col; }
int Snake::getTailRow() const { return tail->row; }
int Snake::getTailCol() const { return tail->col; }

//retorna posição do i-esimo segmento 
int Snake::getRow(int i) const {
    Node* current = tail;
    int count = 0;
    while (current && count < i) {
        current = current->next;
        ++count;
    }
    return current ? current->row : -1;     // -1 se índice inválido (talvez seja legal verificar pra debug)
}

int Snake::getCol(int i) const {
    Node* current = tail;
    int count = 0;
    while (current && count < i) {
        current = current->next;
        ++count;
    }
    return current ? current->col : -1;     // -1 se índice inválido
}

//retorna dir atual da cobra
int Snake::getDr() const {
    if (!head || !head->next) return 0;     //p cobra muito pequena
    return head->row - head->next->row;
}

int Snake::getDc() const {
    if (!head || !head->next) return 0;     //p cobra muito pequena  
    return head->col - head->next->col;
}