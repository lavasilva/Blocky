#include "screen.h"

// Função para desenhar as bordas do jogo com dimensões variáveis
void screenDrawBorders(int linhas, int colunas) {
    char hbc = BOX_HLINE;
    char vbc = BOX_VLINE;

    screenClear();
    screenBoxEnable();
    
    // Desenhar a borda superior
    screenGotoxy(MINX, MINY);
    printf("%c", BOX_UPLEFT);
    for (int i = MINX + 1; i < colunas; i++) {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }
    screenGotoxy(colunas, MINY);
    printf("%c", BOX_UPRIGHT);

    // Desenhar as laterais
    for (int i = MINY + 1; i < linhas; i++) {
        screenGotoxy(MINX, i);
        printf("%c", vbc);
        screenGotoxy(colunas, i);
        printf("%c", vbc);
    }

    // Desenhar a borda inferior
    screenGotoxy(MINX, linhas);
    printf("%c", BOX_DWNLEFT);
    for (int i = MINX + 1; i < colunas; i++) {
        screenGotoxy(i, linhas);
        printf("%c", hbc);
    }
    screenGotoxy(colunas, linhas);
    printf("%c", BOX_DWNRIGHT);
    
    screenBoxDisable();
}

// Função para desenhar o tabuleiro do jogo
void screenDrawTabuleiro(int tabuleiro[][COLUNAS], int linhas, int colunas) {
    for (int y = 0; y < linhas; y++) {
        for (int x = 0; x < colunas; x++) {
            screenGotoxy(x + MINX, y + MINY);
            if (tabuleiro[y][x]) {
                printf("%c", BOX_BLOCK);
            } else {
                printf(" ");
            }
        }
    }
}

// Função para desenhar a peça na posição especificada
void screenDrawPiece(Peca pecaAtual, int x, int y) {
    for (int i = 0; i < pecaAtual.altura; i++) {
        for (int j = 0; j < pecaAtual.largura; j++) {
            if (pecaAtual.forma[i][j]) {
                screenGotoxy(x + j + MINX, y + i + MINY);
                printf("%c", BOX_BLOCK);
            }
        }
    }
}

// Função para renderizar a tela (atualiza o buffer do terminal)
void screenRender() {
    screenUpdate();
}

void screenInit(int drawBorders) {
    screenClear();
    if (drawBorders) {
        screenDrawBorders(MAXY, MAXX);
    }
    screenHomeCursor();
    screenHideCursor();
}

void screenDestroy() {
    printf("%s[0;39;49m", ESC); // Reset colors
    screenSetNormal();
    screenClear();
    screenHomeCursor();
    screenShowCursor();
}

void screenGotoxy(int x, int y) {
    x = (x < 0 ? 0 : x >= MAXX ? MAXX - 1 : x);
    y = (y < 0 ? 0 : y > MAXY ? MAXY : y);
    printf("%s[%d;%df", ESC, y + 1, x + 1);
}

void screenSetColor(screenColor fg, screenColor bg) {
    char atr[] = "[0;";
    if (fg > LIGHTGRAY) {
        atr[1] = '1';
        fg -= 8;
    }
    printf("%s%s%d;%dm", ESC, atr, fg + 30, bg + 40);
}
