#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>        // Inclui o cabeçalho para a função time()
#include "screen.h"
#include "timer.h"
#include "keyboard.h"

#define LINHAS 20
#define COLUNAS 10

int tetrominos[7][4][4] = {
    {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
    {{1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // T
    {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // O
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // S
    {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // Z
    {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // J
    {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}  // L
};

int tabuleiro[LINHAS][COLUNAS] = {0};  // Inicializa o tabuleiro com 0s
Peca peçaAtual;  // A peça que está caindo, declarada como Peca
int x, y;

void exibirTelaInicial() {
    system("clear");
    printf("########################### #################################\n");
    printf("████████╗███████╗████████╗██████╗░██╗░███████╗\n ");
    printf("╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝\n ");
    printf("░░░██║░░░█████╗░░░░░██║░░░██████╔╝██║╚█████╗░\n ");
    printf("░░░██║░░░██╔══╝░░░░░██║░░░██╔══██╗██║░╚═══██╗\n ");
    printf("░░░██║░░░███████╗░░░██║░░░██║░░██║░░██║██║██║█████╔╝\n ");
    printf("░░░╚═╝░░░╚══════╝░░░╚═╝░░░╚═╝░░╚═╝╚═ ════╝░\n ");
    printf("######################################## #############\n");
    printf("\nPrepare-se para uma partida emocionante de TETRIS!\n");
    printf("Pressione ENTER...\n");

    getchar();
}

void exibirInstrucoes() {
    system("clear");
    printf("############################################################\n");
    printf("#                                                          #\n");
    printf("#                   INSTRUÇÕES DO TETRIS                   #\n");
    printf("#                                                          #\n");
    printf("############################################################\n");
    printf("#                                                          #\n");
    printf("#  Como jogar:                                             #\n");
    printf("#  - Use as teclas de setas para controlar as peças:       #\n");
    printf("#    -> Seta para ESQUERDA  : Move a peça para a esquerda  #\n");
    printf("#    -> Seta para DIREITA   : Move a peça para a direita   #\n");
    printf("#    -> Seta para BAIXO     : Acelera a descida da peça    #\n");
    printf("#    -> Tecla ESPAÇO        : Gira a peça                  #\n");
    printf("#                                                          #\n");
    printf("#  Objetivo:                                               #\n");
    printf("#  - Complete linhas horizontais para ganhar pontos e      #\n");
    printf("#    limpar as linhas.                                     #\n");
    printf("#  - O jogo acaba se as peças chegarem ao topo.            #\n");
    printf("#                                                          #\n");
    printf("#  Pressione ENTER para começar o jogo!                    #\n");
    printf("#                                                          #\n");
    printf("############################################################\n");
    getchar();
}

void inicializarPeça() {
    int tipo = rand() % 7;
    peçaAtual.altura = 4;
    peçaAtual.largura = 4;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            peçaAtual.forma[i][j] = tetrominos[tipo][i][j];
        }
    }
    x = COLUNAS / 2 - 2;
    y = 0;
}

int verificarColisao() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (peçaAtual.forma[i][j]) {
                if (y + i >= LINHAS || x + j < 0 || x + j >= COLUNAS || tabuleiro[y + i][x + j]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void rotacionarPeça() {
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = peçaAtual.forma[3 - j][i];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (temp[i][j] && (y + i >= LINHAS || x + j < 0 || x + j >= COLUNAS || tabuleiro[y + i][x + j])) {
                return;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            peçaAtual.forma[i][j] = temp[i][j];
        }
    }
}

void atualizarTela() {
    screenClear();
    screenDrawBorders(LINHAS, COLUNAS);
    screenDrawTabuleiro(tabuleiro, LINHAS, COLUNAS);
    screenDrawPiece(peçaAtual, x, y);
    screenRender();
}

int main() {
    exibirTelaInicial();
    exibirInstrucoes();

    srand(time(NULL));
    inicializarPeça();

    while (1) {
        atualizarTela();
        if (keyboardHit()) {
            char tecla = keyboardRead();
            if (tecla == 'q') break;
            if (tecla == 'a') moverEsquerda();
            if (tecla == 'd') moverDireita();
            if (tecla == 's') moverAbaixo();
            if (tecla == 'w') rotacionarPeça();
        }
        sleep(1);
    }

    return 0;
}
