#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para a função usleep()
#include "screen.h" // Inclui o cabeçalho do controle de tela
#include "timer.h"
#include "keyboard.h"

#define LINHAS 20
#define COLUNAS 10

// Definindo os sete tipos de peças (tetrominos)
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

void exibirTelaInicial() {
    screenClear(); // Limpa a tela
    printf("########################### #################################\n");
    printf("████████╗███████╗████████╗██████╗░██╗░███████╗\n ");
    printf("╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝\n ");
    printf("░░░██║░░░█████╗░░░░░██║░░░██████╔╝██║╚█████╗░\n ");
    printf("░░░██║░░░██╔══╝░░░░░██║░░░██╔══██╗██║░╚═══██╗\n ");
    printf("░░░██║░░░███████╗░░░██║░░░██║░░██║░░██║██║██║█████╔╝\n ");
    printf("░░░╚═╝░░░╚══════╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═ ════╝░\n ");
    printf("######################################## #############\n");
}

int main() {
    screenInit(1); // Inicializa a tela com as bordas

    exibirTelaInicial();
    
    // Aqui você pode chamar funções do seu jogo Tetris, por exemplo
    // Espera um tempo antes de reiniciar o jogo
    usleep(3000000);
    
    screenDestroy(); // Finaliza o uso da tela
    return 0;
}
