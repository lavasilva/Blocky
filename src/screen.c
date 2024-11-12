#include "screen.h"

void screenDrawBorders() 
{
    char hbc = '-'; // Caractere para bordas horizontais
    char vbc = '|'; // Caractere para bordas verticais
    char corner = '+'; // Caractere para os cantos

    screenClear(); // Limpa a tela antes de desenhar
    screenBoxEnable();

    // Desenha o canto superior esquerdo
    screenGotoxy(MINX, MINY);
    printf("%c", corner);

    // Desenha a borda superior
    for (int i = MINX + 1; i < MAXX; i++) 
    {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }

    // Desenha o canto superior direito
    screenGotoxy(MAXX, MINY);
    printf("%c", corner);

    // Desenha as bordas laterais
    for (int i = MINY + 1; i < MAXY; i++) 
    {
        screenGotoxy(MINX, i);
        printf("%c", vbc);
        screenGotoxy(MAXX, i);
        printf("%c", vbc);
    }

    // Desenha o canto inferior esquerdo
    screenGotoxy(MINX, MAXY);
    printf("%c", corner);

    // Desenha a borda inferior
    for (int i = MINX + 1; i < MAXX; i++) 
    {
        screenGotoxy(i, MAXY);
        printf("%c", hbc);
    }

    // Desenha o canto inferior direito
    screenGotoxy(MAXX, MAXY);
    printf("%c", corner);

    screenBoxDisable();
}
