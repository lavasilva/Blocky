#ifndef TETROMINO_H
#define TETROMINO_H

// Definindo o tamanho máximo de um tetromino (4x4)
#define TETROMINO_SIZE 4

// Definindo as formas dos tetrominos como matrizes de 4x4
extern int tetrominos[7][TETROMINO_SIZE][TETROMINO_SIZE];

// Funções para manipulação dos tetrominos
void inicializarTetrominos();
void rotacionarTetromino(int tetromino[TETROMINO_SIZE][TETROMINO_SIZE]);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "tetromino.h"

// Definindo as formas dos tetrominos
int tetrominos[7][TETROMINO_SIZE][TETROMINO_SIZE];

// Função para inicializar os tetrominos
void inicializarTetrominos() {
    // Forma do "I" (4 blocos em linha)
    tetrominos[0][0][0] = 1; tetrominos[0][1][0] = 1; tetrominos[0][2][0] = 1; tetrominos[0][3][0] = 1;
    tetrominos[0][0][1] = 0; tetrominos[0][1][1] = 0; tetrominos[0][2][1] = 0; tetrominos[0][3][1] = 0;
    tetrominos[0][0][2] = 0; tetrominos[0][1][2] = 0; tetrominos[0][2][2] = 0; tetrominos[0][3][2] = 0;
    tetrominos[0][0][3] = 0; tetrominos[0][1][3] = 0; tetrominos[0][2][3] = 0; tetrominos[0][3][3] = 0;

    // Forma do "O" (quadrado 2x2)
    tetrominos[1][0][0] = 1; tetrominos[1][1][0] = 1; 
    tetrominos[1][0][1] = 1; tetrominos[1][1][1] = 1;

    // Forma do "T"
    tetrominos[2][0][1] = 1; tetrominos[2][1][0] = 1; tetrominos[2][1][1] = 1; tetrominos[2][2][1] = 1;

    // Forma do "L"
    tetrominos[3][0][1] = 1; tetrominos[3][1][1] = 1; tetrominos[3][2][1] = 1; tetrominos[3][2][0] = 1;

    // Forma do "J"
    tetrominos[4][0][1] = 1; tetrominos[4][1][1] = 1; tetrominos[4][2][1] = 1; tetrominos[4][2][2] = 1;

    // Forma do "S"
    tetrominos[5][0][1] = 1; tetrominos[5][1][1] = 1; tetrominos[5][1][0] = 1; tetrominos[5][2][0] = 1;

    // Forma do "Z"
    tetrominos[6][0][0] = 1; tetrominos[6][1][0] = 1; tetrominos[6][1][1] = 1; tetrominos[6][2][1] = 1;
}

// Função para rotacionar um tetromino 90 graus no sentido horário
void rotacionarTetromino(int tetromino[TETROMINO_SIZE][TETROMINO_SIZE]) {
    int temp[TETROMINO_SIZE][TETROMINO_SIZE];

    // Realiza a rotação (transposta + inversão das colunas)
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            temp[i][j] = tetromino[TETROMINO_SIZE - 1 - j][i];
        }
    }

    // Copia o resultado de volta para o tetromino original
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            tetromino[i][j] = temp[i][j];
        }
    }
}
