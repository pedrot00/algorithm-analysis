#include "Game.h"
#include <iostream>

Game::Game(int linha, int coluna, int snakeSize) {
    screen = new Screen(coluna, linha);     // linha = altura, coluna = largura
    snake = new Snake(snakeSize);
    snake->draw(*screen, Screen::SNAKE);    // desenha cobra inicial
    
    food = new int*[10];                    // max de 10 comidas ao mesmo tempo (talvez criar uma const)
    for (int i = 0; i < 10; i++) {
        food[i] = new int[3];               // [ttl, row, col] p cada comida
    }
    numFoodAtivas = 0;
    
    prevRow = snake->getHeadRow();          // guarda pos anterior
    prevCol = snake->getHeadCol();
}

Game::~Game() {
    delete screen;
    delete snake;
    for (int i = 0; i < 10; i++) {
        delete[] food[i];
    }
    delete[] food;
    screen = nullptr; snake = nullptr; food = nullptr;
    numFoodAtivas = 0;
}

//add comida na pos r/c com tempo de vida ttl
void Game::addFood(int r, int c, int ttl) {
    if (screen->get(r, c) != Screen::EMPTY) return;     // pos ocupada
    
    if (numFoodAtivas < 10) {                           // ainda tem espaco
        food[10 - numFoodAtivas - 1][0] = ttl + 1;      // armazena final da lista
        food[10 - numFoodAtivas - 1][1] = r;
        food[10 - numFoodAtivas - 1][2] = c;
        numFoodAtivas++;
        screen->set(r, c, Screen::FOOD);
    }
}

//remove comida específica da posição r/c
void Game::removeFood(int r, int c) {
    for (int i = 10 - numFoodAtivas; i < 10; ++i) {     // procura na lista ativa
        if (food[i][1] == r && food[i][2] == c) {       // substitui por último elemento ativo (compacta lista)
            food[i][0] = food[10 - numFoodAtivas][0];
            food[i][1] = food[10 - numFoodAtivas][1];
            food[i][2] = food[10 - numFoodAtivas][2];
            numFoodAtivas--;
            break;
        }
    }
}

//executa um passo do jogo na direção dr/dc
bool Game::step(int dr, int dc) {
    int headRow = snake->getHeadRow();
    int headCol = snake->getHeadCol();
    
    // impede movimento reverso -> cobra nn deve voltar sobre si
    if (dr == -1 * (headRow - prevRow) && dc == -1 * (headCol - prevCol)) {
        dr = headRow - prevRow;     // mantem dir correta
        dc = headCol - prevCol;
    }
    
    int newRow = headRow + dr;              // calcula nova pos da heada
    int newCol = headCol + dc;
    int elemento = screen->get(newRow, newCol);

    if (elemento == Screen::WALL) return false;         // caso colida parede

    if (elemento == Screen::SNAKE) {                    // caso colida corpo
        int tailRow = snake->getTailRow();
        int tailCol = snake->getTailCol();
      
        if (newRow != tailRow || newCol != tailCol) return false;  // so permite se for na cauda
    }
    
    bool comeu = (elemento == Screen::FOOD);
    
    //limpar -> mover -> desenhar -> processar comida
    snake->draw(*screen, Screen::EMPTY);    // apaga cobra atual
    snake->move(dr, dc, comeu);             // move cobra (cresce se comeu)
    snake->draw(*screen, Screen::SNAKE);    // desenha cobra na nova posição
    
    if (comeu) {
        removeFood(newRow, newCol);         //remove comida da estrutura
    }
    
    //processa ttl comidas ativas
    for (int i = 10 - numFoodAtivas; i < 10; i++) {
        if (food[i][0] > 0) {
            food[i][0]--;                   //decrementa da ttl
            if (food[i][0] == 0) {          //comida expirou
                screen->set(food[i][1], food[i][2], Screen::EMPTY);
            }
        }
    }
    //remove comidas expiradas da lista ativa
    int pos = 10 - numFoodAtivas;
    while (numFoodAtivas > 0 && pos < 10 && food[pos][0] == 0) { //(talvez precise ser melhor verificado)
        pos++;
        numFoodAtivas--;
    }
    
    prevRow = headRow;                      //atualiza pos anterior
    prevCol = headCol;
    
    return true;                            //movimento bem sucedido
}