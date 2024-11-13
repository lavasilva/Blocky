#include "screen.h"
#include "timer.h"
#include "keyboard.h"
#include <stdlib.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 20
#define BLOCK_SIZE 2

// Definição das formas das peças com rotações possíveis
char tetrominos[7][4][4][4] = {
    { // I
        { {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} },
        { {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} }
    },
    { // O
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }
    },
    { // T
        { {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} }
    },
    { // S
        { {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} }
    },
    { // Z
        { {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0} }
    },
    { // L
        { {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0} },
        { {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0} }
    },
    { // J
        { {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0} },
        { {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} },
        { {1, 1, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0} }
    }
};

// Estado do tabuleiro
int board[WIDTH][HEIGHT];

// Estrutura para representar uma peça
typedef struct {
    int x, y;
    int type;
    int rotation;
} Piece;

Piece currentPiece;

void drawBoard() {
    screenClear();
    screenSetColor(CYAN, BLACK);
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (board[i][j]) {
                screenGotoxy(SCRSTARTX + i * BLOCK_SIZE, SCRSTARTY + j);
                printf("[]");
            }
        }
    }
}

void drawPiece(Piece *p) {
    screenSetColor(RED, BLACK);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[p->type][p->rotation][i][j]) {
                screenGotoxy(SCRSTARTX + (p->x + i) * BLOCK_SIZE, SCRSTARTY + p->y + j);
                printf("[]");
            }
        }
    }
}

int checkCollision(Piece *p) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[p->type][p->rotation][i][j]) {
                int x = p->x + i;
                int y = p->y + j;
                if (x < 0 || x >= WIDTH || y >= HEIGHT || board[x][y]) return 1;
            }
        }
    }
    return 0;
}

void placePiece(Piece *p) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetrominos[p->type][p->rotation][i][j]) {
                int x = p->x + i;
                int y = p->y + j;
                if (y < HEIGHT) board[x][y] = 1;
            }
        }
    }
}

void rotatePiece(Piece *p) {
    int prevRotation = p->rotation;
    p->rotation = (p->rotation + 1) % 4;
    if (checkCollision(p)) {
        p->rotation = prevRotation;
    }
}

void moveLeft(Piece *p) {
    p->x--;
    if (checkCollision(p)) p->x++;
}

void moveRight(Piece *p) {
    p->x++;
    if (checkCollision(p)) p->x--;
}

void moveDown(Piece *p) {
    p->y++;
    if (checkCollision(p)) {
        p->y--;
        placePiece(p);
        // Geração da próxima peça
        currentPiece.x = WIDTH / 2 - 2;
        currentPiece.y = 0;
        currentPiece.type = rand() % 7;
        currentPiece.rotation = 0;
    }
}

void screenDrawBorders() {
    screenSetColor(WHITE, BLACK);
    for (int i = 0; i < WIDTH + 2; i++) {
        screenGotoxy(SCRSTARTX + i * BLOCK_SIZE, SCRSTARTY - 1);
        printf("[]");
        screenGotoxy(SCRSTARTX + i * BLOCK_SIZE, SCRSTARTY + HEIGHT);
        printf("[]");
    }
    for (int i = 0; i < HEIGHT + 2; i++) {
        screenGotoxy(SCRSTARTX - 1, SCRSTARTY + i);
        printf("[]");
        screenGotoxy(SCRSTARTX + WIDTH * BLOCK_SIZE, SCRSTARTY + i);
        printf("[]");
    }
}

int main() {
    srand(time(NULL));
    screenInit();

    currentPiece.x = WIDTH / 2 - 2;
    currentPiece.y = 0;
    currentPiece.type = rand() % 7;
    currentPiece.rotation = 0;

    while (1) {
        drawBoard();
        drawPiece(&currentPiece);
        screenDrawBorders();

        if (keyPressed()) {
            char key = getKey();
            if (key == 'a') moveLeft(&currentPiece);
            if (key == 'd') moveRight(&currentPiece);
            if (key == 's') moveDown(&currentPiece);
            if (key == 'w') rotatePiece(&currentPiece);
        }

        screenFlush();
        usleep(100000); // Delay
    }

    return 0;
}
