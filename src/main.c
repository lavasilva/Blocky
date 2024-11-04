#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para a função sleep()

void exibirTelaInicial() {
    system("clear"); // Limpa o terminal

    // Exibe o título 
    printf("############################################################\n");
    printf("#                                                          #\n");
    printf("#                 BEM-VINDO AO TETRIS MASTER               #\n");
    printf("#                                                          #\n");
    printf("############################################################\n");
    
    printf("\nPrepare-se para uma partida emocionante de TETRIS!\n");
    printf("Pressione ENTER para começar...\n");
    
    // Aguarda o usuário pressionar Enter para continuar
    getchar();
}

int main() {
    exibirTelaInicial();
    
    // Aqui a gente inicia o jogo
    printf("Iniciando o jogo...\n");

    return 0;
}

