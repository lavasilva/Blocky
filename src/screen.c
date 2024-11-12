#include "screen.h"

void screenDrawBorders() {
    char hbc = BOX_HLINE;
    char vbc = BOX_VLINE;

    screenClear();
    screenBoxEnable();
    
    // Desenhar a borda superior
    screenGotoxy(MINX, MINY);
    printf("%c", BOX_UPLEFT);
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }
    screenGotoxy(MAXX, MINY);
    printf("%c", BOX_UPRIGHT);

    // Desenhar as laterais
    for (int i = MINY + 1; i < MAXY; i++) {
        screenGotoxy(MINX, i);
        printf("%c", vbc);
        screenGotoxy(MAXX, i);
        printf("%c", vbc);
    }

    // Desenhar a borda inferior
    screenGotoxy(MINX, MAXY);
    printf("%c", BOX_DWNLEFT);
    for (int i = MINX + 1; i < MAXX; i++) {
        screenGotoxy(i, MAXY);
        printf("%c", hbc);
    }
    screenGotoxy(MAXX, MAXY);
    printf("%c", BOX_DWNRIGHT);
    
    screenBoxDisable();
}

void screenInit(int drawBorders) {
    screenClear();
    if (drawBorders) {
        screenDrawBorders();
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
