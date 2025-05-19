#include "Game.h"
#include "Snake.h"

Game::Game(int linha, int coluna, int snakeSize){
    screen = new Screen(linha, coluna);
    snake = new Snake(snakeSize);
    numFoodAtivas = 0;
}

Game::~Game(){
    delete screen;
    delete snake;
}

Screen Game::getScreen() const{
    return *screen;
}

int Game::getNumFood() const{
    return numFoodAtivas;
}

bool Game::step(int dr, int dc) {
    int currDr = snake->getDr();
    int currDc = snake->getDc();

    if (dr == -currDr && dc == -currDc) {
        dr = currDr;
        dc = currDc;
    }

    int headRow = snake->getHeadRow();
    int headCol = snake->getHeadCol();

    int newRow = headRow + dr;
    int newCol = headCol + dc;

    if (newRow < 0 || newRow >= screen->getHeight() || newCol < 0 || newCol >= screen->getWidth())
        return false;

    if (screen->get(newRow, newCol) == screen->SNAKE || screen->get(newRow, newCol) == screen->WALL)
        return false;

    bool comeu = false;
    for (int i = 0; i < numFoodAtivas; i++) {
        if (food[i].foodRow == newRow && food[i].foodCol == newCol) {
            comeu = true;
            screen->set(newRow, newCol, screen->EMPTY);

            for (int j = i; j < numFoodAtivas - 1; j++)
                food[j] = food[j + 1];
            numFoodAtivas--;

            break;
        }
    }
    if (!comeu) {
        int tailRow = snake->getRow(snake->getSize() - 1);
        int tailCol = snake->getCol(snake->getSize() - 1);
        screen->set(tailRow, tailCol, screen->EMPTY);
    }

    snake->move(dr, dc, comeu);

    int newHeadRow = snake->getRow(0);
    int newHeadCol = snake->getCol(0);
    screen->set(newHeadRow, newHeadCol, screen->SNAKE);

    for (int i = 0; i < numFoodAtivas; ) {
        food[i].ttl--;
        if (food[i].ttl <= 0) {
            screen->set(food[i].foodRow, food[i].foodCol, screen->EMPTY);
            for (int j = i; j < numFoodAtivas - 1; j++)
                food[j] = food[j + 1];
            numFoodAtivas--;
        } else {
            i++;
        }
    }

    for (int i = 0; i < numFoodAtivas; i++) {
        screen->set(food[i].foodRow, food[i].foodCol, screen->FOOD);
    }

    return true;
}

void Game::addFood(int r, int c, int ttl) {
    if (r < 0 || r >= screen->getHeight() || c < 0 || c >= screen->getWidth())
        return;

    if (screen->get(r, c) != screen->EMPTY)
        return;

    screen->set(r, c, screen->FOOD);

    if (numFoodAtivas < 10) {
        food[numFoodAtivas].foodRow = r;
        food[numFoodAtivas].foodCol = c;
        food[numFoodAtivas].ttl = ttl;
        numFoodAtivas++;
    }
}


