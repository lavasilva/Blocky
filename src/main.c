#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para a função sleep() em Unix /Linux
#include "screen.h" // Inclui os cabeçalhos em vez dos arquivos .c
#include "timer.h"
#include "keyboard.h"
#include "tetrominos.h" // Inclusão da biblioteca dos tetrominos

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

int main() {
    exibirTelaInicial(); // Exibe a tela inicial
    exibirInstrucoes();  // Exibe as instruções antes de começar o jogo

    // Inicializa os tetrominos
    inicializarTetrominos();

    // Aqui a gente inicia o jogo
    printf("Iniciando o jogo...\n");

    // Chama a função para desenhar a borda
    screenInit(1); // Inicializa a tela com bordas
    screenDrawBorders(); // Desenha as bordas após o início do jogo
    
    // Aqui você pode adicionar o código do jogo dentro da borda desenhada

    // Por enquanto, apenas exibe o tetromino "I" na tela para fins de teste
    printf("Exibindo o Tetromino 'I':\n");
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            if (tetrominos[0][i][j] == 1) {
                printf("█"); // Representação de bloco do tetromino
            } else {
                printf(" "); // Espaço vazio
            }
        }
        printf("\n");
    }

    // O código do jogo vai aqui...

    return 0;
}
