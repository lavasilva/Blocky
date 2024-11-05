#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para a função sleep()
#include <screen.c> // bibliotecas de Tiaguinho
#include <timer.c>
#include <keyboard.c>

void exibirTelaInicial() {
    system("clear"); // Limpa o terminal

    // Exibe o título 
    printf("############################################################\n");
    printf("████████╗███████╗████████╗██████╗░██╗░██████╗\n");
    printf("╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝\n");
    printf("░░░██║░░░█████╗░░░░░██║░░░██████╔╝██║╚█████╗░\n");
    printf("░░░██║░░░██╔══╝░░░░░██║░░░██╔══██╗██║░╚═══██╗\n");
    printf("░░░██║░░░███████╗░░░██║░░░██║░░██║██║██████╔╝\n");
    printf("░░░╚═╝░░░╚══════╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═════╝░\n");
    printf("############################################################\n");
    
    printf("\nPrepare-se para uma partida emocionante de TETRIS!\n");
    printf("Pressione ENTER...\n");
    
    // Aguarda o usuário pressionar Enter para continuar
    getchar();
}

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
    exibirTelaInicial();
    exibirInstrucoes(); // Exibe as instruções antes de começar o jogo
    
    // Aqui a gente inicia o jogo
    printf("Iniciando o jogo...\n");

    return 0;
}
