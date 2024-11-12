#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>

// Defina COLUNAS e LINHAS se não estiverem definidos em outro lugar
#define COLUNAS 10
#define LINHAS 20

struct Peca {
    int largura;          // Largura da peça
    int altura;           // Altura da peça
    int forma[4][4];      // Forma da peça (matriz 4x4)
};

// Terminal control sequences
#define ESC            "\033"
#define NORMALTEXT     "[0m"
#define BOLDTEXT       "[1m"
#define ITALICTEXT     "[3m"
#define BLINKTEXT      "[5m"
#define REVERSETEXT    "[7m"
#define HOMECURSOR     "[f"
#define SHOWCURSOR     "[?25h"
#define HIDECURSOR     "[?25l"
#define CLEARSCREEN    "[2J"

// BOX Drawing - Unix like terminals
#define BOX_ENABLE     "(0"
#define BOX_DISABLE    "(B"
#define BOX_VLINE      0x78
#define BOX_HLINE      0x71
#define BOX_UPLEFT     0x6C
#define BOX_UPRIGHT    0x6B
#define BOX_DWNLEFT    0x6D
#define BOX_DWNRIGHT   0x6A
#define BOX_CROSS      0x6E
#define BOX_TLEFT      0X74
#define BOX_TRIGHT     0X75
#define BOX_TUP        0X77
#define BOX_TDOWN      0X76
#define BOX_DIAMOND    0x60
#define BOX_BLOCK      0x61
#define BOX_DOT        0x7E

// Screen constants
#define MINX           1
#define MINY           1
#define MAXX           80
#define MAXY           24

typedef enum {BLACK, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN, LIGHTGRAY,
        DARKGRAY, LIGHTRED, LIGHTGREEN, YELLOW, LIGHTBLUE, 
        LIGHTMAGENTA, LIGHTCYAN, WHITE} screenColor; 

// Funções para o gerenciamento da tela
static inline void screenHomeCursor() {
    printf("%s%s", ESC, HOMECURSOR);
}

static inline void screenShowCursor() {
    printf("%s%s", ESC, SHOWCURSOR);
}

static inline void screenHideCursor() {
    printf("%s%s", ESC, HIDECURSOR);
}

static inline void screenClear() {
    screenHomeCursor();
    printf("%s%s", ESC, CLEARSCREEN);
}

static inline void screenUpdate() {
    fflush(stdout);
}

static inline void screenSetNormal() {
    printf("%s%s", ESC, NORMALTEXT);
}

void screenInit(int drawBorders);
void screenDestroy();
void screenGotoxy(int x, int y);
void screenSetColor(screenColor fg, screenColor bg);

// Funções específicas para o jogo Tetris
void screenDrawBorders(int linhas, int colunas);            // Função para desenhar as bordas do jogo
void screenDrawTabuleiro(int tabuleiro[][COLUNAS], int linhas, int colunas);  // Função para desenhar o tabuleiro do jogo
void screenDrawPiece(Peca pecaAtual, int x, int y);         // Função para desenhar a peça na posição especificada
void screenRender();                                        // Função para renderizar a tela

void screenBoxEnable();
void screenBoxDisable();

#endif /* __SCREEN_H__ */
