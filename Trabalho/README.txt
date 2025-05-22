Eu li as regras.

Autor: Pedro Santos Teixeira - Matrícula: 116224 - INF213

## PROJETO JOGO DA COBRINHA


Este projeto implementa o clássico jogo da cobrinha utilizando a linguagem C++.
A cobra é representada por uma lista encadeada simples e o jogo é exibido em um terminal utilizando uma interface de tela personalizada.
(NOTA: Ao elaborar o jogo foi necessário a criação de métodos/atributos auxiliares (getters na classe Snake e prevRow/Col na classe Game) eles foram essenciais para permitir um bom funcionamento da classe Game, espero que esse motivo seja justificável dado os requisitos do sistema.)

## FUNCIONALIDADES
- Movimento da cobrinha com base em direção (linha, coluna).
- Detecção de colisão com paredes e com o próprio corpo.
- Crescimento da cobra ao comer alimentos.
- Gerenciamento de alimentos com tempo de vida (TTL).
- Interface de tela via classe Screen.
- Exibição dinâmica da cobra, alimentos e parede.
- Validação dos movimentos da cobra e retorno de posições.

## FONTES CONSULTADAS
Nenhuma. Todo o projeto foi desenvolvido de forma independente.

## OBSERVAÇÕES
- O jogo não possui interface gráfica, sendo exibido apenas em terminal.
- Os alimentos desaparecem após um tempo, mesmo que não sejam consumidos.
- A cobra não pode colidir com a própria cauda no mesmo instante em que ela está se movendo, permitindo virar sobre si mesma em alguns casos, como esperado.

## ESTRUTURA DO CÓDIGO
- `main.cpp` — Função principal do jogo.
- `Game.cpp / Game.h` — Lógica principal do jogo.
- `Snake.cpp / Snake.h` — Representação e movimentação da cobra.
- `Screen.cpp / Screen.h` — Representação da "tela" onde o jogo é desenhado.
