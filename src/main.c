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
    printf("░░░╚═╝░░░╚══════╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═ ════╝░\n ");
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

// Função para desenhar a borda do jogo
void desenharBorda() {
    system("clear"); // Limpa a tela

    // Desenha a borda superior
    printf("===========================================\n");

    // Desenha as laterais e a parte de dentro do jogo
    for (int i = 0; i < LINHAS; i++) {  // Ajuste o número de linhas conforme necessário
        printf("||                                         ||\n");
    }

    // Desenha a borda inferior
    printf("===========================================\n");
}

// Função para desenhar o tabuleiro
void desenharTabuleiro() {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("  ");  // Espaço vazio
            } else {
                printf("[]"); // Bloco da peça
            }
        }
        printf("\n");
    }
}

// Função para girar a peça
void girarPeca(int peca[4][4]) {
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[j][3 - i] = peca[i][j]; // Realiza a rotação de 90 graus
        }
    }
    // Copia a matriz rotacionada de volta para a peça
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            peca[i][j] = temp[i][j];
        }
    }
}

// Função para mover a peça para baixo
void moverPecaParaBaixo(int peca[4][4], int *linha, int *coluna) {
    (*linha)++;
    if (verificarColisao(peca, *linha, *coluna)) {
        (*linha)--; // Se houver colisão, retorna a peça para sua posição anterior
        adicionarPecaAoTabuleiro(peca, *linha, *coluna);
        gerarNovaPeca();  // Gere uma nova peça
    }
}

// Função para verificar colisões
int verificarColisao(int peca[4][4], int linha, int coluna) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (peca[i][j] != 0) {
                if (linha + i >= LINHAS || coluna + j < 0 || coluna + j >= COLUNAS || tabuleiro[linha + i][coluna + j] != 0) {
                    return 1; // Colidiu com algo
                }
            }
        }
    }
    return 0; // Não colidiu
}

// Função para adicionar a peça ao tabuleiro
void adicionarPecaAoTabuleiro(int peca[4][4], int linha, int coluna) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (peca[i][j] != 0) {
                tabuleiro[linha + i][coluna + j] = 1; // Marca a posição da peça no tabuleiro
            }
        }
    }
}

// Função para gerar uma nova peça (aleatória)
void gerarNovaPeca() {
    // Aqui você deve gerar uma nova peça aleatória
}

// Função para iniciar o loop do jogo
int main() {
    exibirTelaInicial();
    exibirInstrucoes();
    desenharBorda();  // Desenha a borda

    int linha = 0, coluna = COLUNAS / 2 - 2;  // Posição inicial da peça

    // Loop do jogo
    while (1) {
        desenharTabuleiro();
        moverPecaParaBaixo(pecaAtual, &linha, &coluna); // Mover a peça para baixo
        usleep(500000);  // Aguarda 0.5 segundos para a próxima atualização
    }

    return 0;
}
