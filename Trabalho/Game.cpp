#include "Game.h"
#include <iostream>

Game::Game(int linha, int coluna, int snakeSize) {
    screen = new Screen(coluna, linha);  // linha = altura, coluna = largura
    snake = new Snake(snakeSize);
    snake->draw(*screen, Screen::SNAKE);

    food = new int*[10];  // maximo de 10 comidas
    for (int i = 0; i < 10; i++) {
        food[i] = new int[3];  // [ttl, row, col]
    }
    numFoodAtivas = 0;

    prevRow = snake->getHeadRow(); 
    prevCol = snake->getHeadCol(); 
}

Game::~Game() {
    delete screen;
    delete snake;
    for (int i = 0; i < 10; i++) {
        delete[] food[i];
    }
    delete[] food;

    screen = nullptr;
    snake = nullptr;
    food = nullptr;
    numFoodAtivas = 0;
}

void Game::addFood(int r, int c, int ttl) {
    if (screen->get(r, c) != Screen::EMPTY) return;

    if (numFoodAtivas < 10) {
        food[10 - numFoodAtivas - 1][0] = ttl + 1;
        food[10 - numFoodAtivas - 1][1] = r;
        food[10 - numFoodAtivas - 1][2] = c;

        numFoodAtivas++; 
        screen->set(r, c, Screen::FOOD);
    }
}

void Game::removeFood(int r, int c) {
    for (int i = 10 - numFoodAtivas; i < 10; ++i) {
        if (food[i][1] == r && food[i][2] == c) {
            food[i][0] = food[10 - numFoodAtivas][0];
            food[i][1] = food[10 - numFoodAtivas][1];
            food[i][2] = food[10 - numFoodAtivas][2];

            numFoodAtivas--;  
            screen->set(r, c, Screen::EMPTY);
            break;
        }
    }
}

bool Game::step(int dr, int dc) {
    int headRow = snake->getHeadRow();
    int headCol = snake->getHeadCol();

    if (dr == -1 * (headRow - prevRow) && dc == -1 * (headCol - prevCol)) {
        dr = headRow - prevRow;
        dc = headCol - prevCol;
    }

    int newRow = headRow + dr;
    int newCol = headCol + dc;

    int elemento = screen->get(newRow, newCol);

    if (elemento == Screen::WALL) return false;

    if (elemento == Screen::SNAKE) {
        int tailRow = snake->getTailRow();
        int tailCol = snake->getTailCol();
        if (newRow != tailRow || newCol != tailCol) return false;
    }

    bool comeu = (elemento == Screen::FOOD);
    if (comeu) {
        removeFood(newRow, newCol);  
    }
    snake->draw(*screen, Screen::EMPTY);
    snake->move(dr, dc, comeu);
    snake->draw(*screen, Screen::SNAKE);

    for (int i = 10 - numFoodAtivas; i < 10; i++) {
        if (food[i][0] > 0) {
            food[i][0]--;
            if (food[i][0] == 0) {
                screen->set(food[i][1], food[i][2], Screen::EMPTY);
            }
        }
    }
    int pos = 10 - numFoodAtivas;
    while (numFoodAtivas > 0 && pos < 10 && food[pos][0] == 0) {
        pos++;
        numFoodAtivas--;
    }

    prevRow = headRow;
    prevCol = headCol;

    return true;
}