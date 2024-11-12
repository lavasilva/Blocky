#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para a função sleep() em Unix /Linux
#include "screen.h" // Inclui os cabeçalhos em vez dos arquivos .c
#include "timer.h"
#include "keyboard.h"

// Definindo o tamanho do tabuleiro
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

// Variáveis da peça atual e posição
struct Peca peçaAtual;  
int x, y;  // Posição da peça

// (Demais funções permanecem as mesmas)

// Função para exibir a tela inicial
void exibirTelaInicial() {
    system("clear"); // Limpa o terminal (ajuste para "cls" se estiver no Windows)
    
    // Exibe o título
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

    // Aguarde o usuário iniciar
    getchar();
}

// Função para exibir as instruções do jogo
void exibirInstrucoes() {
    system("clear"); // Limpa o terminal para as instruções
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
    getchar(); // Espera o usuário pressionar ENTER para continuar
}

// Função para inicializar a peça
void inicializarPeça() {
    int tipo = rand() % 7;  // Escolhe um tipo de peça aleatoriamente
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            peçaAtual.forma[i][j] = tetrominos[tipo][i][j];
        }
    }
    x = COLUNAS / 2 - 2;  // Posição inicial no centro do tabuleiro
    y = 0;  // Iniciar no topo
}

// Função para verificar colisões
int verificarColisao() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (peçaAtual.forma[i][j]) {
                if (y + i >= LINHAS || x + j < 0 || x + j >= COLUNAS || tabuleiro[y + i][x + j]) {
                    return 1;  // Colidiu com algo
                }
            }
        }
    }
    return 0;  // Não colidiu
}

// Função para rotacionar a peça
void rotacionarPeça() {
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = peçaAtual.forma[3 - j][i];  // Rotaciona a peça 90 graus
        }
    }

    // Verificar se a rotação é válida
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (temp[i][j] && (y + i >= LINHAS || x + j < 0 || x + j >= COLUNAS || tabuleiro[y + i][x + j])) {
                return;  // Não pode rotacionar
            }
        }
    }

    // Se a rotação é válida, atualizar a peça
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            peçaAtual.forma[i][j] = temp[i][j];
        }
    }
}

// Função para mover a peça para a esquerda
void moverEsquerda() {
    x--;
    if (verificarColisao()) {
        x++;  // Reverter o movimento
    }
}

// Função para mover a peça para a direita
void moverDireita() {
    x++;
    if (verificarColisao()) {
        x--;  // Reverter o movimento
    }
}

// Função para mover a peça para baixo
void moverAbaixo() {
    y++;
    if (verificarColisao()) {
        y--;  // Reverter o movimento
        // Adicionar a peça no tabuleiro e gerar uma nova peça
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (peçaAtual.forma[i][j]) {
                    tabuleiro[y + i][x + j] = 1;  // Preencher o tabuleiro
                }
            }
        }
        inicializarPeça();  // Gerar nova peça
    }
}

// Função para atualizar a tela com o estado atual do jogo
void atualizarTela() {
    system("clear"); // Limpa o terminal
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (tabuleiro[i][j]) {
                printf("X ");  // Peça fixa no tabuleiro
            } else if (i >= y && i < y + 4 && j >= x && j < x + 4 && peçaAtual.forma[i - y][j - x]) {
                printf("O ");  // Peça atual
            } else {
                printf(". ");  // Espaço vazio
            }
        }
        printf("\n");
    }
}

// Função principal do jogo
int main() {
    exibirTelaInicial();
    exibirInstrucoes();

    inicializarPeça();

    while (1) {
        atualizarTela();
        usleep(500 * 1000);  // Espera 500 ms entre atualizações
        moverAbaixo();
    }

    return 0;
}
